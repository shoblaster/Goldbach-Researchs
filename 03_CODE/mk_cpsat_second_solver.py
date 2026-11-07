"""Second-solver cross-check of the fixed-window minima M_k (EXP015/EXP019).

Same mathematical model as barca_sieve2_milp_exact.py but written from the
definition with a different solver (OR-tools CP-SAT instead of HiGHS):
  * primes p_1..p_k = 2,3,5,...; window n in [1, p_k^2];
  * choose 1 forbidden residue mod 2 and exactly 2 forbidden residues mod each odd p;
  * n survives if no chosen residue equals n mod p for any p;
  * M_k = minimum number of survivors over all choices.
The reported witness is recomputed directly from the definition.  Usage:
  python mk_cpsat_second_solver.py K [K ...]    (env TIME_LIMIT seconds, default 900)
A status other than OPTIMAL means NO exact minimum is claimed; the best
objective and the proven lower bound are printed instead.
"""
import os
import sys
import time
from ortools.sat.python import cp_model

PRIMES = (2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31)
RECORDED = {1: 2, 2: 1, 3: 2, 4: 2, 5: 3, 6: 2, 7: 4, 8: 4, 9: 5}  # EXP007..EXP019


def solve(k, limit_s):
    primes = PRIMES[:k]
    W = primes[-1] ** 2
    m = cp_model.CpModel()
    x = {(p, r): m.NewBoolVar(f"x{p}_{r}") for p in primes for r in range(p)}
    for p in primes:
        m.Add(sum(x[p, r] for r in range(p)) == (1 if p == 2 else 2))
    y = [m.NewBoolVar(f"y{n}") for n in range(1, W + 1)]
    for n in range(1, W + 1):
        m.AddBoolOr([y[n - 1]] + [x[p, n % p] for p in primes])
    m.Minimize(sum(y))
    s = cp_model.CpSolver()
    s.parameters.max_time_in_seconds = limit_s
    s.parameters.num_workers = 2
    t = time.time()
    st = s.Solve(m)
    name = s.StatusName(st)
    out = {"k": k, "window": W, "status": name,
           "seconds": round(time.time() - t, 1)}
    if st in (cp_model.OPTIMAL, cp_model.FEASIBLE):
        chosen = {p: tuple(r for r in range(p) if s.Value(x[p, r]))
                  for p in primes}
        direct = [n for n in range(1, W + 1)
                  if all(n % p not in chosen[p] for p in primes)]
        out.update(objective=int(s.ObjectiveValue()),
                   best_bound=s.BestObjectiveBound(),
                   direct_survivors=len(direct),
                   direct_match=(len(direct) == int(s.ObjectiveValue())),
                   survivors=tuple(direct[:12]),
                   selected=tuple(chosen[p] for p in primes))
    return out


if __name__ == "__main__":
    lim = float(os.environ.get("TIME_LIMIT", "900"))
    print(f"solver cpsat (ortools {__import__('ortools').__version__}) time_limit_s {lim}")
    for k in map(int, sys.argv[1:]):
        r = solve(k, lim)
        rec = RECORDED.get(k)
        agree = (None if rec is None or r["status"] != "OPTIMAL"
                 else r["objective"] == rec)
        print(r, "recorded_minimum", rec, "agrees_with_recorded", agree, flush=True)
