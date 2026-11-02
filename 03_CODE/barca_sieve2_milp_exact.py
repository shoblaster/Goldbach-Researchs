"""Exact finite optimization for the Barca Sieve II residue model.

The binary variable x[p,r] selects a forbidden residue r modulo p.  The
binary variable y[n] records whether n survives every selected residue.
For each n, y[n] + sum(selected residues matching n) >= 1.  Minimizing
sum(y[n]) therefore gives the exact number of survivors: y[n] is forced to
1 exactly when no selected residue covers n, and is otherwise set to 0.

This is an exact finite formulation, not an asymptotic Goldbach proof.
It uses scipy.optimize.milp (HiGHS) and reports the solver status.
"""

from __future__ import annotations

import sys
from pathlib import Path

import numpy as np
from scipy.optimize import Bounds, LinearConstraint, milp
from scipy.sparse import lil_matrix


def solve(k: int) -> None:
    primes = (2, 3, 5, 7, 11, 13, 17, 19, 23)[:k]
    limit = primes[-1] ** 2

    x_offset = {}
    cursor = 0
    for p in primes:
        for r in range(p):
            x_offset[p, r] = cursor
            cursor += 1
    y_offset = cursor
    nvars = cursor + limit

    # One row per prime for the number of forbidden residue classes.
    # One row per n for the coverage/survival constraint.
    rows = len(primes) + limit
    A = lil_matrix((rows, nvars), dtype=float)
    lower = np.empty(rows, dtype=float)
    upper = np.empty(rows, dtype=float)

    row = 0
    for p in primes:
        for r in range(p):
            A[row, x_offset[p, r]] = 1.0
        target = 1.0 if p == 2 else 2.0
        lower[row] = upper[row] = target
        row += 1

    for n in range(1, limit + 1):
        for p in primes:
            A[row, x_offset[p, n % p]] = 1.0
        A[row, y_offset + n - 1] = 1.0
        lower[row] = 1.0
        upper[row] = np.inf
        row += 1

    objective = np.zeros(nvars, dtype=float)
    objective[y_offset:] = 1.0
    integrality = np.ones(nvars, dtype=int)
    bounds = Bounds(np.zeros(nvars), np.ones(nvars))
    constraints = LinearConstraint(A.tocsr(), lower, upper)

    result = milp(
        c=objective,
        integrality=integrality,
        bounds=bounds,
        constraints=constraints,
        options={"disp": False},
    )
    print("k", k, "status", result.status, result.message)
    if not result.success:
        return

    print("objective", result.fun,
          "mip_gap", getattr(result, "mip_gap", "UNAVAILABLE"),
          "mip_node_count", getattr(result, "mip_node_count", "UNAVAILABLE"))
    values = np.rint(result.x).astype(int)
    selected = tuple(
        tuple(r for r in range(p) if values[x_offset[p, r]]) for p in primes
    )
    survivors = tuple(n for n in range(1, limit + 1) if values[y_offset + n - 1])
    # Recompute the witness directly, independently of the MILP y variables.
    direct = tuple(
        n for n in range(1, limit + 1)
        if all(n % p not in selected[j] for j, p in enumerate(primes))
    )
    print("k", k, "limit", limit, "exact_minimum", len(survivors))
    print("selected", selected)
    print("survivors", survivors)
    print("direct_match", survivors == direct)


if __name__ == "__main__":
    ks = [int(sys.argv[1])] if len(sys.argv) > 1 else list(range(1, 9))
    for k in ks:
        solve(k)
