# Proof frontier 013 — the source-stated switching barrier

**Status: SOURCE-VERIFIED BARRIER; PROOF GAP — NOT PROVED.**

## Direct source observation

In Section 8.1 of the Li--Liu arXiv HTML v2, the authors isolate a sieve term

```
G = sum_{N^tau <= p <= N^(1/2)} S(A_p; P(N), p).
```

They state that, when the upper limit approaches `N^(1/2)`, an upper bound
without Chen's switching principle does not have the correct order of growth;
they call the switching principle indispensable for this range. The same
discussion says that although other terms can be bounded with suitable weights,
the resulting constants are too poor to give a nontrivial lower bound for the
`(1+2)` count without the switching argument. These are source statements, not
claims independently reproved here (see CIT-019, Section 8.1).

## Relevance to the current gap

The composite-witness estimate required by
`PROOF_FRONTIER_009_ALMOST_PRIME_SPLIT.md` is also a large-prime, semiprime
counting problem. The source's discussion explains why replacing the analytic
sieve by elementary factor counting loses the needed order and constants. It
does not itself supply an upper bound that removes all `r>1` witnesses; it
supplies the mixed-count lower bound instead.

**PROVED LIMITATION:** the inspected source explicitly identifies a switching
and constant-control barrier in the relevant sieve range.

**PROOF GAP — NOT PROVED:** no argument here converts that barrier into a
bound on `D_comp(N)` strong enough to force `r=1`.

The source's analytic proof and constants remain SOURCE-REPORTED and were not
independently rederived.
