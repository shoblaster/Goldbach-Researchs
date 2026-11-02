"""Exact first and second moments for the k=8 finite residue model."""

from fractions import Fraction


PRIMES = (2, 3, 5, 7, 11, 13, 17, 19)


def one_point_probability(p):
    return Fraction(1, 2) if p == 2 else Fraction(p - 2, p)


def two_point_probability(p, same_residue):
    if p == 2:
        return Fraction(1, 2) if same_residue else Fraction(0, 1)
    if same_residue:
        return Fraction(p - 2, p)
    return Fraction((p - 2) * (p - 3), p * (p - 1))


limit = PRIMES[-1] ** 2
mean = Fraction(limit, 1)
for p in PRIMES:
    mean *= one_point_probability(p)

second = Fraction(0, 1)
for n in range(1, limit + 1):
    for m in range(1, limit + 1):
        probability = Fraction(1, 1)
        for p in PRIMES:
            probability *= two_point_probability(p, n % p == m % p)
        second += probability

variance = second - mean * mean
print("k=8 p_k=19 limit=361")
print("mean", mean)
print("second_moment", second)
print("variance", variance)
print("variance_decimal", float(variance))
print("minimum_from_EXP015", 4)
print("minimum_to_mean_ratio", Fraction(4, 1) / mean)
