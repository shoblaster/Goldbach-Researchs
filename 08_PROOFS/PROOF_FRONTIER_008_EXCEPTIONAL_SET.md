# Proof frontier 008 — exceptional-set bounds do not close Strong Goldbach

**Status: SOURCE-REPORTED PROGRESS; PROOF GAP — NOT PROVED.**

## Source-verified theorem statement

Zhao's arXiv version 2 (23 January 2026) defines `E(X)` as the number of even
integers at most `X` that are not sums of two odd primes and states:

```
E(X) = O(X^(7/10)),
```

with an ineffective implied constant. The paper's introduction explicitly says
that the strong Goldbach conjecture is still unsolved. See CIT-018 in the
literature ledger; the exact statement appears in the abstract and Theorems
1.1--1.2 of the HTML version.

This repository records the theorem as **SOURCE-REPORTED**. The paper's proof
has not been independently checked here.

## Elementary consequence: density zero

From the source-reported bound, for some (ineffective) constant `C` and all
sufficiently large `X`,

```
0 <= E(X)/X <= C X^(-3/10).
```

Since `X^(-3/10) -> 0`, the proportion of even integers up to `X` that are
exceptions tends to zero. This is a valid consequence of the stated big-O
bound, but it is an averaged/density statement rather than a pointwise
statement for each even integer.

## Exact quantifier gap

Strong Goldbach requires a threshold `X0` such that **every** even integer
`m >= X0` has a representation. An estimate `E(X)=O(X^(7/10))` does not imply
that `E(X)` is eventually zero: a nonnegative integer-valued function can be
unbounded while remaining `O(X^(7/10))`. For example, the purely logical model
`E(X)=floor(X^(1/2))` satisfies such a bound but never vanishes. This example
is not a claim about the actual Goldbach exceptional set; it only demonstrates
why the implication from a sublinear bound to Strong Goldbach is invalid.

Therefore the source-reported result narrows the possible failure set but does
not supply the missing pointwise exclusion of every sufficiently large
exception. The current project has no proof that the actual `E(X)` is bounded,
let alone zero after a finite threshold.

## What would close this frontier

At least one of the following would be needed:

1. a proof that `E(X)` is eventually zero (with a rigorously established
   threshold), or
2. a separate pointwise representation theorem covering every even integer
   outside a verified finite range.

The finite EXP005 computation is not such a pointwise theorem beyond its tested
range, and the source-reported exceptional-set bound has an ineffective
constant, so it does not itself provide a computable threshold.

**PROOF GAP — NOT PROVED:** no step here establishes binary Goldbach for all
even integers.
