# Proof frontier 016 — corrected boundary between arbitrary-residue and paired models

**Status:** corrected elementary definition-level relation; no novelty claim.
**Date:** 2026-11-02

Let P_k be the primes through p_k. The Barca finite model chooses one
forbidden class modulo 2 and two distinct forbidden classes modulo every odd
prime. Call this family of choices A_k.

Fix integers a,b with even difference. For the paired progression
(a+i,b+i), a prime p excludes an index i when

    i = -a (mod p) or i = -b (mod p).

If p does not divide b-a, these are two distinct classes for odd p; modulo 2
they coincide because b-a is even. Conversely, given arbitrary residue pairs
(r_p,s_p) at the primes, the Chinese remainder theorem produces a and b
satisfying a=-r_p and b=-s_p modulo every p. Thus every arbitrary two-class
selection with distinct odd-prime classes is induced by a paired progression.
This is the key point made explicitly in the Ziller–Morack ancillary algorithm
note (their Proposition 1.5, for the condensed odd-prime formulation).

If an odd prime divides b-a, the two paired classes coincide. Choosing any
second distinct forbidden class at that prime can only decrease the finite
survivor set. Therefore, when minimizing a survivor count over a fixed finite
interval, allowing coincident paired classes cannot produce a smaller minimum
than the distinct-class model: a coincident choice can be refined by adding a
class.

Consequently, the finite minimum over A_k agrees with the minimum over paired
residue assignments for the same fixed interval. It is **not**, however,
identical to the paired-Jacobsthal function h_2: h_2 is a maximum-gap /
translation quantity (the least length guaranteeing a survivor for every
paired progression), whereas EXP015 minimizes the number of survivors in one
fixed interval [1,p_k^2].

Therefore the verified Ziller–Morack ancillary algorithms are directly
relevant prior art for the residue-selection model. EXP015 is not claimed to
reproduce their h_2 table, and no novelty claim is made. Any stronger claim
about priority or published equivalence of the exact fixed-window minima is
**UNVERIFIED**.
