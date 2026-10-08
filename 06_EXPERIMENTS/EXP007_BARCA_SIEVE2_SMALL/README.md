# EXP007 — finite Sieve II residue-selection audit

**Run date:** 2026-10-06  
**Source code:** `03_CODE/barca_sieve2_exhaustive.py`  
**Raw output:** `RAW_OUTPUT.txt`

## Purpose

This is a finite diagnostic of the residue-selection model described in Barca’s Sieve II exposition. For each (k\le5), it exhaustively enumerates one forbidden residue modulo 2 and two forbidden residues modulo each later prime (p\le p_k), then counts permitted indices (1\le n\le p_k^2).

The reported density is `min_count / p_k`, matching the source’s normalization by the number (p_k^2/p_k) of (p_k)-sized subintervals in the left block.

## Results

| k | p_k | full-period source-normalized density \(\delta_k\) | all choices | minimum count | minimum count / p_k | maximum count |
|---:|---:|---:|---:|---:|---:|---:|
| 1 | 2 | 1.000000 | 2 | 2 | 1.000000 | 2 |
| 2 | 3 | 0.500000 | 6 | 1 | 0.333333 | 2 |
| 3 | 5 | 0.500000 | 60 | 2 | 0.400000 | 3 |
| 4 | 7 | 0.500000 | 1,260 | 2 | 0.285714 | 6 |
| 5 | 11 | 0.642857 | 69,300 | 3 | 0.272727 | 10 |

## Interpretation limits

Here “density” uses Barca's source normalization: permitted count divided by the number of subintervals of size \(p_k\), not ordinary permitted-count divided by the full period length. These are finite observations only. They show substantial dependence on the selected residues and that the left-block density is not automatically equal to the full-period source-normalized average at small (k) (for example, (k=5) has minimum left density (3/11) versus \(\delta_5=135/210\)). They do **not** disprove an eventual asymptotic statement for the particular sieve, and they do not bear directly on the truth of Strong Goldbach.

No external theorem, extrapolation, or novelty claim is made. The computation was actually run with Python on 2026-10-06; the exact terminal output is preserved in `RAW_OUTPUT.txt`.
