"""Finite audit of Barca's Sieve II residue-selection model.

This script enumerates every allowed choice of one forbidden residue modulo 2
and two forbidden residues modulo each later prime, then counts permitted
indices n in 1 <= n <= p_k^2.  It is a finite diagnostic only; it makes no
claim about any unbounded k.
"""

from itertools import combinations, product


PRIMES = (2, 3, 5, 7, 11)


def choices_for_prime(p: int):
    size = 1 if p == 2 else 2
    return tuple(combinations(range(p), size))


def count_permitted(primes, selected, limit):
    count = 0
    for n in range(1, limit + 1):
        if all(n % p not in forbidden for p, forbidden in zip(primes, selected)):
            count += 1
    return count


def audit(k: int):
    primes = PRIMES[:k]
    limit = primes[-1] ** 2
    option_lists = tuple(choices_for_prime(p) for p in primes)
    min_count = None
    max_count = None
    minimizer = None
    minimizer_survivors = None
    total = 0
    for selected in product(*option_lists):
        count = count_permitted(primes, selected, limit)
        total += 1
        if min_count is None or count < min_count:
            min_count = count
            minimizer = selected
            minimizer_survivors = tuple(
                n
                for n in range(1, limit + 1)
                if all(n % p not in forbidden for p, forbidden in zip(primes, selected))
            )
        max_count = count if max_count is None else max(max_count, count)
    return {
        "k": k,
        "p_k": primes[-1],
        "limit": limit,
        "choices": total,
        "min_count": min_count,
        "min_density_count_over_p_k": min_count / primes[-1],
        "max_count": max_count,
        "max_density_count_over_p_k": max_count / primes[-1],
        "minimizer": minimizer,
        "minimizer_survivors": minimizer_survivors,
    }


if __name__ == "__main__":
    for k in range(1, len(PRIMES) + 1):
        print(audit(k))
