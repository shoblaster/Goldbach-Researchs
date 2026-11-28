# EXP039: M_13 = 16 by a decision branch and bound

**Question.** What is the exact fixed-window minimum M_13 (window [1, 41^2], one class removed mod 2, two classes mod each odd prime up to 41)?

**Method.** `03_CODE/mk_decision_bb.cpp` was written from scratch by an independent verifier (not copied from `mk_enum_bb.cpp`). For B = 0, 1, 2, ... it decides whether some choice of classes leaves at most B survivors. At each node every unassigned prime can remove at most `top_q` survivors (largest class count for 2, sum of the two largest for odd primes); a node is pruned when survivors minus the sum of these bounds exceeds B. It branches on the prime with the largest `top_q`, keeping only class pairs that can still reach B. The first feasible B is M_k, and the program recomputes the survivors of its witness directly from the definition. Environment variable `B0` sets the starting B (used to resume).

**Run in three parts** (the machine has 2 shared cores): `RAW_OUTPUT_k13_B0_to_11.txt` (B = 0..11), `..._B12_to_14.txt` (B = 12..14), `..._B15_to_16.txt` (B = 15, 16).

**Result.** B = 0..15 are all infeasible (the last, B = 15, took 503 s and 3.39e8 nodes); B = 16 is feasible. So **M_13 = 16**. Witness (survivors recomputed directly): 77 119 227 443 599 767 779 863 953 1163 1199 1337 1373 1397 1493 1667.

**Validation.** The same program reproduces M_3..M_10 (checked independently against CP-SAT and brute force by its author) and M_11 = 8, M_12 = 13 (0.3 s and 1.8 s), which agree with EXP033 (branch and bound and HiGHS MILP). An earlier HiGHS run on k = 13 stopped at a solution of 16 with a lower bound of about 7, which is consistent.

**Status.** FINITE COMPUTATION, ONE METHOD at k = 13 (no second solver has proved the lower bound). Both this and EXP033 use the same covering model. Novelty not established; a literature search found no table of M_k, but the OEIS full-sequence search could not be run.

**Sequence so far (k = 3..13):** 2, 2, 3, 2, 4, 4, 5, 10, 8, 13, 16. It is not monotone.

## Addendum (27 Nov 2026): second implementation of k = 13, and k = 14 bounds

**M_13 = 16, second implementation.** `03_CODE/mk_exhaustive_second_impl.cpp` was written independently of `mk_decision_bb.cpp` (different branching rule: fewest viable class pairs; extra pair-viability cut; reflection n -> N+1-n used only at q = 3). It proved no choice leaves 15 or fewer survivors (184,070,270 nodes, 1181 s, `RAW_OUTPUT_k13_B15_second_impl.txt`) and reproduces M_9..M_12 = 5, 10, 8, 13. Both implementations use the same pruning *family* (a prime removes at most its top-two class counts), so this is two codes of one technique, not two techniques. A SAT or MILP proof of the k = 13 lower bound is still open. The 16-survivor witness from the first run was recounted directly; the second implementation's witness was recounted again here and also leaves 16.

**k = 14 (p = 43, window 1849).**
* Upper bound **M_14 <= 14**, from simulated annealing (`03_CODE/mk_anneal_upper_bound.cpp`, witness in `RAW_OUTPUT_k14_anneal_witness.txt`). Survivors 261 279 321 339 369 435 1269 1275 1329 1461 1605 1725 1809 1839; recounted directly from the definition, 14 survivors. The annealer returned the proved value 16 at k = 13, but was run once at k = 14, so 14 may not be optimal.
* Lower bound **M_14 >= 12**: B = 0..11 proved infeasible by `03_CODE/mk_decision_bb_reflect.cpp` (the decision search with a root reflection symmetry and static buffers, about 1.7x faster; validated on k = 9..12). Largest case B = 11: 2.795e8 nodes, 532 s (`RAW_OUTPUT_k14_lower_bound_B0_to_11.txt`).
* At that point 12 <= M_14 <= 14; see Addendum 2 for the final value.

## Addendum 2 (29 Nov 2026): M_14 = 14

`mk_decision_bb_reflect.cpp` proved B = 12 infeasible for k = 14 (5.17e8 nodes, 913 s, `RAW_OUTPUT_k14_B12.txt`) and B = 13 infeasible in two root-option ranges covering all 3 root options: [0,1) 5.26e8 nodes, 889 s, and [1,3) 5.06e8 nodes, 857 s (`RAW_OUTPUT_k14_B13_root0.txt`, `..._root1_2.txt`). Together with B = 0..11 (earlier addendum) every B <= 13 is infeasible, and the annealing witness leaves exactly 14 survivors (recounted directly). Hence **M_14 = 14**.

Status: FINITE COMPUTATION, ONE IMPLEMENTATION at k = 14 (the reflection-symmetry decision search; the independent second code `mk_exhaustive_second_impl.cpp` was not run at k = 14 and would need hours). The same code reproduces M_9..M_12 and agrees with the other two codes at k = 13. Same covering model and pruning family as above. Novelty not established.

Sequence for k = 3..14: 2, 2, 3, 2, 4, 4, 5, 10, 8, 13, 16, 14.
