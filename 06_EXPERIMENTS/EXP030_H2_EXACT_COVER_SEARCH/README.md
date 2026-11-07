# EXP030 — exact solver-free certification of the paired-Jacobsthal values h2(k), k = 3..10

Branch: `verify/h2-exact-cover-search`. Question: RQ1 in `01_RESEARCH_QUESTIONS.md`.
Closes the item left open by EXP023 (CP-SAT: `L+1 = 75` UNKNOWN after 1800 s for k = 10) and by EXP029
(h2(10) = 450 lower bound only; infeasibility at 75 unresolved). Raw output: `RAW_OUTPUT.txt`.

## Method (`03_CODE/h2_cover_search.cpp`)
Same covering model as `h2_frontier_verify.py`: for each prime `p` in `{5..p_k}` choose exactly two nonzero residues;
position `q` is covered by `p` iff `q mod p` is a chosen residue. Exhaustive depth-first search that always branches on
the lowest uncovered position (some prime with quota left must cover it), pruned by an exact upper bound on what the
remaining quotas can still cover (best `t_p` classes among currently uncovered positions). A finished search with no
complete cover is a proof of infeasibility, relying on the code's correctness. No solver, no shared code with EXP023.

## Results (from `RAW_OUTPUT.txt`)
For each `k`, `L = omega2 = (H-6)/6` is FEASIBLE (witness re-checked directly from the definition) and `L+1` is
INFEASIBLE, where `H` is the transcribed Ziller–Morack Table 1 value:

| k | p_k | H = h2(k) | omega2 | INFEASIBLE nodes at omega2+1 |
|---:|---:|---:|---:|---:|
| 3 | 5 | 18 | 2 | 1 |
| 4 | 7 | 30 | 4 | 1 |
| 5 | 11 | 66 | 10 | 10 |
| 6 | 13 | 150 | 24 | 88 |
| 7 | 17 | 192 | 31 | 4,175 |
| 8 | 19 | 258 | 42 | 120,324 |
| 9 | 23 | 366 | 60 | 4,194,640 |
| 10 | 29 | 450 | 74 | 214,353,300 (51 s) |

* **h2(10) = 450 is now independently certified**, matching the source and the lower bound of EXP023/EXP029.
  The hypothesis `h2(k) < p_k^2 - p_k` therefore rests on recomputed values for `k <= 10` (at `k = 10`: `450 < 812`).
* The method reproduces every `k <= 9` value already certified by CP-SAT/HiGHS, which is the validation of the code.
  The k = 9 infeasibility proof takes 1 s here versus about 60 s for CP-SAT.
* **k = 11 (section D of `RAW_OUTPUT.txt`):** `L = 94` is FEASIBLE with a directly verified witness, so
  `h2(11) >= 570`. The infeasibility run at `L = 95` was stopped by a 2700 s limit and has **no result**; `h2(11) = 570`
  is therefore not certified. Rows `k >= 11` of the source table remain **transcribed**, not recomputed.

## Limits
Finite computation only. The infeasibility proofs are exhaustive-search outputs, not independently checkable
certificates. Node counts grow roughly 30–50x per k, so k >= 12 is likely out of reach of this single-thread search
without further pruning. Nothing here proves the bound for all k, Conjecture 4, or Strong Goldbach.
**NOVELTY NOT ESTABLISHED.**
