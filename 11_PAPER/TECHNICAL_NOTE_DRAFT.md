# A finite audit of the density-transfer step in a proposed binary Goldbach sieve

**Status:** Draft technical note / reproducibility report. Not peer reviewed.  
**Mathematical status:** Strong Goldbach remains open. This note does not claim a proof or disproof.  
**Repository:** <https://github.com/shoblaster/Goldbach-Researchs>

## Abstract

This note audits a specific step in Ricardo Barca's proposed Sieve II argument
for binary Goldbach: transferring a full-period normalized density of permitted
residue tuples to the initial interval ([1,p_k^2]). We formalize the finite
residue-selection model stated in the source and compute the left-interval
minimum through (k\le 9). The exact minima are
(2,1,2,2,3,2,4,4,5) for (k=1,\ldots,9), respectively. The (k=6) computation enumerates all
5,405,400 selections directly. The (k=7) computation is equivalent to all
735,134,400 selections by optimizing the final pair of forbidden residue
classes exactly. The (k=8) result is obtained from an exact 0–1 mixed-integer
formulation, checked against the direct results for k<=7 and by direct
recomputation of the returned witness. EXP019 extends the same exact MILP to
(k=9), where the optimum is 5 with survivors (178,196,286,376,394), again with
direct modular agreement. These results demonstrate finite
dependence on residue placement, but they do not establish an asymptotic
counterexample or settle Strong Goldbach. The source-level audit identifies the remaining logical issue:
a full-period average does not by itself provide the required uniform lower
bound in the moving initial interval.

## 1. Scope and source protocol

The audited source is Ricardo G. Barca, *The binary Goldbach conjecture is also
true*, arXiv:1207.4802, together with the author's explanatory page
([source](https://ricardobarca.wordpress.com/very-easy/)). The source defines a
periodic Sieve II sequence, selects one residue modulo 2 and two residues modulo
each later prime, and studies permitted indices in ([1,p_k^2]).

This note uses the project's verified records `CIT-021` and `CIT-022` in
`09_LITERATURE/CITATION_VERIFICATION.md`. Paired-Jacobsthal work is recorded
in `CIT-029`–`CIT-031`; its ancillary algorithm note gives a CRT
characterization using two residue classes per odd prime. The fixed-window
survivor objective here is not asserted identical to their h_2 objective. No
novelty claim is made. All raw
outputs and scripts are preserved under `06_EXPERIMENTS/`.

## 2. Finite model

For primes (p_1=2,p_2=3,\ldots,p_k), choose one forbidden residue modulo
2 and two distinct forbidden residues modulo every (p_j>2). An index (n)
is permitted when its residue avoids every selected forbidden set. The finite
audit counts permitted (n) in ([1,p_k^2]).

For a complete period (m_k=p_1\cdots p_k), the source's normalized density
is

\[
\delta_k=\frac{(p_1-1)(p_2-2)\cdots(p_k-2)}{m_k/p_k}.
\]

This is a source-specific normalization: it is not the ordinary permitted
fraction (c_k/m_k).

## 3. Computation

EXP007 exhaustively enumerates all choices for (k\le5) using direct modular
checks. EXP009 independently enumerates all (k=6) choices using bit-mask
intersections and directly reconstructs each minimizer. EXP010 enumerates every
choice through (p=13) and, for each one, groups the survivors in
([1,17^2]) by residue modulo 17. Removing the two most populated classes is
exactly the minimum over all two-forbidden-residue choices modulo 17; hence
EXP010 covers all (5,405,400\times\binom{17}{2}=735,134,400) (k=7)
selections without redundant iteration.

| (k) | (p_k) | exact minimum permitted count | search status |
|---:|---:|---:|---|
| 1 | 2 | 2 | exhaustive |
| 2 | 3 | 1 | exhaustive |
| 3 | 5 | 2 | exhaustive |
| 4 | 7 | 2 | exhaustive |
| 5 | 11 | 3 | exhaustive |
| 6 | 13 | 2 | exhaustive |
| 7 | 17 | 4 | exhaustive via exact final-prime optimization |
| 8 | 19 | 4 | exact 0–1 MILP, cross-checked on k<=7 |
| 9 | 23 | 5 | exact 0–1 MILP, direct witness recomputation |

The exact raw outputs are `EXP007.../RAW_OUTPUT.txt`,
`EXP009.../RAW_OUTPUT.txt`, and `EXP010.../RAW_OUTPUT.txt`.

EXP015 encodes the same finite optimization as a 0–1 mixed-integer program:
binary residue-selection variables choose the forbidden classes, and one
binary variable per index records whether it is uncovered. Lemma 003 proves
the finite equivalence of this formulation. HiGHS returned an optimal value of
4 at k=8 with survivors (56, 86, 224, 302), and the script's independent
modular recomputation matched the solver's survivor variables. This is an
exact finite computation, not a solver-independent formal certificate and not
an asymptotic result.

EXP017 independently implemented the paired-Jacobsthal ILP described in the
Ziller–Morack ancillary file and reproduced its h_2 values through k=8. This
confirms that the general two-class finite ILP direction is established prior
art. The note therefore makes no novelty claim; EXP015 is retained only as an
audit of the fixed-window survivor-count objective.

The construction itself is standard sieve background: Pollack's Chapter 6
Brun-method exercise allows bounded arbitrary residue classes and explicitly
identifies the Goldbach classes as 0 and N modulo p (CIT-036). The source's
asymptotic parameter B(k) has not been shown here to reach the moving boundary
p_k=(p_k^2)^{1/2}, so no direct theorem is imported into the finite audit.

EXP018 makes the objective boundary explicit. If M_k denotes the EXP015
minimum and h_2(k) the paired-Jacobsthal value, then the elementary block
argument gives M_k >= floor(p_k^2/h_2(k)). For k=3,...,8 this bound is only 1,
while the exact M_k values are 2,2,3,2,4,4. The quantities are therefore
different finite statistics, but this separation is not a new asymptotic
estimate. Hildebrand's interval-sieve survey already treats minimum translated
interval survivor counts as an extremal problem (CIT-033), and a recent
non-peer-reviewed preprint studies a closely related finite-window primorial
obstruction while explicitly making no unconditional Goldbach claim (CIT-034).

EXP011 measures the full count distribution for every choice through (k=6).
It verifies that the uniform-choice mean equals (p_k\delta_k) exactly, while
the worst-case left count can be much smaller. At (k=6), the mean count is
(117/14), the median is 8, and the exact minimum is 2; only 5 of the
5,405,400 choices attain that minimum. Thus the finite computation separates
the source's average-density statement from the uniform worst-case lower bound
needed by the proof.

EXP013 gives an exact finite second-moment formula by summing local joint
survival probabilities over ordered pairs of indices. It reproduces the
exhaustive variances through (k=6) and gives variance (165639/66248) at
(k=7) without enumerating all (k=7) residue choices. EXP016 extends the same
exact moment calculation to k=8, giving mean (2565/182) and variance
(1422011/472017). The finite optimum 4 is a low-tail value relative to this
random-model mean; that comparison has no asymptotic implication.

## 4. Interpretation

The finite minima are not equal to the source-normalized full-period averages
in general. This is evidence that the left-block lower bound requires a
distribution theorem beyond the complete-period count. It is not evidence that
the proposed asymptotic statement is false, and it is not evidence against the
truth of Strong Goldbach.

An important scope distinction is required. For a fixed even target N, the
Goldbach-specific sieve forbids the linked classes 0 and N modulo each small
odd prime. A direct elementary argument shows that its survivors in the
interior interval are exactly offsets n for which both n and N-n are primes
above sqrt(N). EXP015/EXP019 instead minimize over arbitrary independent class
choices, so their minima are not Goldbach representation counts. EXP020 checks
this fixed-N correspondence for every even N from 6 through 10,000. The
discussion source and the independent proof are recorded in CIT-035 and Proof
Frontier 018.

The source's explanatory page itself introduces approximate regular placement
of permitted tuples when transferring the full-period density to the two
subintervals. The later source version attempts a convergence argument, but
the project's source-level audit records an unresolved uniform-rate/
shrinking-tolerance step. This note records that diagnosis as **PROOF GAP —
NOT PROVED**, not as a refutation.

## 5. Limitations and publication status

This draft does not claim:

- an asymptotic formula for the finite minima;
- a general theorem for all (k);
- a counterexample to Strong Goldbach;
- novelty relative to all sieve literature; or
- peer-reviewed validation.

Before journal submission, the author should obtain an independent mathematical
check of the model and search the literature more broadly for equivalent finite
wheel/interval-sieve computations, including the paired-Jacobsthal ancillary
algorithms. A suitable submission category would be a
technical note, reproducibility report, or preprint focused on the audited
proof step—not a claimed solution of Goldbach.

## 6. Reproducibility

The earlier enumeration scripts use Python's standard library; EXP015 additionally
requires SciPy 1.17.1 and its HiGHS-backed `scipy.optimize.milp`. Re-run:

```text
python 03_CODE/barca_sieve2_exhaustive.py
python 03_CODE/barca_sieve2_k6_exhaustive_bitmask.py
python 03_CODE/barca_sieve2_k7_extension_search.py
python 03_CODE/barca_sieve2_milp_exact.py
```

The output files are preserved verbatim. The repository's `CLAIM_LEDGER.md`
and `00_MASTER_RESEARCH_LOG.md` record the evidence, uncertainty, and proof
status for each result.

## References

1. Ricardo G. Barca, *The binary Goldbach conjecture is also true*,
   [arXiv:1207.4802](https://arxiv.org/abs/1207.4802).
2. Ricardo G. Barca, “Very easy explanation of the main ideas of the proof,”
   [author's exposition](https://ricardobarca.wordpress.com/very-easy/).
3. Mario Ziller; John F. Morack, *A short note on the computation of the
   generalised Jacobsthal function for paired progressions*,
   [arXiv:1706.03668](https://arxiv.org/abs/1706.03668).
4. Mario Ziller; John F. Morack, *Divisibility in paired progressions,
   Goldbach’s conjecture, and the infinitude of prime pairs*,
   [arXiv:1706.00317](https://arxiv.org/abs/1706.00317).
5. Mario Ziller; John F. Morack, *On the computation of the generalised
   Jacobsthal function for paired progressions*, ancillary file,
   [full_details.pdf](https://arxiv.org/src/1706.03668v1/anc/full_details.pdf).
6. A. Hildebrand, *Extremal Problems in Sieve Theory*,
   [Kyoto Kokyuroku PDF](https://www.kurims.kyoto-u.ac.jp/~kyodo/kokyuroku/contents/pdf/0958-1.pdf).
7. Tien Tuan Khiem Nguyen, *Finite-Window Noncovering on Primorial Wheels:
   Higher-Order CRT Bounds and Shift Correlations*,
   [Preprints.org version 1](https://doi.org/10.20944/preprints202608.1299.v1).
8. MathOverflow, “Can a sparse set of residue classes cover all integers up to
   E?”,
   [discussion](https://mathoverflow.net/questions/497359/can-a-sparse-set-of-residue-classes-cover-all-integers-up-to-e).
9. Paul Pollack, *Not Always Buried Deep: A Second Course in Elementary Number
   Theory*, Chapter 6, [book PDF](https://pollack.uga.edu/NABDofficial.pdf).
