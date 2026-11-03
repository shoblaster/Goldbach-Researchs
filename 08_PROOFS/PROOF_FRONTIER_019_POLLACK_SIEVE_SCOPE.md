# Proof frontier 019 — textbook sieve scope for arbitrary residue classes

**Status:** source-verified background and applicability boundary; no new
theorem claimed.
**Date:** 2026-11-03

Paul Pollack's *Not Always Buried Deep* presents a Brun-method exercise in
which, for each prime p, one chooses at most k residue classes and counts
integers avoiding all chosen classes. The displayed statements give upper and
lower bounds uniform in the particular residue choices when the sieving primes
are restricted to p <= x^B, with B depending on k. The accompanying remark
identifies the twin-prime classes as 0 and -2 and the Goldbach classes as 0 and
N modulo p.

This source has two consequences for our project:

1. Choosing bounded numbers of arbitrary residue classes is standard sieve
   structure, not by itself a novel algorithmic idea.
2. The fixed Goldbach residue classes are linked by one target N, whereas
   EXP015/EXP019 optimize over arbitrary independent choices.

The source's lower-bound exercise does **not** automatically settle our finite
boundary. In EXP015/EXP019, the interval length is x=p_k^2 and the largest
sieved prime is p_k=x^{1/2}. The textbook statement only asserts the existence
of some B(k)>0; this repository has not verified that B(k) reaches 1/2 for the
relevant two-class problem, nor that the exercise's asymptotic hypotheses apply
with this moving parameter. Therefore any direct application to the exact
finite minima would be **UNVERIFIED**.

The source is used as a literature and scope check, not as an independently
reproved theorem here. The finite model equivalence and EXP015/EXP019 results
remain exactly as recorded in their own proof and experiment files.
