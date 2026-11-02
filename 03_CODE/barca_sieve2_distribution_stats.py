"""Distributional audit for Barca's finite Sieve II model, k <= 6.

The bit-mask count is independent of EXP007's per-integer implementation.
For k <= 5 every mask result is cross-checked by direct modular filtering.
For k=6, deterministic samples are cross-checked because a full direct
cross-check would repeat billions of modular tests.
"""

from collections import Counter
from fractions import Fraction
from itertools import combinations, product, islice
from statistics import median


PRIMES = (2, 3, 5, 7, 11, 13)


def choices_for(prime):
    return list(combinations(range(prime), 1 if prime == 2 else 2))


def make_masks(primes, limit, choices):
    return [
        [
            sum(1 << (n - 1) for n in range(1, limit + 1)
                if n % p not in forbidden)
            for forbidden in prime_choices
        ]
        for p, prime_choices in zip(primes, choices)
    ]


def direct_count(primes, selected, limit):
    return sum(
        all(n % p not in forbidden
            for p, forbidden in zip(primes, selected))
        for n in range(1, limit + 1)
    )


def expected_count(primes, limit):
    probability = Fraction(primes[0] - 1, primes[0])
    for p in primes[1:]:
        probability *= Fraction(p - 2, p)
    return limit * probability


def percentile(histogram, total, numerator, denominator):
    target = (total * numerator + denominator - 1) // denominator
    seen = 0
    for value in sorted(histogram):
        seen += histogram[value]
        if seen >= target:
            return value
    raise AssertionError("percentile target was not reached")


for k in range(1, len(PRIMES) + 1):
    primes = PRIMES[:k]
    limit = primes[-1] ** 2
    choices = [choices_for(p) for p in primes]
    masks = make_masks(primes, limit, choices)
    histogram = Counter()
    total = 0
    sum_counts = 0
    sum_squares = 0
    sample_for_direct = []

    for indices in product(*[range(len(options)) for options in choices]):
        mask = masks[0][indices[0]]
        for j in range(1, k):
            mask &= masks[j][indices[j]]
        count = mask.bit_count()
        histogram[count] += 1
        total += 1
        sum_counts += count
        sum_squares += count * count
        if k <= 5 or (k == 6 and total <= 100):
            sample_for_direct.append(indices)

    for indices in sample_for_direct:
        selected = tuple(choices[j][indices[j]] for j in range(k))
        mask = masks[0][indices[0]]
        for j in range(1, k):
            mask &= masks[j][indices[j]]
        assert mask.bit_count() == direct_count(primes, selected, limit)

    mean = Fraction(sum_counts, total)
    variance = Fraction(sum_squares, total) - mean * mean
    expected = expected_count(primes, limit)
    assert mean == expected

    print(f"k={k} p_k={primes[-1]} limit={limit}")
    print(f"choices={total} min={min(histogram)} max={max(histogram)}")
    print(f"mean_count={mean} expected_count={expected}")
    print(f"mean_normalized={mean / primes[-1]} expected_delta={expected / primes[-1]}")
    print(f"population_variance={variance}")
    print(
        "quantiles(min, q25, median, q75, max)=",
        (
            min(histogram),
            percentile(histogram, total, 1, 4),
            percentile(histogram, total, 1, 2),
            percentile(histogram, total, 3, 4),
            max(histogram),
        ),
    )
    print("histogram=" + ",".join(f"{value}:{histogram[value]}" for value in sorted(histogram)))
    print()
