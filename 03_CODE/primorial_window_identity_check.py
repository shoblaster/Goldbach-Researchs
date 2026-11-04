"""Independent finite check of the primorial lower-window identity.

For N = p_k# and H = p_(k+1)^2, the source-level claim audited here is

    #{p < H : p and N-p are prime}
      = #{q prime : N-H < q <= N-2}.

The script checks the stronger set bijection q = N-p for manageable primorials.
It uses trial division only; no external primality library is used.  This is a
finite verification of the stated identity, not a proof of Goldbach.
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


def check_k(k: int, primes: list[int]) -> tuple[int, int, set[int], set[int]]:
    p_k = primes[k - 1]
    p_next = primes[k]
    N = 1
    for p in primes[:k]:
        N *= p
    H = p_next * p_next

    direct_p = {
        p
        for p in range(2, H)
        if is_prime_trial(p) and is_prime_trial(N - p)
    }
    interval_q = {
        q
        for q in range(max(2, N - H + 1), N - 1)
        if is_prime_trial(q)
    }
    mapped_q = {N - p for p in direct_p}
    if mapped_q != interval_q:
        raise AssertionError(
            f"bijection mismatch for k={k}, N={N}, H={H}: "
            f"mapped-only={sorted(mapped_q - interval_q)}, "
            f"interval-only={sorted(interval_q - mapped_q)}"
        )
    return N, H, direct_p, interval_q


def main() -> None:
    # k=4,...,8 keeps every independent trial-division check comfortably finite
    # and ensures N-H >= 2, so the interval count has the intended endpoints.
    primes = first_primes(9)
    print("primes_used", primes)
    for k in range(4, 9):
        N, H, direct_p, interval_q = check_k(k, primes)
        print(
            "k",
            k,
            "N",
            N,
            "p_next",
            primes[k],
            "H",
            H,
            "direct_count",
            len(direct_p),
            "interval_count",
            len(interval_q),
            "bijection",
            True,
            "first_p",
            sorted(direct_p)[:10],
            "first_q",
            sorted(interval_q)[:10],
        )
    # Boundary diagnostic: the literal formula fails at the tiny primorial
    # N=30 if H=p_4^2=49, because the interval then reaches q=2,3,5.  This is
    # recorded rather than hidden; the audited identity is used only once
    # N-H > p_k (k>=4 in this run).
    N = 2 * 3 * 5
    H = 7 * 7
    direct_p = {
        p
        for p in range(2, H)
        if is_prime_trial(p) and is_prime_trial(N - p)
    }
    interval_q = {
        q
        for q in range(max(2, N - H + 1), N - 1)
        if is_prime_trial(q)
    }
    print(
        "edge_case_k",
        3,
        "N",
        N,
        "H",
        H,
        "direct_count",
        len(direct_p),
        "interval_count",
        len(interval_q),
        "extra_interval_primes",
        sorted(interval_q - {N - p for p in direct_p}),
        "literal_formula_match",
        False,
    )
    print("all_exact_matches", True)
    print("primality_method", "independent trial division")


if __name__ == "__main__":
    main()
