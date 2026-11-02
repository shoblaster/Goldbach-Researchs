# Proof frontier 017 — fixed-window minima versus paired-Jacobsthal h2

**Status:** proved finite comparison; no novelty claim; no Goldbach implication.
**Date:** 2026-11-02

## Definitions

For the primes P_k={p_1,...,p_k}, let S_R be the set of indices that avoid
one selected residue class modulo 2 and two distinct selected residue classes
modulo every odd prime in P_k. Define

    M_k = min_R |S_R intersect [1,p_k^2]|.

EXP015 computes M_k exactly for 1 <= k <= 8. Let h2(k) be the primorial
paired-Jacobsthal value in the Ziller--Morack definition: every paired
progression of length h2(k), with even fixed difference, contains an index for
which both entries are coprime to the primorial p_k#.

## Elementary bound

For any distinct-residue assignment R, the CRT gives a paired progression whose
two forbidden classes at each odd prime are exactly those in R, and whose
parity obstruction is the selected class modulo 2. Apply the definition of
h2(k) to each block of h2(k) consecutive indices in [1,p_k^2]. Each block
contains at least one member of S_R. Disjointly partitioning the interval into
floor(p_k^2/h2(k)) such blocks gives

    |S_R intersect [1,p_k^2]| >= floor(p_k^2 / h2(k)).

Taking the minimum over R proves

    M_k >= floor(p_k^2 / h2(k)).

This is only a finite counting consequence of the definition. It does not
improve the published h2 values, prove an asymptotic estimate, or imply Strong
Goldbach.

## Executed comparison

`03_CODE/fixed_window_vs_h2_comparison.py` reads the raw outputs of EXP015 and
EXP017 and checks the inequality. Its output is preserved in
`06_EXPERIMENTS/EXP018_FIXED_WINDOW_H2_COMPARISON/RAW_OUTPUT.txt`.

| k | p_k | p_k^2 | M_k (EXP015) | h2(k) (EXP017/source) | floor bound |
|---:|---:|---:|---:|---:|---:|
| 1 | 2 | 4 | 2 | 2 | 2 |
| 2 | 3 | 9 | 1 | 6 | 1 |
| 3 | 5 | 25 | 2 | 18 | 1 |
| 4 | 7 | 49 | 2 | 30 | 1 |
| 5 | 11 | 121 | 3 | 66 | 1 |
| 6 | 13 | 169 | 2 | 150 | 1 |
| 7 | 17 | 289 | 4 | 192 | 1 |
| 8 | 19 | 361 | 4 | 258 | 1 |

Thus the h2 guarantee gives only one survivor for k=3,...,8, whereas the exact
fixed-window minima are 2, 2, 3, 2, 4, and 4. This is a distinction between
the two finite objectives, not evidence of a new theorem: h2 is a
worst-translation maximum-gap threshold, while M_k is the minimum count in one
specified window.

## Boundary and publication interpretation

The paired-Jacobsthal residue structure is established prior art. Classical
interval-sieve literature also formulates minimum translated-window survivor
counts as an extremal problem, and a 2026 non-peer-reviewed preprint explicitly
studies a related finite-window primorial obstruction. The exact M_k table was
not matched to a published table in this search, but that absence is not a
novelty proof. Status remains **NOVELTY NOT ESTABLISHED** and
**PROOF GAP — NOT PROVED** for any Goldbach conclusion.
