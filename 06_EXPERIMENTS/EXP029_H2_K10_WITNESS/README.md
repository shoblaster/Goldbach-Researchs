# EXP029: attempt to certify h2(10) = 450 with CP-SAT

Branch: `verify/h2-k10-witness`. Question: RQ1 in `01_RESEARCH_QUESTIONS.md`.
Script: `03_CODE/h2_frontier_verify.py` (unchanged, from EXP023). Raw output: `RAW_OUTPUT.txt`.

EXP023 certified h2(k) for k = 3..9. Rows k >= 10 of the source table (arXiv:1706.03668, Table 1) were only transcribed. This run applies the same method to k = 10: h2(10) = 450 means omega2 = (450 - 6) / 6 = 74, so the positions 1..74 must be coverable by two nonzero residues per prime in {5, ..., 29}, and 1..75 must not be.

## Result (from `RAW_OUTPUT.txt`)
| Half | Statement | CP-SAT status | Meaning |
|---|---|---|---|
| L = 74 | a covering choice exists | FEASIBLE, witness re-checked directly: True | h2(10) >= 450 is **confirmed** |
| L = 75 | no covering choice exists | UNKNOWN after 1500 s | the upper bound h2(10) <= 450 is **not** certified |

`certified False` in the output means exactly this: one half done, one half unresolved within the time limit. It is not evidence that the source value is wrong.

## Interpretation and limits
- Only the lower bound h2(10) >= 450 is established here (a verified witness). The source value could still be too small if a covering of 1..75 existed; nothing in this run rules that out.
- CP-SAT did not prove infeasibility in 1500 s on a 2-core machine, as it also failed to give a lower bound for the fixed-window problem at k >= 7 in EXP024. A different method (exact enumeration with symmetry reduction, as used in EXP024) is the natural next attempt for the infeasible half.
- Finite computation only. It says nothing about the universal bound H, Conjecture 4, or Strong Goldbach. NOVELTY NOT ESTABLISHED.
