# EXP024 — second-method cross-check of the fixed-window minima M_k

Branch: `verify/m-k-second-solver`. Question: RQ3 in `01_RESEARCH_QUESTIONS.md`.
Reference values: EXP007/009/010 (exhaustive, k<=7), EXP015 (k=8) and EXP019 (k=9), the last two from a
single HiGHS run each. Raw output: `RAW_OUTPUT.txt`.

## Two independent attempts
1. **CP-SAT** (`03_CODE/mk_cpsat_second_solver.py`): same model as EXP015, different solver.
2. **Exact enumeration, no solver** (`03_CODE/mk_enum_cpp.cpp`): enumerate every residue selection for
   primes `p_1..p_{k-1}` with bit-mask survivor sets, then choose the last prime's two classes exactly
   (the two classes holding the most survivors give the minimum over all pairs). This covers every selection
   of the full model and shares no code or solver with the MILP.

## Results (from `RAW_OUTPUT.txt`)
| k | window | recorded M_k | CP-SAT (300 s) | C++ enumeration |
|---:|---:|---:|---|---|
| 1 | 4 | 2 | OPTIMAL 2 | not run (k>=3 only) |
| 2 | 9 | 1 | OPTIMAL 1 | not run |
| 3 | 25 | 2 | OPTIMAL 2 | exact 2 |
| 4 | 49 | 2 | OPTIMAL 2 | exact 2 |
| 5 | 121 | 3 | OPTIMAL 3 | exact 3 |
| 6 | 169 | 2 | OPTIMAL 2 | exact 2 |
| 7 | 289 | 4 | FEASIBLE 4, **proven bound 0** | exact 4 (<1 s) |
| 8 | 361 | 4 | FEASIBLE 4, **proven bound 0** | exact 4 (77 s, 2 threads) |

Every reported witness was recomputed directly from the definition (`direct_match True`).

* **k = 8 is now confirmed by a non-solver exhaustive method:** `M_8 = 4`, agreeing with EXP015.
* **CP-SAT is not a usable certifier here.** It rediscovers the optimal witnesses at k=7,8 but its lower
  bound stays at 0 within 300 s, so it certifies nothing for k>=7. This is a limit of the formulation under
  CP-SAT, not evidence about M_k.
* **k = 9 (M_9 = 5, EXP019) is NOT re-verified.** Full enumeration needs about 1.3e11 prefix selections
  (171 times the k=8 run: at least 171 x 77 s, about 3.7 hours on this 2-thread machine, and more because
  the last prime has 23 classes and the masks are wider); not attempted. M_9 still rests on one HiGHS run plus direct witness recomputation.
* No value for k >= 10 is claimed.

## Interpretation and limits
Finite computation only; it supports the correctness of the existing minima for k <= 8 and says nothing
about asymptotics, Strong Goldbach, or novelty. **NOVELTY NOT ESTABLISHED.**
