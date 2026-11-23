# PROOF_FRONTIER_024 — soundness of the pruned search (branching rule and bound)

Status: elementary argument written out and spot-tested; **not machine-checked**. It supports the claim that a completed
INFEASIBLE run of `03_CODE/h2_cover_search.cpp` (and `_par`) proves infeasibility *in the stated covering model*. It says nothing
about the model-to-h2 equivalence taken from Ziller–Morack.

**Model.** Primes p in {5,..,p_k}. A choice assigns to each p a set S_p of at most two residues in {1,..,p-1}. Position q in {1..L} is covered
iff q % p lies in S_p for some p. Question: is there a choice covering all of 1..L? (Choosing fewer than two residues is never better, so
"at most two" and "exactly two" give the same answer.)

**Lemma 1 (branching is exhaustive).** Let a partial choice leave q the lowest uncovered position. In any completion that covers all positions,
q is covered by some prime p with q % p = r != 0 and r in the final S_p. Since q is not covered now, r was not yet in S_p, so p still has
quota (|S_p| < 2). Hence every completion is found in the subtree that adds r = q % p to S_p for one such p (primes with q % p = 0 can never cover q and are skipped).
*Proof.* Immediate from the definition of covering. Every full cover is therefore reached on some root-to-leaf path; if the search exhausts all
branches without reaching total = 0, no cover exists. ∎

**Lemma 2 (bound is an upper bound).** Let U be the set of uncovered positions and, for each prime p with remaining quota t_p, let
g_p(r) = |{q in U : q % p = r}| for residues r not yet in S_p. Then the number of positions of U that any completion can still cover is at most
B = sum over p of (the sum of the t_p largest values g_p(r)).
*Proof.* The classes {q : q % p = r}, r = 1..p-1, are pairwise disjoint, so prime p with newly chosen set R (|R| <= t_p) covers exactly
sum_{r in R} g_p(r) positions of U, at most the sum of the t_p largest g_p values. The union over all primes covers at most the sum of the
individual counts. ∎ The search prunes a node when B < |U|, which is therefore safe.

**Randomised check.** `03_CODE/bound_soundness_test.py 400 7`: 400 random partial states on small instances (k = 3..6, L in {10,16,24,30});
the true maximum extra coverage by full enumeration never exceeded B (0 violations; equality in 259 cases, so the bound is often tight). This
is a sanity check of the implementation idea, not a substitute for Lemma 2.

**Not covered here.** (i) That the C++ code implements the lemmas correctly: the evidence is agreement with the bound-free brute force (EXP036) for
k <= 9, with the prime-first method (EXP035) for k <= 9, and with the independent code of EXP029 at k = 10. (ii) The k = 11 run has no independent re-run.
(iii) The parallel variant: its infeasible node counts equal the sequential ones for k = 5..10.
