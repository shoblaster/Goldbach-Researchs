# Proof frontier 011 — an elementary bound is far too weak

**Status: PROVED LIMITATION; PROOF GAP — NOT PROVED.**

Let `D_comp(N)` be the number of Li--Liu `(1+1.9)` witnesses with prime
`r>1`, so that

```
N = p + r*q,
```

with `p,q,r` prime and `r*q <= N`. For each ordered pair `(r,q)` there is at
most one possible `p=N-r*q`; dropping the primality conditions can therefore
only increase the count.

## Elementary factor-pair bound

If `r*q <= N`, then either `r <= sqrt(N)` or `q <= sqrt(N)`. Hence the number
of possible ordered prime pairs is at most

```
sum_{r <= sqrt(N), r prime} floor(N/r)
  + sum_{q <= sqrt(N), q prime} floor(N/q)
<= 2*N*sum_{m <= sqrt(N)} 1/m.
```

Using the elementary harmonic estimate
`sum_{m <= X} 1/m <= 1 + log X`, this gives

```
D_comp(N) <= 2*N*(1 + log(sqrt(N)))
           = 2*N + N*log(N).
```

The restrictions `r <= q^(9/10)` and primality of `p` and `q` were ignored,
so this is a valid upper bound but intentionally crude.

## Why this does not close the Li--Liu reduction

The conditional reduction in `PROOF_FRONTIER_009_ALMOST_PRIME_SPLIT.md` needs
an upper bound for `D_comp(N)` below a constant multiple of
`N/log(N)^2`. The bound above is `O(N log N)`, which is many logarithmic powers
larger and cannot imply the required inequality. Improving it to the needed
scale would require nontrivial simultaneous information about the primality of
`p=N-r*q` and the factors `r,q`; pure factor enumeration cannot supply that.

**PROVED LIMITATION:** the elementary counting route does not eliminate the
composite witnesses.

**PROOF GAP — NOT PROVED:** no `D_comp(N)=o(N/log(N)^2)` or matching explicit
upper bound has been established here.

No numerical computation or external theorem is used in this derivation.
