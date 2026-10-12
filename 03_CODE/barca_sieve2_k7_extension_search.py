"""Search k=7 candidates by optimizing the two forbidden residues mod 17.

For each of the 5,405,400 choices through p=13, this computes the permitted
indices in [1,17^2], groups them by residue mod 17, and chooses the two
classes that remove the most survivors. This is equivalent to minimizing over
all two-residue choices modulo 17, while avoiding a 734-million-case direct
enumeration.
"""

from itertools import combinations, product


PRIMES = (2, 3, 5, 7, 11, 13)
LIMIT = 17 ** 2
choices = [list(combinations(range(p), 1 if p == 2 else 2)) for p in PRIMES]
masks = [
    [sum(1 << (n - 1) for n in range(1, LIMIT + 1)
         if n % p not in forbidden) for forbidden in prime_choices]
    for p, prime_choices in zip(PRIMES, choices)
]
class_masks = [
    sum(1 << (n - 1) for n in range(1, LIMIT + 1) if n % 17 == residue)
    for residue in range(17)
]

best = LIMIT + 1
rows = []
tested = 0
for indices in product(*[range(len(options)) for options in choices]):
    mask = masks[0][indices[0]]
    for j in range(1, len(PRIMES)):
        mask &= masks[j][indices[j]]
    counts = [(mask & class_mask).bit_count() for class_mask in class_masks]
    total = mask.bit_count()
    forbidden17 = tuple(sorted(range(17), key=lambda r: counts[r], reverse=True)[:2])
    remaining = total - counts[forbidden17[0]] - counts[forbidden17[1]]
    tested += 1
    if remaining < best:
        best = remaining
        rows = [(indices, total, forbidden17, counts, mask)]
    elif remaining == best and len(rows) < 10:
        rows.append((indices, total, forbidden17, counts, mask))

print("tested_k6_choices", tested)
print("best_k7_count", best)
print("examples_recorded", len(rows))
for indices, total, forbidden17, counts, mask in rows:
    selected = tuple(choices[j][indices[j]] for j in range(len(PRIMES)))
    survivors = tuple(
        n for n in range(1, LIMIT + 1)
        if (mask >> (n - 1)) & 1 and n % 17 not in forbidden17
    )
    print("selection", selected)
    print("forbidden_mod17", forbidden17)
    print("before_mod17", total, "after", len(survivors), "survivors", survivors)
    print("residue_counts", tuple(counts))
