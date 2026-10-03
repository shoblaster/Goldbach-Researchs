# Proof frontier 009 — splitting the `(1+1.9)` witness count

**Status: CONDITIONAL REDUCTION; PROOF GAP — NOT PROVED.**

## Source-verified input

Li and Liu's arXiv version 2 defines Proposition `(1+a)` by

```
N = p + r*q,    r <= q^(a-1),
```

where `r` is either `1` or prime and `p,q` are prime. Their Theorem 1.1
source-reports, for every sufficiently large even `N`,

```
D_(1,1.9)(N) > 0.0004 * C(N) * N / log(N)^2,
```

where `D_(1,a)(N)` counts the displayed witnesses. The exact definition and
lower bound are in CIT-019, Section 1.1, equations (1.6) and Theorem 1.1.
The proof of the paper has not been independently checked here.

## Exact partition of witnesses

For fixed `N`, partition the counted witnesses into

```
D_(1,1.9)(N) = D_prime(N) + D_comp(N),
```

where `D_prime(N)` counts witnesses with `r=1`, and `D_comp(N)` counts
witnesses with prime `r>1`. The first term is exactly the binary Goldbach
representation count (with the ordered convention used by `D`). Therefore the
source-reported lower bound would imply a binary representation if one could
prove the explicit upper bound

```
D_comp(N) < 0.0004 * C(N) * N / log(N)^2.
```

Indeed, subtracting this bound from Theorem 1.1 gives `D_prime(N)>0`.

This is a valid conditional reduction, not an estimate that has been proved in
this project.

## Why the source theorem alone does not close the gap

The definition permits `r>1`, so the second summand `r*q` may be composite.
For example, `18 = 3 + 3*5` satisfies the source's form with `r=3`, `q=5`:
the exact inequality `3^10 = 59049 < 1953125 = 5^9` implies
`3 <= 5^(9/10)`. This illustrates the allowed witness type. It does not claim
that 18 lacks a binary representation (it has one), nor does it test the
source theorem's asymptotic range.

The source reports a lower bound for the **total** witness count, not a bound
that forces a positive `r=1` subcount. No upper bound of the displayed strength
for `D_comp(N)` is supplied by the source or established here. Hence replacing
the almost-prime witness by a prime witness would be an invalid proof step.

**PROOF GAP — NOT PROVED:** the composite-witness estimate needed to deduce
binary Goldbach from Proposition `(1+1.9)` is absent.

## Boundary

- This file records a source-verified theorem statement and an elementary
  counting reduction only.
- It does not independently verify Li--Liu's analytic proof.
- It does not prove Strong Goldbach or make a novelty claim.
