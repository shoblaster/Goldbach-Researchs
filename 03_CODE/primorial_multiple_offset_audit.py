"""Finite audit of forced-prime offsets for primorial multiples.

For P_k=p_k#, choose R whose prime factors are all at most p_k and set
N=R*P_k.  The elementary claim audited here is:

    if 2 <= m < p_(k+1)^2 and N+m is prime, then m is prime;
    if additionally N-m > p_k and N-m is prime, then m is prime.

The second endpoint condition is deliberate: without it, a small prime
N-m <= p_k can divide N and produce a tiny boundary exception.  This script
tests many smooth multipliers with trial division only.  It does not prove a
Goldbach theorem and makes no novelty claim.
"""

from __future__ import annotations


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


def first_primes(count: int) -> list[int]:
    result: list[int] = []
    candidate = 2
    while len(result) < count:
        if is_prime_trial(candidate):
            result.append(candidate)
        candidate += 1
    return result


def smooth_numbers(limit: int, allowed_primes: list[int]) -> list[int]:
    values = {1}
    for p in allowed_primes:
        additions = set()
        for value in values:
            power = value
            while power <= limit:
                additions.add(power)
                power *= p
        values |= additions
    return sorted(values)


def audit_k(k: int, primes: list[int], multiplier_limit: int) -> dict[str, object]:
    p_k = primes[k - 1]
    p_next = primes[k]
    primorial = 1
    for p in primes[:k]:
        primorial *= p
    H = p_next * p_next
    multipliers = smooth_numbers(multiplier_limit, primes[:k])

    plus_failures: list[tuple[int, int]] = []
    minus_failures: list[tuple[int, int]] = []
    boundary_failures: list[tuple[int, int]] = []
    endpoint_min = None
    for R in multipliers:
        N = R * primorial
        endpoint_min = N - (H - 1) if endpoint_min is None else min(
            endpoint_min, N - (H - 1)
        )
        for m in range(2, H):
            if is_prime_trial(N + m) and not is_prime_trial(m):
                plus_failures.append((R, m))
            if N - m > p_k and is_prime_trial(N - m) and not is_prime_trial(m):
                minus_failures.append((R, m))
            if N - m >= 2 and N - m <= p_k:
                if is_prime_trial(N - m) and not is_prime_trial(m):
                    boundary_failures.append((R, m))

    return {
        "k": k,
        "p_k": p_k,
        "p_next": p_next,
        "primorial": primorial,
        "H": H,
        "multiplier_limit": multiplier_limit,
        "multiplier_count": len(multipliers),
        "plus_failures": plus_failures,
        "minus_failures_under_endpoint": minus_failures,
        "boundary_failures": boundary_failures,
        "minimum_N_minus_(H-1)": endpoint_min,
    }


def main() -> None:
    primes = first_primes(7)
    print("primes_used", primes)
    results = []
    for k in range(3, 7):
        result = audit_k(k, primes, multiplier_limit=200)
        results.append(result)
        print(
            "k",
            result["k"],
            "p_k",
            result["p_k"],
            "p_next",
            result["p_next"],
            "primorial",
            result["primorial"],
            "H",
            result["H"],
            "multipliers",
            result["multiplier_count"],
            "plus_failures",
            len(result["plus_failures"]),
            "minus_failures_under_endpoint",
            len(result["minus_failures_under_endpoint"]),
            "boundary_failures",
            len(result["boundary_failures"]),
            "boundary_examples",
            result["boundary_failures"][:10],
            "minimum_N_minus_(H-1)",
            result["minimum_N_minus_(H-1)"],
        )
        if result["plus_failures"] or result["minus_failures_under_endpoint"]:
            raise AssertionError(f"forced-prime implication failed: {result}")
    print("all_endpoint_implications_match", True)
    print("primality_method", "independent trial division")
    print(
        "boundary_note",
        "boundary failures are reported, not counted as endpoint failures",
    )


if __name__ == "__main__":
    main()
