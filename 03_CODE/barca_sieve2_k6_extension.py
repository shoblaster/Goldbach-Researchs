"""Targeted k=6 extension of the finite Barca Sieve II audit.

This is not an exhaustive k=6 search.  It fixes the k=5 minimizer found by
EXP007 and enumerates all choices of the two forbidden residues modulo 13.
It records a valid finite choice with unusually small left-block count.
"""

from itertools import combinations


PRIMES = (2, 3, 5, 7, 11, 13)
BASE = ((0,), (0, 1), (0, 2), (1, 3), (1, 9))


def survivors(selected):
    return tuple(
        n
        for n in range(1, PRIMES[-1] ** 2 + 1)
        if all(n % p not in forbidden for p, forbidden in zip(PRIMES, selected))
    )


rows = []
for extra in combinations(range(13), 2):
    selected = BASE + (extra,)
    kept = survivors(selected)
    rows.append((len(kept), extra, kept))

for row in sorted(rows)[:10]:
    print(row)

print("tested_extensions", len(rows))
print("best_count_upper_bound", min(row[0] for row in rows))
print("best_normalized_density_upper_bound", min(row[0] for row in rows) / 13)
print("full_period_normalized_density", 1485 / 2310)
