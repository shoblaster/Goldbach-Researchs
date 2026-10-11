# EXP009 — exhaustive (k=6) Sieve II audit

**Run date:** 2026-10-11  
**Source code:** `03_CODE/barca_sieve2_k6_exhaustive_bitmask.py`  
**Raw output:** `RAW_OUTPUT.txt`

## Purpose

EXP009 exhaustively enumerates every residue selection allowed by Barca's
Sieve II rules for (k=6): one forbidden residue modulo 2 and two forbidden
residues modulo each of 3, 5, 7, 11, and 13. The total is

\[
2\cdot3\cdot10\cdot21\cdot55\cdot78=5,405,400
\]

choices. It uses a bit-mask intersection implementation independent of the
earlier per-integer enumeration, then recomputes the survivors of each
minimizer directly from the defining modular condition.

## Result

The exact minimum number of permitted indices in ([1,13^2]) is **2**.
There are 5 minimizing selections, listed with their two surviving indices in
`RAW_OUTPUT.txt`.

This is a finite result for the stated model. It does not establish an
asymptotic statement, does not contradict a lower bound asserted only for
sufficiently large (k), and does not prove or disprove Strong Goldbach.
