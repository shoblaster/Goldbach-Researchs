# Proof frontier 010 — source-level boundary of the Li--Liu sieve

**Status: SOURCE AUDIT; PROOF GAP — NOT PROVED.**

## What the source actually counts

The Li--Liu arXiv HTML v2 defines

```
D_(1,a)(N) = |{ p <= N : N-p = r*q,
                 r <= q^(a-1), r prime or 1, q prime }|.
```

In the proof of Theorem 1.1, the source introduces a sieve weight `w(n)` and
states that, in one of its cases, `w(n)=1` exactly when `n` is either a prime
or a product `r*q` of two primes in specified ranges. These are the source
locations around equations (4.4)--(4.7), especially the explicit case
analysis at lines 516--520 of the HTML. See CIT-019.

Thus the positive lower bound for `D_(1,1.9)(N)` is deliberately a lower bound
for a mixed prime/semiprime set. The source's displayed proof does not turn the
semiprime terms into primes.

## Logical consequence

The source itself says that the binary equation remains out of reach before
introducing the relaxed almost-prime equation. Therefore the correct inference
from Theorem 1.1 is the conditional split in
`PROOF_FRONTIER_009_ALMOST_PRIME_SPLIT.md`, not a binary Goldbach proof.

**PROOF GAP — NOT PROVED:** an independent estimate that removes all `r>1`
terms (or otherwise produces an `r=1` witness) is still missing.

## Verification boundary

- The paper's analytic estimates and numerical constants were not independently
  rederived here.
- This audit verifies only the source's definitions and the logical scope of
  its counted set.
- No novelty claim is made.
