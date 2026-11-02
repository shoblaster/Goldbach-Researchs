"""Cross-check the Ziller--Morack condensed paired-Jacobsthal ILP.

For primes p_3,...,p_k, choose two nonzero residue classes modulo each p and
ask for the largest m such that every q in [1,m] is covered by at least one
chosen class. The ancillary note states h_2(k)=6*omega_2(k)+6 for k>2.
"""

from __future__ import annotations

import numpy as np
from scipy.optimize import Bounds, LinearConstraint, milp
from scipy.sparse import lil_matrix


PRIMES = (2, 3, 5, 7, 11, 13, 17, 19)


def feasible(primes, length):
    offsets = {}
    cursor = 0
    for p in primes:
        for residue in range(1, p):
            offsets[p, residue] = cursor
            cursor += 1

    rows = len(primes) + length
    matrix = lil_matrix((rows, cursor), dtype=float)
    lower = np.empty(rows)
    upper = np.empty(rows)
    row = 0
    for p in primes:
        for residue in range(1, p):
            matrix[row, offsets[p, residue]] = 1.0
        lower[row] = upper[row] = 2.0
        row += 1
    for q in range(1, length + 1):
        residue_count = 0
        for p in primes:
            residue = q % p
            if residue != 0:
                matrix[row, offsets[p, residue]] = 1.0
                residue_count += 1
        lower[row] = 1.0
        upper[row] = np.inf
        row += 1

    result = milp(
        c=np.zeros(cursor),
        integrality=np.ones(cursor, dtype=int),
        bounds=Bounds(np.zeros(cursor), np.ones(cursor)),
        constraints=LinearConstraint(matrix.tocsr(), lower, upper),
    )
    return bool(result.success)


for k in range(3, 9):
    odd_primes = PRIMES[2:k]
    length = 0
    while feasible(odd_primes, length + 1):
        length += 1
    h2 = 6 * length + 6
    print("k", k, "p_k", PRIMES[k - 1], "omega2", length,
          "reconstructed_h2", h2)
