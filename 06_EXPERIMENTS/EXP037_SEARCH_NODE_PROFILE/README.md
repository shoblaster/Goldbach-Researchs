# EXP037 — where the search spends its nodes (k=8 L=43 and k=9 L=61, infeasible runs)

RQ1. Diagnostic only, to decide where a stronger pruning rule could help. `03_CODE/h2_cover_search_profile.cpp` is the unchanged sequential
search plus counters (nodes per depth = number of classes already chosen; nodes pruned by the bound; histogram of slack = bound − |uncovered| at
nodes that survive the bound). Its total node counts equal the uninstrumented search (120,324 at k=8; 4,194,640 at k=9), so the counters do not change the tree.

## k = 9, L = 61 (4,194,640 nodes)
* Pruned by the bound: 3,227,646 (77%); surviving (expanded) nodes: 966,994.
* Depth: 3,804,378 nodes (90.7%) are at depth >= 8, and 82.6% of those (3,140,494) are pruned at once. At depth <= 6 only about 0-10% of nodes are pruned (e.g. depth 6: 6,837 of 68,553).
* Slack of surviving nodes: 453,337 (46.9%) have slack 0; 878,810 (90.9%) have slack <= 3. k = 8 shows the same shape (15,966 of 32,000-ish survivors at slack 0).

## What the data show, and what they do not
* Most work is in a thick band of depths 7-10 where nodes are generated and die immediately. A pruning rule that fires at depths 5-7 would remove whole subtrees; a rule that only trims children at depth >= 8 would not change the count much.
* At the nodes that survive, the bound is almost tight (slack 0-3), so the loose part of the bound is not "how many positions each prime can gain" but the overlap between primes, which the sum ignores. Any improvement likely has to reason about overlaps (for example, positions that only large primes can still cover, or pairs of primes competing for the same positions).
* Untested ideas (nothing here is a result): (a) a bound on the lowest few uncovered positions using the primes that can reach them; (b) a canonical-form or dominance rule among the choices at the same depth; (c) processing the primes in a different order inside the bound. None has been implemented.
* Limits: two instances, one machine; depth is "classes chosen", not search-tree height in positions.
