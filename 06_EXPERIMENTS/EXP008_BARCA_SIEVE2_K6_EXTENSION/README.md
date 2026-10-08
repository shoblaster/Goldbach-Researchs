# EXP008 — targeted (k=6) Sieve II extension

**Run date:** 2026-10-09  
**Source code:** `03_CODE/barca_sieve2_k6_extension.py`  
**Raw output:** `RAW_OUTPUT.txt`

## Purpose

EXP007 exhaustively audited the model through (k=5). EXP008 fixes the
(k=5) minimizing residue choices from EXP007 and enumerates all
(inom{13}{2}=78) choices for the two forbidden residues modulo (13).
This is a targeted extension, not an exhaustive search over all (k=6)
residue choices.

## Result

The smallest count among these 78 extensions is 3 permitted indices in
([1,13^2]). One witness is the forbidden-residue selection

`((0,), (0,1), (0,2), (1,3), (1,9), (1,5))`,

with survivors `(11, 41, 149)`. Its source-normalized left density is
(3/13). For comparison, the exact full-period source-normalized density is


\[
\delta_6=\frac{(2-1)(3-2)(5-2)(7-2)(11-2)(13-2)}{2\cdot3\cdot5\cdot7\cdot11}=\frac9{14}.
\]

This finite result does not contradict an eventual lower bound beginning at
large (k), does not disprove Strong Goldbach, and does not establish
anything asymptotic.
