# EXP029: certification of h2(10) = 450

Branch: `verify/h2-k10-witness`. Question: RQ1 in `01_RESEARCH_QUESTIONS.md`.
Code: `03_CODE/h2_exact_dfs.cpp` (new, no solver library), `03_CODE/h2_frontier_verify.py` (CP-SAT, from EXP023).
Raw outputs: `RAW_OUTPUT_cpsat.txt`, `RAW_OUTPUT_dfs_validation.txt`, `RAW_OUTPUT_dfs_k10.txt`.

EXP023 certified the paired-Jacobsthal values h2(k) for k = 3..9. The source table (arXiv:1706.03668, Table 1) rows for k >= 10 were only transcribed. This experiment certifies the k = 10 row: h2(10) = 450, that is omega2(10) = (450 - 6) / 6 = 74. The statement to certify is that positions 1..74 can be covered by choosing two nonzero residues per prime in {5, 7, 11, 13, 17, 19, 23, 29} and positions 1..75 cannot.

## Methods
1. CP-SAT (EXP023 script): found and directly re-checked a covering of 1..74. It returned UNKNOWN for 1..75 after 1500 s, so on its own it did not certify the upper bound.
2. Exact depth-first search (`h2_exact_dfs.cpp`, new): take the smallest uncovered position q, branch over every prime p with q % p != 0 and a free slot (that prime must choose residue q % p), and prune when the free slots cannot cover the uncovered positions even in the best case. This is complete: every covering is found because the smallest uncovered position must be covered by some prime.

## Results
- Validation first: the DFS reproduces every EXP023-certified value for k = 3..9 (feasible at omega2, infeasible at omega2 + 1; 14 checks, about 1.4 s). `RAW_OUTPUT_dfs_validation.txt`.
- k = 10, L = 74: FEASIBLE, witness re-checked directly, 363,132 nodes.
- k = 10, L = 75: INFEASIBLE, 214,353,300 nodes, about 62 s on one thread.
- Together: omega2(10) = 74, so h2(10) = 6 * 74 + 6 = 450, matching the source table.
- Witness for L = 74: 5:{1,4} 7:{1,2} 11:{3,5} 13:{3,7} 17:{1,11} 19:{10,13} 23:{12,17} 29:{15,24}.

## Interpretation and limits
- The infeasibility at 75 rests on the exhaustive search being correct. It is validated on 14 cases with known answers from an independent CP-SAT/HiGHS certification; it has not been cross-checked at k = 10 by a second solver (CP-SAT timed out).
- The search covers the model as stated in EXP023 (two nonzero residues per prime from 5 to p_k; q covered when q % p is chosen and nonzero). It does not check the translation from that model to h2(k) beyond the cited identity h2(k) = 6 * omega2(k) + 6.
- Finite computation only. It says nothing about the universal bound H, Conjecture 4, or Strong Goldbach. NOVELTY NOT ESTABLISHED.
