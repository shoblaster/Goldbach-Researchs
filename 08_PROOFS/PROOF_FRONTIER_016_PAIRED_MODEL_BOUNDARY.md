# Proof frontier 016 — boundary between arbitrary-residue and paired models

**Status:** elementary definition-level relation; no novelty claim.  
**Date:** 2026-11-02

Let P_k be the primes through p_k. The Barca finite model chooses one
forbidden class modulo 2 and two distinct forbidden classes modulo every odd
prime. Call this family of choices A_k.

Fix an even integer d and a starting integer a. For a paired progression
(a+i, a+d+i), a prime p excludes an index i when

    i = -a (mod p) or i = -a-d (mod p).

If p does not divide d, these are two distinct classes for odd p; modulo 2
they coincide because d is even. Thus, when no odd p <= p_k divides d, the
paired progression induces a member of A_k. If an odd prime divides d, the two
classes coincide; adding any second forbidden class produces a member of A_k
whose survivor set is a subset of the paired survivor set.

Consequently, for every fixed paired progression and finite interval I,

    min_{F in A_k} |S(F; I)| <= |S_paired(a,d; I)|,

where S(F; I) is the set of indices avoiding all selected classes. This is
only a one-way comparison. The arbitrary model allows each pair of classes to
be chosen independently at each prime, while the paired model links them by a
single global difference d. Also, the paired-Jacobsthal function studied by
Ziller and Morack is a maximum-gap/translation quantity, not the survivor
count in one fixed interval [1,p_k^2].

Therefore the verified Ziller–Morack sources are close prior art, but the
EXP015 optimization is not declared equivalent to their h_2 values. Any claim
that the two problems are identical is **UNVERIFIED**. This boundary does not
imply a new theorem or a novelty result.
