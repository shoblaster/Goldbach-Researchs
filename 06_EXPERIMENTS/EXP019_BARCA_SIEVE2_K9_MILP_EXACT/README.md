# EXP019 — exact k=9 fixed-window MILP extension

This experiment extends the exact 0–1 MILP in EXP015 to k=9, with
`p_9 = 23` and window `[1,529]`. It uses the same formulation and solver
script, now with the prime 23 included in the source list.

Command actually run:

    python 03_CODE/barca_sieve2_milp_exact.py 9

Environment: Python 3.14.4, SciPy 1.17.1, HiGHS via `scipy.optimize.milp`.
The raw solver output is preserved verbatim. The solver reported optimal status,
zero MIP gap, and direct modular recomputation agreed with the MILP witness.
This is an exact finite computation only; it does not establish an asymptotic
bound, a theorem for all k, Goldbach, or novelty.
