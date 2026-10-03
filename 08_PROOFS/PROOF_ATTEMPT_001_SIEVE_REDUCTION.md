# Proof attempt 001 — sieve reduction for Strong Goldbach

**Status: PROOF GAP — NOT PROVED.**

## Target statement

For every even integer `E > 2`, there are primes `p,q` with `E=p+q`.

## Definitions

Fix an even integer `E >= 4`. For an odd prime `p <= E/2`, call `p` a *surviving candidate* if both `p` and `E-p` are not divisible by any prime at most a chosen bound `B`.

If a surviving candidate additionally satisfies

```
p > B^2  and  E-p > B^2,
```

then the condition “not divisible by any prime at most `B`” alone does **not** show that either number is prime. A composite number can have every prime factor greater than `B`.

## Rigorous elementary observations

1. A Goldbach representation corresponds exactly to a prime `p <= E/2` for which `E-p` is prime.
2. For each fixed prime `r`, sieving candidates by `r` removes at most two residue classes modulo `r`: `p ≡ 0 (mod r)` and `p ≡ E (mod r)`. If `r | E`, these two classes coincide.
3. Removing residue classes for finitely many primes can be computed exactly using residue arithmetic (or inclusion–exclusion). It determines candidates free of those *small* prime divisors only.

These statements do not require a claim about the distribution of primes.

## Attempted route

The intended route was:

1. Sieve the possible `p` values by all small primes `r <= B`.
2. Prove that at least one candidate remains.
3. Conclude that the remaining `p` and `E-p` are prime.

## Exact obstruction

Step 3 is invalid unless the sieve bound is strong enough to certify primality of **both** values. A trial-division certificate for an integer `m` requires testing all prime divisors up to `sqrt(m)`, not merely a fixed smaller bound `B`.

Taking `B >= sqrt(E)` would make the sieve a primality test for both `p` and `E-p`, but then Step 2 is precisely the unresolved existence problem: proving a survivor is equivalent to producing a Goldbach representation. Thus this formulation does not reduce the mathematical difficulty.

## Proof gap

**PROOF GAP — NOT PROVED:** No valid argument has been supplied that guarantees a surviving candidate after a sieve strong enough to certify both addends as prime for every even `E`.

The finite EXP005 computation does not close this gap: it only checks `E <= 100000` in one bounded range.

## What would be needed

A valid proof would need a rigorously established lower bound for the number of simultaneous prime pairs `p, E-p` that is positive for every relevant `E`; a small-prime residue count alone does not provide it.

## Literature status

CIT-006 records a directly inspected source that describes the Strong Goldbach conjecture as unproven. This proof attempt does not rely on an unstated theorem beyond the elementary divisibility observations above.
