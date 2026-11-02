# EXP014 — exploratory \(k=8\) heuristic search

**Run date:** 2026-11-02  
**Source code:** `03_CODE/barca_sieve2_k8_heuristic.py`  
**Raw output:** `RAW_OUTPUT.txt`

## Purpose

The full (k=8) search would involve
(735,134,400\times\binom{19}{2}) selections (over 125 billion), so EXP014
uses fixed-seed simulated annealing over the first seven prime choices and
optimizes the final two forbidden classes modulo 19 exactly at each state. The
result is a candidate witness only.

## Result

The run found a witness with 4 permitted indices in ([1,19^2]). This is not
an exact minimum, not a lower bound, and not an asymptotic result. It is
preserved solely to guide a future exact branch-and-bound or constraint-search
implementation.
