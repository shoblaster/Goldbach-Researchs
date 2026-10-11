"""Independent exhaustive k=6 audit of Barca's Sieve II model.

The earlier EXP007 implementation checks each integer for each residue
selection.  This implementation instead builds a bit mask of permitted
indices for every single-prime choice and intersects six masks.  It
enumerates every k=6 choice and then directly reconstructs each minimizer's
survivors for an independent output check.
"""

from itertools import combinations, product


PRIMES = (2, 3, 5, 7, 11, 13)
LIMIT = PRIMES[-1] ** 2


def make_choices():
    return [
        list(combinations(range(p), 1 if p == 2 else 2))
        for p in PRIMES
    ]


def make_masks(choices):
    masks = []
    for p, prime_choices in zip(PRIMES, choices):
        masks.append([
            sum(1 << (n - 1) for n in range(1, LIMIT + 1)
                if n % p not in forbidden)
            for forbidden in prime_choices
        ])
    return masks


def direct_survivors(selected):
    return tuple(
        n for n in range(1, LIMIT + 1)
        if all(n % p not in forbidden
               for p, forbidden in zip(PRIMES, selected))
    )


choices = make_choices()
masks = make_masks(choices)
minimum = LIMIT + 1
minimizers = []
tested = 0

for indices in product(*[range(len(options)) for options in choices]):
    mask = masks[0][indices[0]]
    for j in range(1, len(PRIMES)):
        mask &= masks[j][indices[j]]
    count = mask.bit_count()
    tested += 1
    selected = tuple(choices[j][indices[j]] for j in range(len(PRIMES)))
    if count < minimum:
        minimum = count
        minimizers = [selected]
    elif count == minimum:
        minimizers.append(selected)

print("tested_choices", tested)
print("exact_minimum_count", minimum)
print("number_of_minimizers", len(minimizers))
for selected in minimizers:
    survivors = direct_survivors(selected)
    print(selected, survivors)
