# EXP035 — second, structurally different exact method (prime-first): agrees for k = 3..9

RQ1. Limitation (2) of the paper: both earlier k=10/11 implementations shared the same algorithm (branch on the lowest uncovered position).
Method B (`03_CODE/h2_cover_search_primefirst.cpp`) instead processes the primes in descending order and enumerates the *pair* of
residues at each prime, with a sum-of-best-gains bound for the primes still to come. It does not share method A's search tree.

| k | L (feasible = omega2) | L+1 (infeasible) | method B nodes (feas / infeas) | method A nodes (infeas) |
|---:|---:|---:|---|---:|
| 3 | 2 | 3 | 2 / 1 | 1 |
| 4 | 4 | 5 | 3 / 1 | 1 |
| 5 | 10 | 11 | 62 / 107 | 10 |
| 6 | 24 | 25 | 1,328 / 1,941 | 88 |
| 7 | 31 | 32 | 134,943 / 298,327 | 4,175 |
| 8 | 42 | 43 | 9,213,408 / 36,968,104 | 120,324 |
| 9 | 60 | 61 | 2,813,820,734 / 5,943,763,545 | 4,194,640 |

All feasible runs pass the direct witness check. Every (feasible, infeasible) pair reproduces omega2(k) and therefore
h2(k) = 6*omega2+6 for k = 3..9 (source values 18, 30, 66, 150, 192, 258, 366), now by two methods with different search trees.

**Cost.** Method B is 3 orders of magnitude worse than A at k=9 (about 1,400x more nodes at k=9), roughly 15 min on one core each for the two k=9 runs. Extrapolating the observed growth (x~124-480 per step), k=10 would take days, so method B cannot independently re-run k=10 or k=11.

## What this does and does not show
* Shows: for k <= 9 the published values are reproduced by two algorithms with different trees (plus earlier solver checks), so a logic bug specific to A's lowest-uncovered branching is unlikely to affect those rows.
* Does not show: any independent confirmation of k=10 or k=11 (k=10 also has the other account's EXP029 code, same algorithm family as A; k=11 has only A).
* Both methods use the same bound idea (sum of best two classes per prime), so a flaw in that bound would not be caught. The bound is a valid upper bound by construction (no more than the two best classes can be gained per prime), but this has not been formally proved here.
* Runs used 2 single-thread jobs concurrently on one machine.
