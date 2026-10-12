# EXP010 — exact (k=7) Sieve II minimum

**Run date:** 2026-10-12  
**Source code:** `03_CODE/barca_sieve2_k7_extension_search.py`  
**Raw output:** `RAW_OUTPUT.txt`

## Method

For each of the 5,405,400 choices through (p=13), the script counts the
permitted indices in the enlarged interval ([1,17^2]=[1,289]) by residue
class modulo 17. Choosing the two classes with largest counts is exactly the
minimum over all (inom{17}{2}=136) allowed forbidden-residue pairs modulo
17. Thus the search is equivalent to all

\[
5,405,400\times136=735,134,400
\]

(k=7) selections, without redundantly iterating the final factor.

## Result

The exact minimum permitted count in ([1,289]) is **4**. Ten minimizing
examples are recorded in `RAW_OUTPUT.txt`; each was directly reconstructed
after the residue-class optimization.

This is a finite result for the stated model. It is not an asymptotic lower
bound and does not prove or disprove Strong Goldbach.
