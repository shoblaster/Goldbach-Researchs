# Proof Frontier 021 — Forced-prime offsets for primorial multiples

## Statement

Let (P_k=p_k\#), let (R\ge1) have no prime factor larger than (p_k), and
set (N=R P_k). Let (m) satisfy (2\le m<p_{k+1}^2).

1. If (N+m) is prime, then (m) is prime.
2. If (N-m) is prime and (N-m>p_k), then (m) is prime.

This is a known/source-reported elementary mechanism, not a novelty claim.

## Proof

Suppose (m) is composite. Its least prime divisor (r) satisfies

\[
r\le\sqrt m<p_{k+1},
\]

so (r\le p_k). Because every prime at most (p_k) divides (P_k), we
have (r\mid N), and because (r\mid m), we get (r\mid N\pm m).

For (N+m), the number (N+m>r), so it cannot be the prime (r), a
contradiction. For (N-m), the explicit condition (N-m>p_k\ge r) gives
the same contradiction. Therefore (m) is prime in either case. ∎

## Edge condition

The minus-direction endpoint cannot be silently omitted. For (N=30) and
(m\in\{25,27,28\}), (N-m\in\{5,3,2\}) is prime while (m) is composite.
These are exactly the three boundary failures recorded by EXP022 for (k=3),
(R=1). For (k=4,5,6) and all tested smooth (R\le200), the endpoint
condition held throughout the audited window.

## Status

- The lemma is **PROVED** by the divisor argument above.
- The mechanism is already present in prior literature and recent preprints;
  **NOVELTY NOT ESTABLISHED**.
- EXP022 is a finite audit only.
- Strong Goldbach remains **OPEN; PROOF GAP — NOT PROVED**.
