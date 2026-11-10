# EXP032 — exhaustive refutation of k=11, L=95 (certifies h2(11)=570)

RQ1. Result: **`h2_cover_search_par 11 95` → INFEASIBLE, 13,867,370,405 nodes**, 29 min 47 s wall (2 threads, 58 m 45 s CPU),
2026-11-10 13:04–13:34 UTC. With EXP031/EXP030 (k=11, L=94 FEASIBLE, witness re-checked directly) this gives omega2(11)=94, i.e.
**h2(11)=6*94+6=570, matching Ziller–Morack Table 1**, under the same covering-model equivalence used for k<=10.

* Node growth k=10→11: 214,353,300 → 13,867,370,405 (x64.7), consistent with the earlier x30–50 trend, a little steeper.
* Binary: `03_CODE/h2_cover_search_par.cpp` as in branch `verify/h2-search-prime-table-fix` (commit af0ea91); for K<=13 identical in behaviour to main's version (the fix only extends the prime table).
* Validation of the parallel code: identical INFEASIBLE node counts to the sequential search for k=5..10 (EXP030/031 notes).

## Limits (read before citing)
* One implementation, one algorithm family; no independent re-run, no machine-checkable certificate. A bug in pruning would invalidate it; the k<=10 agreement with the source and with the independent EXP029 code is the main evidence.
* Rows k>=12 remain transcribed (k=12,13 lower-side runs timed out in EXP031).
* Extrapolating x65/step, k=12 L=118 would need ~1e12 nodes (~25–30 h on 2 threads): not feasible without better pruning.
* ID check: only `main` of the shallow clone was visible; renumber on merge if EXP032 collides.
