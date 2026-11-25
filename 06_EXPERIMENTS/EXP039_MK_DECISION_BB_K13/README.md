# EXP039: M_13 = 16 by a decision branch and bound

**Question.** What is the exact fixed-window minimum M_13 (window [1, 41^2], one class removed mod 2, two classes mod each odd prime up to 41)?

**Method.** `03_CODE/mk_decision_bb.cpp` was written from scratch by an independent verifier (not copied from `mk_enum_bb.cpp`). For B = 0, 1, 2, ... it decides whether some choice of classes leaves at most B survivors. At each node every unassigned prime can remove at most `top_q` survivors (largest class count for 2, sum of the two largest for odd primes); a node is pruned when survivors minus the sum of these bounds exceeds B. It branches on the prime with the largest `top_q`, keeping only class pairs that can still reach B. The first feasible B is M_k, and the program recomputes the survivors of its witness directly from the definition. Environment variable `B0` sets the starting B (used to resume).

**Run in three parts** (the machine has 2 shared cores): `RAW_OUTPUT_k13_B0_to_11.txt` (B = 0..11), `..._B12_to_14.txt` (B = 12..14), `..._B15_to_16.txt` (B = 15, 16).

**Result.** B = 0..15 are all infeasible (the last, B = 15, took 503 s and 3.39e8 nodes); B = 16 is feasible. So **M_13 = 16**. Witness (survivors recomputed directly): 77 119 227 443 599 767 779 863 953 1163 1199 1337 1373 1397 1493 1667.

**Validation.** The same program reproduces M_3..M_10 (checked independently against CP-SAT and brute force by its author) and M_11 = 8, M_12 = 13 (0.3 s and 1.8 s), which agree with EXP033 (branch and bound and HiGHS MILP). An earlier HiGHS run on k = 13 stopped at a solution of 16 with a lower bound of about 7, which is consistent.

**Status.** FINITE COMPUTATION, ONE METHOD at k = 13 (no second solver has proved the lower bound). Both this and EXP033 use the same covering model. Novelty not established; a literature search found no table of M_k, but the OEIS full-sequence search could not be run.

**Sequence so far (k = 3..13):** 2, 2, 3, 2, 4, 4, 5, 10, 8, 13, 16. It is not monotone.
