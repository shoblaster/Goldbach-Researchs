# Proof frontier 007 — the binary circle-method inequality

**Status: PROOF GAP — NOT PROVED.**

This record isolates a concrete analytic implication needed by a standard
circle-method route to Strong Goldbach. It does not claim a new theorem or a
proof of the conjecture.

## Source-verified context

Helfgott's survey/paper *The ternary Goldbach problem* defines prime-supported
Fourier functions and writes the corresponding additive representation as a
circle integral (Section 1.2). It then splits the integral into major and minor
arcs. For the binary problem, the paper states that the method fails at the
minor-arc comparison inequality and explains that the presently available
minor-arc information does not yield the needed lower bound. See CIT-017 in the
literature ledger; the relevant source locations are pp. 7--9 of the arXiv PDF,
especially equations (1.2)--(1.4) and the discussion immediately following.

The same source records Chen's theorem in the form: every sufficiently large
even integer is a prime plus a product of at most two primes. This is an
almost-prime result, not the binary statement that both summands are prime.

## Self-contained conditional lemma

Let `f` be a nonnegative, finitely supported function on the integers, with
support contained in the positive primes, and let

```
S(alpha) = sum_n f(n) exp(2*pi*i*alpha*n).
```

For an even integer `N`, Fourier inversion gives the weighted binary count

```
R_f(N) = integral_[R/Z] S(alpha)^2 exp(-2*pi*i*alpha*N) d alpha.
```

Let `M` be a chosen major-arc set and `m = (R/Z) \ M`. Define

```
I_M(N) = integral_M S(alpha)^2 exp(-2*pi*i*alpha*N) d alpha,
I_m(N) = integral_m S(alpha)^2 exp(-2*pi*i*alpha*N) d alpha.
```

The finite support makes all sums and integrals below unambiguous. Fourier
orthogonality gives

```
R_f(N) = sum_{a+b=N} f(a) f(b) >= 0.
```

Then

```
R_f(N) = I_M(N) + I_m(N)
```

and the elementary estimate

```
|I_m(N)| <= integral_m |S(alpha)|^2 d alpha
```

holds by the triangle inequality. Consequently, the following explicit
condition is sufficient for a Goldbach representation:

```
Re(I_M(N)) > integral_m |S(alpha)|^2 d alpha >= 0.
```

Indeed, `R_f(N)` is real and
`R_f(N) >= Re(I_M(N)) - |I_m(N)| > 0`. Because `f` is nonnegative and
supported on primes, a positive weighted count supplies at least one pair of
primes summing to `N`.

## Exact unresolved step

The displayed major-arc domination condition is not established here. The
source-verified discussion in CIT-017 says that, for binary Goldbach, the
analogous minor-arc comparison is where the circle method fails; it attributes
the difficulty to the fact that squaring the prime Fourier transform does not
amplify the major-arc peaks enough, and that suitable precise minor-arc
estimates/lower bounds are unavailable. This identifies the missing analytic
input without treating it as a contradiction or an impossibility theorem.

**PROOF GAP — NOT PROVED:** no uniform argument has been supplied that makes
the sufficient inequality hold for every sufficiently large even `N`.

## Boundary of the result

- This file proves only the conditional lemma above and records a literature-
  verified obstruction to completing it with the cited binary circle-method
  estimates.
- It does not prove the Hardy--Littlewood asymptotic, Chen's theorem, or
  Strong Goldbach.
- No novelty claim is made. The conditional lemma is an elementary audit of
  the logical step exposed in the cited source.
