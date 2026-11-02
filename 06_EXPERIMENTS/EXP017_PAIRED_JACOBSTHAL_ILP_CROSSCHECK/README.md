# EXP017 — paired-Jacobsthal ILP cross-check

**Run date:** 2026-11-02  
**Code:** `03_CODE/paired_jacobsthal_ilp_crosscheck.py`  
**Raw output:** `RAW_OUTPUT.txt`  
**External source:** Ziller–Morack ancillary `full_details.pdf`, Proposition
1.5 and ILP formulation (2.3), plus the relation (h_2(k)=6\omega_2(k)+6).

## Purpose

Reproduce the source-side condensed paired-Jacobsthal values using an
independent SciPy/HiGHS 0–1 feasibility model. For each odd prime
(p_3,\ldots,p_k), exactly two nonzero residue classes are selected; every
position in `[1,m]` must be covered. The largest feasible m is `omega2`.

## Result

The reconstructed values for (k=3,ldots,8) are `18,30,66,150,192,258`,
matching the table in the cited source. This validates the source's finite ILP
interpretation against an independent implementation, but does not validate
the source's proofs or establish any novelty for EXP015.

## Reproduction

```
python 03_CODE/paired_jacobsthal_ilp_crosscheck.py
```
