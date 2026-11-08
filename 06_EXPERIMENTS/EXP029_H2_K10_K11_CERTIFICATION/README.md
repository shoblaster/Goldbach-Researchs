# EXP029: h2(11) = 570 certified; second implementation for k <= 10

Branch: `verify/h2-k10-witness`. Question: RQ1 in `01_RESEARCH_QUESTIONS.md`.
Code: `03_CODE/h2_exact_dfs.cpp` (new, no solver library, optional work splitting).
Raw outputs: `RAW_OUTPUT_dfs_validation.txt` (k = 3..9), `RAW_OUTPUT_dfs_k10.txt`, `RAW_OUTPUT_dfs_k11.txt`,
`RAW_OUTPUT_split_check.txt`, `RAW_OUTPUT_cpsat.txt` (CP-SAT at k = 10: lower bound only, UNKNOWN at 75 after 1500 s).

## Relation to EXP030
EXP030 (`03_CODE/h2_cover_search.cpp`, merged) certifies h2(k) for k = 3..10 with the same covering model and the same
algorithm (branch on the lowest uncovered position, prune by best remaining coverage). This experiment began as a separate
attempt at k = 10 and agrees with EXP030 on all 16 shared runs (verdict and node count; see EXP030 README). Read the two as
one certification of k <= 10 with two implementations. The new result here is k = 11.

## k = 11 result
Primes {5, 7, ..., 31}, source value h2(11) = 570, so omega2(11) = (570 - 6) / 6 = 94.
- L = 94: FEASIBLE, witness re-checked directly (2,521,728 nodes). `RAW_OUTPUT_dfs_k11.txt`.
- L = 95: INFEASIBLE. The search was split into two shares (`H2_SPLIT_M=2`, `H2_SPLIT_R=0` and `1`), each about 50 minutes on one
  core: 6,905,350,180 and 6,962,027,300 nodes, 13,867,377,480 in total, both INFEASIBLE. EXP030 stopped its k = 11 run at 2700 s with no result.
- So omega2(11) = 94 and h2(11) = 6 * 94 + 6 = 570, matching the source table.

Split mode: each process explores only the depth-4 subtrees whose index modulo m equals its share number. A claim of INFEASIBLE
needs every share to say INFEASIBLE. Validation (`RAW_OUTPUT_split_check.txt`): 10 split runs on cases with known verdicts
(k = 8, 9, 10; m = 2 and 3) all combine to the known verdict. Node totals of the two k = 10 shares (107,201,275 + 107,156,466) exceed
the unsplit 214,353,300 by 4,441, the shared nodes above the cut, as expected.

## Interpretation and limits
- The L = 95 infeasibility is an exhaustive-search output, not an independently checkable certificate. It uses the same algorithm as EXP030, and the k = 11 run has only one implementation (the k = 11 run of EXP030 timed out), so a flaw in the algorithm's reasoning would not be caught.
- The k = 11 shares ran on a build with the splitting code; the L = 94 witness came from an earlier build with identical search logic. Both are recorded in the raw output.
- The covering model is the one in EXP023. The identity h2(k) = 6 * omega2(k) + 6 is used as cited, not re-derived.
- Rows k >= 12 remain transcribed. Node counts grow about 30 to 65 times per k (214 million at k = 10, about 13.9 billion at k = 11), so k = 12 needs stronger pruning.
- Finite computation only. It says nothing about the universal bound H, Conjecture 4, or Strong Goldbach. NOVELTY NOT ESTABLISHED.
