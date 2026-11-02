# EXP015 — exact k=8 MILP formulation and cross-check

**Run date:** 2026-11-02  
**Code:** `03_CODE/barca_sieve2_milp_exact.py`  
**Raw output:** `RAW_OUTPUT.txt`  
**Proof note:** `08_PROOFS/LEMMA_003_SIEVE2_MILP_FORMULATION.md`

## Purpose

Use an exact 0–1 mixed-integer formulation of the finite residue-selection
problem. This avoids enumerating all (735,134,400\times\binom{19}{2})
full selections while remaining equivalent to exhaustive finite optimization.
The formulation was first checked on (k=1,ldots,7), where its optima agree
with the previously recorded exact searches, and then run at (k=8).

## Result

The HiGHS solver reported an optimal value of 4 for (k=8), with witness

```
selected ((1,), (0, 1), (0, 3), (3, 4), (2, 3), (0, 2), (7, 16), (5, 6))
survivors (56, 86, 224, 302)
```

The script recomputed the witness directly and printed `direct_match True`.
The exact finite minima for (k=1,ldots,8) were
(2,1,2,2,3,2,4,4).

This is an **EXACT COMPUTATION** for the stated finite model only. It is not a
proof of Strong Goldbach, an asymptotic result, or a novelty claim.

## Reproduction

Environment used: Python 3.14.4, SciPy 1.17.1, HiGHS through
`scipy.optimize.milp`. Run:

```
python 03_CODE/barca_sieve2_milp_exact.py
```
