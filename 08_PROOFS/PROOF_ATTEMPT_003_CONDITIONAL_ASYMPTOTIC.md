# Proof attempt 003 — conditional positive-main-term route

**Status: CONDITIONAL RESULT; not an unconditional proof.**

## Setup

Let `R(E)` denote the number of unordered prime pairs `{p,q}` with `p+q=E`, using the project's convention. Suppose there is a positive function `H(E)` defined for even `E` such that

```
H(E) > 0
```

for every sufficiently large even `E`, and suppose an asymptotic formula holds:

```
R(E) = (1 + o(1)) H(E)       as E -> infinity through even integers.
```

The `o(1)` is understood uniformly along the even integers in the usual sequential sense: for every `epsilon > 0`, there is `E_0` such that `|R(E)/H(E)-1| < epsilon` for all even `E >= E_0`.

## Conditional conclusion

Under these assumptions, every sufficiently large even `E` has a Goldbach representation.

## Proof

Choose `epsilon = 1/2`. For every even `E >= E_0`,

```
|R(E)/H(E)-1| < 1/2.
```

Therefore

```
R(E)/H(E) > 1/2,
```

and hence `R(E) > H(E)/2 > 0`. Since `R(E)` is an integer counting representations, `R(E) >= 1`.

Thus the assumed asymptotic proves Strong Goldbach for all even `E >= E_0`. The finitely many smaller even values would still require separate verification.

## Where the unconditional proof fails

The project has not proved the assumed asymptotic formula. Treating a Hardy–Littlewood prediction or a finite numerical fit as that formula would be an invalid substitution. Therefore this file is a conditional implication, not a proof of Strong Goldbach.

## Status of the remaining task

**PROOF GAP — NOT PROVED:** Establishing an unconditional positive asymptotic for the binary prime-pair representation count with a sufficiently controlled error term remains the missing analytic step in this route.

The positivity argument after such an asymptotic is complete; the asymptotic hypothesis itself is not established here.
