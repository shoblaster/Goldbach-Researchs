# EXP023 — paired-Jacobsthal bound: ratios, independent certification, Conjecture 4 check

Branch: `research/h2-ratio-frontier`. Question: RQ1 in `01_RESEARCH_QUESTIONS.md`.
Proof note: `08_PROOFS/PROOF_FRONTIER_022_H2_BOUND_AND_CONJECTURE4.md`.
Raw output: `RAW_OUTPUT.txt` (sections A, B, C1, C2; section D appended if the k=10 run finished).

## What was run
| Section | Command | Purpose |
|---|---|---|
| A | `h2_ratio_analysis.py` | exact-fraction ratios, margins, headroom `c_k` from the source table |
| B | `conjecture4_finite_check.py 20000000` | check the source's Conjecture 4 for all even `N` in `[12, 2e7]`; independent trial-division cross-check for `N <= 1e5`; `k_n` ranges; window depth |
| C1 | `h2_frontier_verify.py highs 3 4 5 6 7 8` | second-solver certification of `h2(k)` |
| C2 | `h2_frontier_verify.py cpsat 3 4 5 6 7 8 9` | certify `h2(k) = H` via `L = (H-6)/6` feasible and `L+1` infeasible, with direct witness re-check |

## Results (all from `RAW_OUTPUT.txt`)
* `h2(k)` for `k = 3..9` equals the source value under both CP-SAT (`k <= 9`) and HiGHS (`k <= 8`),
  every feasible witness re-checked directly. This agrees with EXP017.
* Source bound `h2(k) < p_k^2 - p_k` holds on all 19 rows `k = 3..21` (rows `k >= 10` are **transcribed**
  from Table 1 of arXiv:1706.03668, not recomputed here).
* Tightest rows: `k = 6` ratio `25/26`, margin `6`. Headroom `c_k = (p^2 - h2)/p` has minimum `7/5` at `k = 3`.
* For `k >= 7` the ratio is at most `0.7544` and is not monotone.
* Conjecture 4: **0 failures** over all `9,999,995` even `N` in `[12, 2e7]`; independent check
  `N <= 100000`: 49,995 values, 0 failures. `k_n = 2` exactly for `12 <= N <= 29`.
* Least valid `q1` reaches at most `0.030 p_k^2` for `k = 20` and `0.0003 p_k^2` for `k = 600`.

## Interpretation and limits
Finite evidence only. Nothing here proves H (`h2(k) < p_k^2 - p_k` for all `k >= 3`), Conjecture 4, or
Strong Goldbach. The universal statement H is much stronger than what Conjecture 4 needs
(PROOF_FRONTIER_022 §5). **NOVELTY NOT ESTABLISHED.**
