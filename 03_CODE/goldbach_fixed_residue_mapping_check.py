"""Finite check of the fixed-N Goldbach residue-sieve correspondence.

For an even N, remove even n and every n with p | n or p | (N-n) for a
prime p with p^2 < N.  On 3 <= n <= N-3, the survivors should be exactly the
ordered offsets for which n and N-n are both primes greater than sqrt(N).
This script checks that elementary correspondence over a finite range.
"""

from __future__ import annotations

import math


def primes_up_to(limit: int) -> list[int]:
    sieve = bytearray(b"\x01") * (limit + 1)
    if limit >= 0:
        sieve[0] = 0
    if limit >= 1:
        sieve[1] = 0
    for p in range(2, math.isqrt(limit) + 1):
        if sieve[p]:
            sieve[p * p : limit + 1 : p] = b"\x00" * (((limit - p * p) // p) + 1)
    return [p for p, is_prime in enumerate(sieve) if is_prime]


def is_prime_trial(n: int) -> bool:
    if n < 2:
        return False
    if n % 2 == 0:
        return n == 2
    d = 3
    while d * d <= n:
        if n % d == 0:
            return False
        d += 2
    return True


def check_even_N(
    N: int, primes: list[int], trial_prime_set: set[int]
) -> tuple[set[int], set[int]]:
    cutoff_primes = [p for p in primes if p * p < N]
    root = math.sqrt(N)
    survivors = set()
    for n in range(3, N - 2):
        if n % 2 == 0:
            continue
        if any(n % p == 0 or (N - n) % p == 0 for p in cutoff_primes):
            continue
        survivors.add(n)

    target = {
        n
        for n in range(3, N - 2)
        if n % 2 == 1
        and n > root
        and N - n > root
        and n in trial_prime_set
        and N - n in trial_prime_set
    }
    return survivors, target


def main() -> None:
    maximum = 10_000
    primes = primes_up_to(maximum)
    prime_set = set(primes)
    trial_prime_set = {n for n in range(maximum + 1) if is_prime_trial(n)}
    if prime_set != trial_prime_set:
        raise AssertionError("sieve and independent trial-division prime sets differ")
    # Membership checks in check_even_N use `in primes`; use a local list-like
    # set-backed wrapper by replacing the list with a sorted set is unnecessary
    # at this range, but retain the exact finite algorithm and report the range.
    checked = 0
    for N in range(6, maximum + 1, 2):
        survivors, target = check_even_N(N, prime_set, trial_prime_set)
        if survivors != target:
            print("MISMATCH", N, sorted(survivors), sorted(target))
            raise SystemExit(1)
        checked += 1

    for sample in (100, 1000, 10000):
        survivors, _ = check_even_N(sample, prime_set, trial_prime_set)
        ordered = sorted(survivors)
        print(
            "sample",
            sample,
            "survivor_count",
            len(ordered),
            "first10",
            ordered[:10],
            "last10",
            ordered[-10:],
        )
    print("checked_even_N", checked, "range", "6..10000", "step", 2)
    print("independent_trial_division_prime_check", True)
    print("all_exact_matches", True)


if __name__ == "__main__":
    main()
