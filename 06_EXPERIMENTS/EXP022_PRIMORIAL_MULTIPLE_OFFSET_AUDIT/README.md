# EXP022 — Primorial-multiple forced-prime offset audit

## Question

Does the elementary forced-primality mechanism extend from (p_k\#) to
(N=R p_k\#) when every prime factor of (R) is at most (p_k)?

## Method

`03_CODE/primorial_multiple_offset_audit.py` enumerates every such smooth
multiplier (R\le 200) for (k=3,4,5,6). For every integer
(2\le m<p_{k+1}^2), it tests by trial division:

- plus direction: (N+m) prime implies (m) prime;
- minus direction: (N-m) prime and (N-m>p_k) imply (m) prime.

The endpoint condition in the minus direction is explicit. Without it, a small
prime (N-m\le p_k) can be a boundary exception.

## Result actually computed

| (k) | (p_k\#) | smooth (R\le200) | plus failures | minus failures under endpoint | boundary failures |
|---:|---:|---:|---:|---:|---:|
| 3 | 30 | 46 | 0 | 0 | 3 |
| 4 | 210 | 67 | 0 | 0 | 0 |
| 5 | 2,310 | 83 | 0 | 0 | 0 |
| 6 | 30,030 | 98 | 0 | 0 | 0 |

The three (k=3) boundary failures are (R=1) with (m=25,27,28), where
(30-m\in\{5,3,2\}). The raw output is preserved in `RAW_OUTPUT.txt`.

## Interpretation

This is a finite computational confirmation of an elementary, source-reported
mechanism. It is not a new theorem, not an asymptotic result, and not a proof
of Strong Goldbach. **NOVELTY NOT ESTABLISHED.**
