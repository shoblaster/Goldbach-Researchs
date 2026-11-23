# EXP038 — "independent-set" pruning bound: sound but only ~6% fewer nodes (negative result)

RQ1. Follow-up to EXP037, which showed the sum-of-best-gains bound is nearly tight at surviving nodes and loose only through overlaps between primes.
Idea tested (`03_CODE/h2_cover_search_indep.cpp`): at each node, greedily pick uncovered positions that pairwise cannot share any still-available
(prime, residue) class (no prime p with quota left, p | difference, and q % p != 0). Each such position needs its own new class, so if the set is larger
than the total remaining quota Q = sum(2 - classes chosen), no completion exists, and the node is pruned. Soundness: a class (p, r) can cover two positions
only if p divides their difference, so pairwise-unshareable positions need distinct classes; at most Q new classes can still be added.

| k, L (infeasible) | base nodes | with bound | change | base time | time with bound |
|---|---:|---:|---:|---:|---:|
| 7, 32 | 4,175 | 3,729 | -10.7% | ~0 | ~0 |
| 8, 43 | 120,324 | 110,936 | -7.8% | 0.02 s | 0.03 s |
| 9, 61 | 4,194,640 | 3,929,264 | -6.3% | 0.67 s | 1.3 s |
| 10, 75 | 214,353,300 | 201,557,737 | -6.0% | 41 s | 78 s |

The feasible runs (k=7, 8, 9) find witnesses that pass the direct check, and every feasible/infeasible verdict is unchanged.

**Conclusion.** The bound is valid and removes only about 6% of nodes at k = 10 (the saving shrinks as k grows), while roughly doubling the time per run. It does not help
k = 12, which still needs about 1e12 nodes. The overlap structure is not captured by this simple pairwise-independence argument. Possible stronger relaxations
(a cover-number lower bound using more than pairwise independence, or reasoning with the two lowest classes together) are untested.

Limits: one machine, single thread, four infeasible instances; the greedy independent set is not optimal, so a better choice of set could prune more.
