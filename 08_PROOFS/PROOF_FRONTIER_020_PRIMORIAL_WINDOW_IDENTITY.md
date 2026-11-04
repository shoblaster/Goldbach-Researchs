# Proof Frontier 020 — Primorial lower-window bijection and endpoint condition

## Scope

This note isolates an elementary finite statement related to the windowed
primorial identity reported in CIT-037. It is not a proof of binary Goldbach.

Let

\[
N=p_k\#,
\qquad p_{k+1}=\text{the next prime after }p_k,
\qquad 2\le H\le p_{k+1}^2.
\]

Assume additionally that (N-H>p_k). Define

\[
A_H=\{p:2\le p<H,\ p\text{ and }N-p\text{ are prime}\},
\]
\[
B_H=\{q:q\text{ is prime and }N-H<q\le N-2\}.
\]

## Proposition (finite window correspondence)

Under the displayed endpoint condition, the map (p\mapsto q=N-p) is a
bijection (A_H\to B_H). Consequently (|A_H|=|B_H|).

### Proof

If (p\in A_H), then (q=N-p) is prime, (q\le N-2), and (p<H)
gives (q>N-H). Thus (q\in B_H).

Conversely, let (q\in B_H) and put (p=N-q). Then (2\le p<H). If
(p) were composite, it would have a prime divisor (r\le\sqrt p
<p_{k+1}), hence (r\le p_k). Since (r\mid N) and (r\mid p), we get
(r\mid q=N-p). The endpoint condition gives (q>N-H>p_k\ge r), which is
impossible for the prime (q). Hence (p) is prime, and (p\in A_H). The
two maps are inverse to one another. ∎

## Source-level boundary finding

The peer-reviewed Journal of Integer Sequences paper by Čejchan, Křížek, and
Somer (CIT-038) proves the same forced-primality mechanism near primorials with
the lower-side threshold based on the preceding prime (p_{k-1}^2) (its
Theorem 18). The present elementary argument explains the proposed
(p_{k+1}^2) extension when the explicit endpoint condition (N-H>p_k) is
available. This is recorded as a checked derivation and comparison, not as a
novelty claim.

The Ross preprint's Zenodo abstract states the same correspondence for
(H\le p_{k+1}^2), but the page is a non-peer-reviewed record and says its
version is superseded. The literal small-(k) wording cannot be used without
an endpoint qualification: for (k=3), (N=30), (H=49), direct trial
division gives (|A_H|=6), whereas (B_H) contains 9 primes, with extra
(q\in\{2,3,5\}). This is a source-scope/endpoint warning, not a claim that
the intended large-(k) statement is false.

## Computation

`03_CODE/primorial_window_identity_check.py` checked exact set equality for
(k=4,5,6,7,8) using independent trial division. The raw output is
`06_EXPERIMENTS/EXP021_PRIMORIAL_WINDOW_IDENTITY/RAW_OUTPUT.txt`.

## Status

- The proposition above is **PROVED** under its explicit endpoint condition.
- EXP021 is a finite computational check, not an asymptotic result.
- Strong Goldbach remains **OPEN; PROOF GAP — NOT PROVED**.
- **NOVELTY NOT ESTABLISHED**; the source-level identity is prior art and the
  project contributes only an independently audited finite check and boundary
  qualification.
