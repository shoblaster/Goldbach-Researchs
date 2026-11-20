# EXP036 — bound-free exhaustive brute force of omega2(k): k = 3..9

RQ1. The earlier searches (EXP022, EXP030, EXP035) all prune with the same idea: "each prime can still gain at most its two best classes".
This experiment uses **no pruning and no bound**: it enumerates every choice of two nonzero residues modulo each prime 5..p_k
(product of C(p-1,2) leaves, checked against the leaf counter) and records the longest fully covered prefix.
Code: `03_CODE/h2_bruteforce_omega2.cpp` (u64 position masks, valid for omega2 < 64, i.e. k <= 9).

| k | omega2 (brute force) | h2 = 6*omega2+6 | leaves enumerated | = prod C(p-1,2)? | source h2 |
|---:|---:|---:|---:|:--:|---:|
| 3 | 2 | 18 | 6 | yes | 18 |
| 4 | 4 | 30 | 90 | yes | 30 |
| 5 | 10 | 66 | 4,050 | yes | 66 |
| 6 | 24 | 150 | 267,300 | yes | 150 |
| 7 | 31 | 192 | 32,076,000 | yes | 192 |
| 8 | 42 | 258 | 4,907,628,000 | yes | 258 |
| 9 | 60 | 366 | 1,133,662,068,000 | yes | 366 |

**Result.** For k = 3..9 the brute-force omega2 equals the value found by the pruned searches and the published table, with no
dependence on any bound, ordering or solver. This closes the "common bound" caveat for k <= 9 (same covering model, so it does not test the
model-to-h2 equivalence taken from the source).

**k = 9.** 1.13e12 leaves enumerated in 21 min 11 s on 2 threads (a first background run was killed with no result when the session paused; a foreground attempt exceeded 10 min and was stopped). omega2(9) = 60, h2(9) = 366, matching the pruned searches and the source.
**k >= 10** needs 128-bit masks and about 4.7e14 leaves for k = 10 (roughly a day and a half or more on this machine), so it is out of reach for brute force.

Limits: same covering model as all other experiments; one implementation; leaf counter verifies the enumeration size, not the mask logic (witness
logic is the same as in the other programs' direct checks for the feasible cases).
