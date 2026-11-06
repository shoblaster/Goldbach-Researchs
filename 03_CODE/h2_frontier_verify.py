"""Independently test source-reported paired-Jacobsthal values h2(k).

Model (same as paired_jacobsthal_ilp_crosscheck.py, Ziller-Morack ancillary
ILP, CIT-032): for each prime p in {5,...,p_k} choose exactly two nonzero
residues mod p.  Position q is covered when some prime p has q % p != 0 and
q % p is a chosen residue.  omega2(k) is the largest L such that positions
1..L can all be covered, and h2(k) = 6*omega2(k) + 6 (k >= 3).

Feasibility is monotone in L (a cover of [1,L] covers [1,L-1]), so
h2(k) = H is certified by: L = (H-6)/6 feasible AND L+1 infeasible.

Usage: python h2_frontier_verify.py SOLVER K [K ...]
       SOLVER is 'cpsat' or 'highs'.  Source values come from Table 1 of
       arXiv:1706.03668 (CIT-029) and are TRANSCRIBED, not computed here.
"""
import sys
import time

PRIMES = (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
          61, 67, 71, 73)
SOURCE_H2 = {3: 18, 4: 30, 5: 66, 6: 150, 7: 192, 8: 258, 9: 366, 10: 450,
             11: 570, 12: 708, 13: 894, 14: 1044, 15: 1284, 16: 1422,
             17: 1656, 18: 1902, 19: 2190, 20: 2460, 21: 2622}


def check_witness(primes, chosen, length):
    for q in range(1, length + 1):
        if not any(q % p != 0 and (q % p) in chosen[p] for p in primes):
            return False
    return all(len(chosen[p]) == 2 for p in primes)


def solve_cpsat(primes, length, limit):
    from ortools.sat.python import cp_model
    m = cp_model.CpModel()
    x = {(p, r): m.NewBoolVar(f"x{p}_{r}") for p in primes
         for r in range(1, p)}
    for p in primes:
        m.Add(sum(x[p, r] for r in range(1, p)) == 2)
    for q in range(1, length + 1):
        m.AddBoolOr([x[p, q % p] for p in primes if q % p != 0])
    s = cp_model.CpSolver()
    s.parameters.max_time_in_seconds = limit
    s.parameters.num_workers = 2
    st = s.Solve(m)
    if st in (cp_model.OPTIMAL, cp_model.FEASIBLE):
        ch = {p: {r for r in range(1, p) if s.Value(x[p, r])} for p in primes}
        return "FEASIBLE", ch
    if st == cp_model.INFEASIBLE:
        return "INFEASIBLE", None
    return "UNKNOWN", None


def solve_highs(primes, length, limit):
    import numpy as np
    from scipy.optimize import Bounds, LinearConstraint, milp
    from scipy.sparse import lil_matrix
    off, cur = {}, 0
    for p in primes:
        for r in range(1, p):
            off[p, r] = cur
            cur += 1
    A = lil_matrix((len(primes) + length, cur))
    lo = np.empty(len(primes) + length)
    hi = np.empty(len(primes) + length)
    row = 0
    for p in primes:
        for r in range(1, p):
            A[row, off[p, r]] = 1
        lo[row] = hi[row] = 2
        row += 1
    for q in range(1, length + 1):
        for p in primes:
            if q % p:
                A[row, off[p, q % p]] = 1
        lo[row], hi[row] = 1, np.inf
        row += 1
    res = milp(c=np.zeros(cur), integrality=np.ones(cur),
               bounds=Bounds(0, 1), constraints=LinearConstraint(A.tocsr(), lo, hi),
               options={"time_limit": limit})
    if res.status == 0:
        ch = {p: {r for r in range(1, p) if res.x[off[p, r]] > 0.5}
              for p in primes}
        return "FEASIBLE", ch
    if res.status == 2:
        return "INFEASIBLE", None
    return "UNKNOWN", None


def main():
    solver = sys.argv[1]
    fn = {"cpsat": solve_cpsat, "highs": solve_highs}[solver]
    limit = float(__import__("os").environ.get("TIME_LIMIT", "900"))
    print(f"solver {solver} time_limit_s {limit}")
    for k in map(int, sys.argv[2:]):
        primes = PRIMES[2:k]
        H = SOURCE_H2[k]
        L = (H - 6) // 6
        t = time.time()
        s1, ch = fn(primes, L, limit)
        w = check_witness(primes, ch, L) if ch else None
        s2, _ = fn(primes, L + 1, limit)
        ok = (s1 == "FEASIBLE" and w and s2 == "INFEASIBLE")
        print(f"k {k} p_k {PRIMES[k-1]} source_h2 {H} omega2 {L} "
              f"L_status {s1} witness_direct_check {w} "
              f"L+1_status {s2} certified {ok} seconds {time.time()-t:.1f}",
              flush=True)


main()
