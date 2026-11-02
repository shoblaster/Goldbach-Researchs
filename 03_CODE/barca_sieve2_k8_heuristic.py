"""Exploratory k=8 local search for the finite Sieve II minimum.

This is deliberately not an exact search. It uses fixed-seed simulated
annealing over the first seven prime choices and optimizes the two forbidden
residue classes modulo 19 exactly at each state. Its only purpose is to find
candidate witnesses for a later exact branch-and-bound investigation.
"""

import random
from itertools import combinations


PRIMES = (2, 3, 5, 7, 11, 13, 17)
FINAL_PRIME = 19
LIMIT = FINAL_PRIME ** 2
RESTARTS = 20
ITERATIONS = 5000
SEED = 20261102

choices = [list(combinations(range(p), 1 if p == 2 else 2)) for p in PRIMES]
masks = [
    [
        sum(1 << (n - 1) for n in range(1, LIMIT + 1)
            if n % p not in forbidden)
        for forbidden in prime_choices
    ]
    for p, prime_choices in zip(PRIMES, choices)
]
class_masks = [
    sum(1 << (n - 1) for n in range(1, LIMIT + 1) if n % FINAL_PRIME == r)
    for r in range(FINAL_PRIME)
]


def objective(selection):
    mask = (1 << LIMIT) - 1
    for j, index in enumerate(selection):
        mask &= masks[j][index]
    counts = [(mask & class_mask).bit_count() for class_mask in class_masks]
    forbidden = tuple(sorted(range(FINAL_PRIME),
                             key=lambda r: counts[r], reverse=True)[:2])
    return (mask.bit_count() - counts[forbidden[0]] - counts[forbidden[1]],
            forbidden, mask, counts)


rng = random.Random(SEED)
best_score = LIMIT + 1
best_state = None
for restart in range(RESTARTS):
    selection = [rng.randrange(len(options)) for options in choices]
    score, forbidden, mask, counts = objective(selection)
    temperature = 2.0
    for _ in range(ITERATIONS):
        j = rng.randrange(len(selection))
        old = selection[j]
        selection[j] = rng.randrange(len(choices[j]))
        new_score, new_forbidden, new_mask, new_counts = objective(selection)
        accept = new_score <= score or rng.random() < pow(
            2.71828, (score - new_score) / max(temperature, 0.05)
        )
        if accept:
            score, forbidden, mask, counts = (
                new_score, new_forbidden, new_mask, new_counts
            )
        else:
            selection[j] = old
        temperature *= 0.999
        if score < best_score:
            best_score = score
            best_state = (selection[:], forbidden, mask, counts)
    print("restart", restart, "best", best_score)

selection, forbidden, mask, counts = best_state
selected = tuple(choices[j][selection[j]] for j in range(len(PRIMES)))
survivors = tuple(
    n for n in range(1, LIMIT + 1)
    if ((mask >> (n - 1)) & 1) and n % FINAL_PRIME not in forbidden
)
print("BEST", best_score)
print("selection", selected)
print("forbidden19", forbidden)
print("survivors", survivors)
print("before", mask.bit_count())
