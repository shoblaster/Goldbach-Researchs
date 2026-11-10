# EXP031 — feasibility (lower-bound) witnesses for transcribed rows k = 11..14

Branch: `verify/h2-lower-bounds`. RQ1. Question: can the *feasible* side of the transcribed `h2(k)` rows be
re-checked cheaply? A feasible `L = omega2(k)` witness shows `h2(k) >= 6*omega2+6` only if the covering-model
equivalence holds; it says nothing about the infeasible side (`L+1`), which is the expensive half.

| k | L = omega2 | result (240 s, 1 thread) | note |
|---:|---:|---|---|
| 11 | 94 | **FEASIBLE**, 2,521,728 nodes, direct witness check True | agrees with EXP030 lower bound |
| 12 | 117 | no result (timeout) | not a negative finding |
| 13 | 148 | no result (timeout) | not a negative finding |
| 14 | 173 | crashed: `std::bad_alloc` | **cause found 2026-11-10: the code's prime table stopped at p_13=41, so K>=14 read out of bounds** (fixed on branch `verify/h2-search-prime-table-fix`); k=14 was never actually searched |

Witness for k=11 is in `RAW_OUTPUT.txt`.

## Limits
* Only k=11 is newly (re)confirmed on the lower side; k=12..14 remain transcribed.
* The infeasible side for k >= 11 is still open (k=11, L=95: no result in two runs).
* The k=14 crash was a code bug (prime table), not a memory limit; after the fix k=14 L=173 runs but gave no result in 60 s. k<=13 runs were unaffected.
* ID check: only the shallow clone's `main` could be inspected, so EXP031 may collide with another branch; renumber on merge if so.
