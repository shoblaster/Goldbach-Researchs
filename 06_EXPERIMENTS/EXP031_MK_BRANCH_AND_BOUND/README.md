# EXP031: exact fixed-window minima M_k by branch and bound, k = 3..12

Branch: `verify/mk-branch-and-bound`. Question: RQ3 in `01_RESEARCH_QUESTIONS.md`.
Code: `03_CODE/mk_enum_bb.cpp` (new, no MILP or CP solver). Raw output: `RAW_OUTPUT.txt` (one build, run for k = 3..12).
Extends EXP015/EXP019/EXP024 (reference values and the plain enumeration `03_CODE/mk_enum_cpp.cpp`).

## Method
Same model as EXP024: window [1, p_k^2]; forbid one class mod 2 and two classes mod each odd prime up to p_k; M_k is the minimum
number of surviving positions. Primes are processed in increasing order and the last prime is resolved exactly (the two classes with
the most survivors give the minimum over all pairs). New here is a bound: at a node with survivor mask m after the primes below p_i,
each remaining prime removes at most the sum of its two largest class counts inside m, so every leaf below has at least
pc(m) - sum of those counts survivors. A subtree is cut only when that bound is strictly greater than the best value found so far.
Equal values are not cut, so the number of leaves attaining the minimum is counted exactly as in EXP024. Threads share the best value.

## Validation against EXP024 (same model, plain enumeration)
Compared value and "prefix witnesses attaining the minimum" (a count of leaves, not an independent quantity):

| k | window | M_k (this run) | leaves at minimum | nodes visited | time (2 threads) | EXP024 value / leaves | match |
|---:|---:|---:|---:|---:|---:|---|---|
| 3 | 25 | 2 | 5 | 6 | 0 s | 2 / 5 | yes |
| 4 | 49 | 2 | 27 | 60 | 0 s | 2 / 27 | yes |
| 5 | 121 | 3 | 51 | 1,260 | 0 s | 3 / 51 | yes |
| 6 | 169 | 2 | 5 | 2,690 | 0 s | 2 / 5 | yes |
| 7 | 289 | 4 | 11 | 33,708 | 0 s | 4 / 11 | yes |
| 8 | 361 | 4 | 156 | 298,646 | 0 s | 4 / 156 | yes |
| 9 | 529 | 5 | 57 | 1,644,734 | 0 s | not run | - |
| 10 | 841 | 10 | 998 | 23,660,400 | 5 s | not run | - |
| 11 | 961 | 8 | 30 | 68,623,761 | 13 s | not run | - |
| 12 | 1369 | 13 | 70 | 689,589,725 | 263 s | not run | - |

The value and the leaf count agree with EXP024 for every k <= 8 where EXP024 ran. k = 3..5 EXP024 values are from its raw output; the plain enumeration
also reproduces them when run again. For k = 8 the plain enumeration needed 77 s; this search needs well under 1 s.

## Results
- **M_9 = 5 is re-verified** by a method that shares no solver and no code with the HiGHS run behind EXP019. EXP024 estimated about 3.7 hours for a plain re-check; this run takes under a second.
- **New values (no earlier value in the repository):** M_10 = 10, M_11 = 8, M_12 = 13. Every reported witness was recomputed directly from the definition (`direct_match True`).
- Witnesses (residues removed, in order of primes 2, 3, 5, ...):
  - k = 10: (0) (0,1) (0,2) (0,1) (0,1) (1,4) (8,10) (3,5) (9,18) (25,17)   survivors: 149 293 311 359 389 479 509 629 761 821 
  - k = 11: (1) (0,1) (3,4) (2,6) (3,4) (4,6) (14,16) (8,17) (10,15) (14,28) (14,16)   survivors: 182 206 242 392 596 722 770 896 
  - k = 12: (0) (0,1) (0,2) (4,5) (7,9) (2,9) (2,6) (7,8) (5,13) (4,6) (9,29) (11,35)   survivors: 101 203 239 371 413 569 791 983 989 1031 1169 1199 
- The sequence M_3..M_12 = 2, 2, 3, 2, 4, 4, 5, 10, 8, 13 is not monotone.

## Limits
- The lower bound for each k rests on the bound argument being correct. It is validated by exact agreement with the plain enumeration (value and leaf count) for k = 3..8 and by agreement with the single HiGHS value at k = 9; k = 10..12 have no second method (the plain enumeration needs about 3 x 10^13 prefix selections at k = 10).
- A first run of k = 11 was invalid: the prime table stopped at 29 (window printed as 0). The table was extended and all reported runs use the corrected build. The invalid output was not kept.
- Finite computation only. It says nothing about the universal bound H, Conjecture 4, or Strong Goldbach, and no pattern in M_k is claimed. Whether these minima are tabulated elsewhere is open: a further bounded search on 2026-11-10 (CIT-045, CIT-046) found no table of M_k, only an unreviewed existence note in a different setting and the OEIS entry for h2 (see also the log entries of 2026-11-02). **NOVELTY NOT ESTABLISHED.**
