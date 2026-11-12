# EXP033 — greedy child ordering in the h2 cover search: negligible effect (negative result)

RQ1. Idea (from the unpaired literature, CIT-045): try the prime whose class q%p covers most uncovered positions first.
Variant: `03_CODE/h2_cover_search_greedy_order.cpp` (insertion-sorts the children by gain). Single thread, 2026-11-12.

| k, L (feasible) | baseline nodes | greedy-order nodes |
|---|---:|---:|
| 9, 60 | 435,160 | 435,142 |
| 10, 74 | 363,132 | 363,108 |
| 11, 94 | 2,521,728 | 2,306,876 (-8.5%) |

Witnesses verified directly in all cases. All three runs take <1 s either way.

**Conclusion.** Child order cannot change the *infeasible* search: the pruning bound is evaluated at node entry and does not depend on sibling
order, so an exhaustive refutation visits exactly the same set of nodes. And the feasible side is already cheap. Greedy ordering therefore does
not help the real bottleneck (k=11 refutation: 1.39e10 nodes; k=12 extrapolated ~1e12). Gains must come from a stronger bound or from symmetry/dominance
pruning — untested.

Limits: three instances, one machine; not run on k=12/13 feasible side (timed out in EXP031 with the baseline, which this does not address).
ID check: only `main` was visible; renumber on merge if EXP033 collides.
