# Proof frontier 012 — prime-density information still does not isolate `r=1`

**Status: CONDITIONAL PROVED LIMITATION; PROOF GAP — NOT PROVED.**

## External input

Bennett, Martin, O'Bryant, and Rechnitzer prove an explicit estimate for
`pi(x;q,a)` in reduced residue classes (CIT-020, Theorem 1.3): for fixed
`q >= 3` and `(a,q)=1`,

```
|pi(x;q,a) - Li(x)/phi(q)| < c_pi(q) * x/log(x)^2
```

for all sufficiently large `x`, with explicit positive constants. Applying this
to `q=3`, `a=1,2`, and adding the prime `3`, gives

```
pi(x) <= 1 + Li(x) + O(x/log(x)^2) = O(x/log x).
```

The last equality follows elementarily by splitting the integral defining
`Li(x)` at `sqrt(x)`; this repository does not need the numerical value of the
constant.

## Consequence for composite witnesses

Let `D_comp(N)` be the `r>1` witness count from the Li--Liu split. For each
factor pair `r*q <= N`, one of `r,q` is at most `sqrt(N)`. If
`pi(y) <= K y/log y` for sufficiently large `y`, then for a small factor
`s <= sqrt(N)`,

```
pi(N/s) <= 2*K*N/(s*log N),
```

because `log(N/s) >= (1/2)log N`. Counting both choices of the small factor
and dropping all primality and exponent restrictions gives

```
D_comp(N)
  <= (4*K*N/log N) * sum_{s <= sqrt(N), s prime} 1/s
  <= (4*K*N/log N) * (1 + log(sqrt(N)))
  = O(N).
```

The second inequality uses the elementary bound by the full harmonic sum.

## Limitation

This improves the previous `O(N log N)` factor-enumeration bound, but `O(N)` is
still much larger than the `N/log(N)^2` scale required to subtract composite
witnesses from Li--Liu's positive lower bound. Prime density alone is therefore
insufficient; one needs cancellation or correlation information involving
`p=N-r*q` as well.

**PROOF GAP — NOT PROVED:** no matching `O(N/log(N)^2)` or smaller bound for
`D_comp(N)` has been established.

The use of CIT-020 is source-reported input; its analytic proof was not
independently rederived in this project. No numerical computation or Lean build
was run.
