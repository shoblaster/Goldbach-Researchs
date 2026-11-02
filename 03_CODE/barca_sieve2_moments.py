"""Exact first and second moments for the finite Sieve II model.

Residue choices are uniform and independent across primes.  The script sums
the exact local joint probabilities for every ordered pair of indices n,m in
[1,p_k^2]. It therefore computes the variance without enumerating residue
choices, and provides an independent check on EXP011's exhaustive variances.
"""

from fractions import Fraction


PRIMES = (2, 3, 5, 7, 11, 13, 17)


def one_point_probability(p):
    return Fraction(p - 1, p) if p == 2 else Fraction(p - 2, p)


def two_point_probability(p, same_residue):
    if p == 2:
        return Fraction(1, 2) if same_residue else Fraction(0, 1)
    if same_residue:
        return Fraction(p - 2, p)
    # Two distinct residues must both avoid a uniformly selected pair.
    return Fraction((p - 2) * (p - 3), p * (p - 1))


def moments(primes):
    limit = primes[-1] ** 2
    first = Fraction(1, 1)
    for p in primes:
        first *= one_point_probability(p)
    # The expected count is limit times the per-index probability.
    first *= limit

    second = Fraction(0, 1)
    for n in range(1, limit + 1):
        for m in range(1, limit + 1):
            pair_probability = Fraction(1, 1)
            for p in primes:
                pair_probability *= two_point_probability(p, n % p == m % p)
            second += pair_probability
    variance = second - first * first
    return limit, first, second, variance


for k in range(1, len(PRIMES) + 1):
    limit, first, second, variance = moments(PRIMES[:k])
    print(
        f"k={k} p_k={PRIMES[k-1]} limit={limit} "
        f"mean={first} second_moment={second} variance={variance}"
    )
