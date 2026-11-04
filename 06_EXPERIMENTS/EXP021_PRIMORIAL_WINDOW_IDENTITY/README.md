# EXP021 — Primorial lower-window identity check

## Question

Does the lower-window counting identity stated in the recent Ross primorial
preprint hold in finite cases, and what endpoint condition is needed for its
elementary proof?

For (N=p_k\#), (H=p_{k+1}^2), the audited correspondence is

\[
\{p:2\le p<H,\ p\text{ and }N-p\text{ prime}\}
\longleftrightarrow
\{q\text{ prime}:N-H<q\le N-2\},
\qquad q=N-p.
\]

## Method

`03_CODE/primorial_window_identity_check.py` uses independent trial division,
constructs the first nine primes by the same method, and checks exact set
equality for (k=4,5,6,7,8). The tested cases satisfy (N-H>p_k), which is
the size condition needed in the elementary reverse implication: if
(p=N-q<H) were composite, a prime divisor (r<p_{k+1}) would divide both
(N) and (q), contradicting that (q) is a large prime.

## Result actually computed

All five tested cases matched exactly:

| (k) | (N) | (H) | direct count | interval count |
|---:|---:|---:|---:|---:|
| 4 | 210 | 121 | 22 | 22 |
| 5 | 2,310 | 169 | 19 | 19 |
| 6 | 30,030 | 289 | 23 | 23 |
| 7 | 510,510 | 361 | 26 | 26 |
| 8 | 9,699,690 | 529 | 32 | 32 |

The raw output is preserved in `RAW_OUTPUT.txt`.

## Boundary audit

The literal formula fails for the tiny case (k=3), (N=30), (H=49):
the direct count is 6, while the interval contains 9 primes; the three extra
primes are (2,3,5). Thus the source statement must be read with an implicit
large-(k)/endpoint condition (or with a restricted interval), not as a
small-(k) identity without qualification.

## Status

- Finite set-bijection checks: **COMPUTED and reproduced by one implementation**.
- Elementary identity under (N-H>p_k): **PROVED in the accompanying audit note**.
- Strong Goldbach: **OPEN; PROOF GAP — NOT PROVED**.
- No asymptotic or novelty claim follows from this experiment.
