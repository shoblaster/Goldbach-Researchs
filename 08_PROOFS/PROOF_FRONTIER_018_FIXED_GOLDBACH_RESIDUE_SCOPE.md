# Proof frontier 018 — fixed-Goldbach residues versus arbitrary MILP residues

**Status:** elementary correspondence proved; finite implementation check passed;
scope correction, not a new Goldbach theorem.
**Date:** 2026-11-03

## Two different residue models

For a fixed even target (N), the Goldbach-specific one-parameter sieve tests
an offset (n) through the pair ((n,N-n)). For each odd prime (p), the
forbidden classes are fixed:

    n = 0 (mod p)  or  n = N (mod p),

and the even class modulo 2 is also forbidden. These two classes are linked by
the single target (N).

EXP015/EXP019 instead minimize over all choices of one class modulo 2 and two
distinct classes modulo every odd prime. That is an arbitrary worst-case
covering problem. Its residue choices are not tied to one fixed Goldbach target.

## Elementary correspondence for the fixed target

Let (N) be even and (3\le n\le N-3). Remove even (n), and remove (n) if
for some prime (p) with (p^2<N), either (p\mid n) or (p\mid(N-n)).

If (n) survives, then neither (n) nor (N-n) has a prime divisor below
(sqrt N). Since both numbers are positive and strictly below (N), a
composite one would have a prime divisor at most its own square root, hence
strictly below (sqrt N). Therefore both (n) and (N-n) are primes greater
than (sqrt N).

Conversely, if (n) and (N-n) are primes greater than (sqrt N), neither is
divisible by a prime (p) with (p^2<N), and (n) is odd because (N) is even.
Thus the survivors are exactly the ordered offsets of prime pairs

    N = p + q,  p,q > sqrt(N).

This is a finite identity, not a proof that such a pair exists for every (N).
The condition “for every sufficiently large even (N), such a pair exists” is
a stronger Goldbach-type statement, not the arbitrary-residue minimization in
EXP015.

## Independent finite check

`03_CODE/goldbach_fixed_residue_mapping_check.py` checked the identity for every
even (N) from 6 through 10,000. It found no mismatch. The raw output is in
`06_EXPERIMENTS/EXP020_FIXED_GOLDBACH_RESIDUE_MAPPING/RAW_OUTPUT.txt`.

The check is supporting evidence only; the elementary argument above is the
reason for the correspondence. The MathOverflow discussion recorded in CIT-035
was used as a literature lead and scope comparison, not as a proof authority.

## Research consequence

The arbitrary-residue minima are useful for auditing claims that infer a
uniform interval lower bound from a complete-period density. They should not be
described as direct Goldbach representation counts. The fixed-(N) residue
pattern is structurally constrained, and a theorem guaranteeing a survivor for
every (N) would itself be a major Goldbach-type result.

Status: **NOVELTY NOT ESTABLISHED**; **PROOF GAP — NOT PROVED** for any
unbounded Goldbach conclusion.
