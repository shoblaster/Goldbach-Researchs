# Proof attempt 002 — midpoint and prime-gap approach

**Status: PROOF GAP — NOT PROVED.**

## Target statement

For every even `E > 2`, find primes `p,q` with `p+q=E`.

## Natural midpoint reformulation

Write every unordered candidate pair symmetrically as

```
E = (E/2-d) + (E/2+d),
```

where `d` is an integer and `0 <= d <= E/2-2`. Thus a Goldbach representation is exactly a value of `d` for which both symmetric terms are prime.

This reformulation is exact.

## Attempted route

One might try to use the fact that primes occur frequently near `E/2`:

1. Find a prime `p` near `E/2`.
2. Argue that its reflection `E-p` is also near `E/2`.
3. Conclude that `E-p` is prime because primes are frequent in that region.

## Exact obstruction

Step 3 does not follow from Step 2. A statement that an interval contains a prime establishes the existence of *some* prime in that interval; it does not establish that the specific reflected integer `E-p` is prime.

More formally, let `I` be any interval centered at `E/2`. The assertions

```
I contains a prime p
```

and

```
I contains a prime q
```

do not imply `p+q=E`. The required property is an intersection statement:

```
P ∩ (E-P) is nonempty,
```

where `P` is the set of primes. Ordinary one-set density or prime-gap information does not by itself prove this two-set correlation statement.

## Conditional statement (tautological but precise)

If there exists `d` with `0 <= d <= E/2-2` such that both `E/2-d` and `E/2+d` are prime, then `E` has a Goldbach representation.

This is immediate from the displayed equality, but it merely restates the target in midpoint coordinates. It is not a new criterion.

## Proof gap

**PROOF GAP — NOT PROVED:** No theorem has been supplied that guarantees a symmetric prime pair around every integer midpoint. Proving such a theorem is equivalent to Strong Goldbach.

## What this eliminates

A proof cannot replace the required correlation between `p` and `E-p` with two separate claims that primes are individually common near `E/2`. Any future midpoint method must establish a genuine correlation estimate strong enough to guarantee a pair, not only a one-dimensional prime-gap bound.

## Literature status

No external theorem is invoked. This is a direct logical check of a proposed proof structure. The open status of Strong Goldbach is separately supported by CIT-006.
