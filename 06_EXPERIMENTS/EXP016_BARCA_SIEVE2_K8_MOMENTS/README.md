# EXP016 — exact k=8 random-model moments

**Run date:** 2026-11-02  
**Code:** `03_CODE/barca_sieve2_k8_moments.py`  
**Raw output:** `RAW_OUTPUT.txt`

## Purpose

Compute the exact first and second moments of the random-residue survivor
count at (k=8) by summing local one-index and two-index probabilities. This
does not enumerate residue selections and is independent of the EXP015 MILP
optimization mechanism.

## Result

The exact mean is `2565/182` and the exact variance is `1422011/472017`.
The EXP015 optimum 4 is therefore a low-tail finite value; the ratio of 4 to
the exact mean is recorded in the raw output. These moments describe the
uniform random-residue model only. They do not prove a concentration theorem,
bound the minimum asymptotically, or imply Strong Goldbach.

## Reproduction

```
python 03_CODE/barca_sieve2_k8_moments.py
```
