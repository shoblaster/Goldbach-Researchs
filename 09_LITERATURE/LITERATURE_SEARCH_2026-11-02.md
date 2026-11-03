# Focused literature search — 2026-11-02

## Scope

Searches targeted the exact combination of: Goldbach, Sieve II/permitted
k-tuples, primorial-period density, and extremal counts in the initial interval
([1,p_k^2]). The purpose was publication scoping, not a novelty declaration.

## Sources inspected

1. Ricardo G. Barca, *The binary Goldbach conjecture is also true*,
   [arXiv:1207.4802](https://arxiv.org/abs/1207.4802). This is the audited
   source whose Sieve II model is implemented in EXP007–EXP012.
2. Ricardo G. Barca, “Very easy explanation of the main ideas of the proof,”
   [author exposition](https://ricardobarca.wordpress.com/very-easy/). This
   explicitly discusses the left/right interval split and approximate regular
   placement.
3. Fu-Gao Song, *Sifting Function Partition for the Goldbach Problem*,
   [arXiv:0801.0786](https://arxiv.org/abs/0801.0786). The arXiv abstract
   describes alternative Goldbach sieve partitions and residual-integer
   methods. Only the abstract/metadata were inspected here; no equivalence to
   the present finite model was established.
4. Mario Ziller and John F. Morack, *A short note on the computation of the
   generalised Jacobsthal function for paired progressions*,
   [arXiv:1706.03668](https://arxiv.org/abs/1706.03668). The source defines a
   paired Jacobsthal function and reports exact primorial values through
   (p=73), including (h_2(8)=258). Its two forbidden classes per odd prime
   are part of the paired-progression formulation.
5. Mario Ziller and John F. Morack, *Divisibility in paired progressions,
   Goldbach's conjecture, and the infinitude of prime pairs*,
   [arXiv:1706.00317](https://arxiv.org/abs/1706.00317). The source states a
   conditional bound on the paired Jacobsthal function sufficient for a
   tightened Goldbach statement. This connection is recorded for scope and
   does not verify the source's proof independently.
6. The ancillary algorithm note,
   [full_details.pdf](https://arxiv.org/src/1706.03668v1/anc/full_details.pdf),
   was inspected after the initial search. Proposition 1.5 states that paired
   progressions can be characterized by choosing two residue classes for each
   odd prime and gives the CRT converse.

7. A. Hildebrand, *Extremal Problems in Sieve Theory*,
   [Kyoto Kokyuroku PDF](https://www.kurims.kyoto-u.ac.jp/~kyodo/kokyuroku/contents/pdf/0958-1.pdf).
   The source defines the minimum translated-interval sifting quantity S_*(x,P)
   and describes the interval-sieve extremal problem as difficult/open in broad
   special cases. This is background prior art; the source's displayed model
   uses one forbidden class per prime and is not asserted identical to EXP015.

8. Tien Tuan Khiem Nguyen, *Finite-Window Noncovering on Primorial Wheels:
   Higher-Order CRT Bounds and Shift Correlations*,
   [Preprints.org version 1](https://doi.org/10.20944/preprints202608.1299.v1).
   This preprint was posted 2026-08-19 and is explicitly marked not peer
   reviewed. Its abstract and discussion directly describe the mismatch between
   complete-period density and a fixed translated window, and explicitly state
   that it proves neither unconditional Goldbach nor a new infinite prime-pair
   family. It is recorded as a close-overlap warning, not as authoritative
   evidence of priority or correctness.

9. MathOverflow, “Can a sparse set of residue classes cover all integers up to
   E?”, [discussion page](https://mathoverflow.net/questions/497359/can-a-sparse-set-of-residue-classes-cover-all-integers-up-to-e).
   The question uses the fixed Goldbach classes 0 and E (mod p), together with
   the even class, and asks about noncoverage. The displayed answer connects
   this to requiring prime pairs above sqrt(E). Because this is a discussion
   page, it is recorded as a scope lead only; the repository proves the finite
   correspondence independently in Proof Frontier 018.

10. Paul Pollack, *Not Always Buried Deep: A Second Course in Elementary
    Number Theory*, [book PDF](https://pollack.uga.edu/NABDofficial.pdf),
    Chapter 6, Exercise 18 and its remark. The source explicitly treats
    uniformly chosen bounded residue classes in a Brun-method sieve and says
    that Goldbach uses the classes 0 and N modulo p. This is textbook background
    and a scope check, not a direct proof for the moving p_k^2 boundary.

The ancillary note also gives an ILP with exactly two selected nonzero
residues per odd prime and coverage constraints for every position. EXP017
implemented that formulation independently and reproduced the source table
through (p=19): (h_2=18,30,66,150,192,258) for (k=3,ldots,8).

## Search outcome

- Related Goldbach sieve literature exists.
- The paired-Jacobsthal literature is directly relevant to the two-class-
  per-prime model and substantially weakens any novelty claim. The inspected
  ancillary file gives a CRT characterization of the same residue-selection
  structure. The remaining difference is the objective: h_2 is a
  worst-translation maximum-gap quantity, whereas EXP015 counts survivors in
  one fixed interval [1,p_k^2].
- No directly matching publication was verified for the exact EXP007–EXP015
  fixed-window optima or full histograms.
- Hildebrand's S_*(x,P) framework shows that minimum survivor counts in
  translated intervals are a recognized interval-sieve extremal theme. The
  2026 Nguyen preprint is even closer in its finite-window primorial framing,
  although its model and objective are not identical and its version is not
  peer reviewed. These findings further lower confidence that EXP015's finite
  statistic is publishably novel without a much broader comparison.
- EXP018 formalizes and executes the elementary comparison
  M_k >= floor(p_k^2/h_2(k)); for k=3,...,9 the h_2 guarantee is only one
  survivor in the p_k^2 window while the exact MILP minima are larger. The
  k=9 h_2 value is source-transcribed because EXP017 independently cross-checked
  only through k=8. This separates the finite objectives but is not a new
  asymptotic result.
- The MathOverflow fixed-N formulation clarifies that the actual Goldbach sieve
  uses residue classes linked by the target N. EXP015/EXP019 instead optimize
  over arbitrary residue choices. This is a model distinction, not evidence
  that the arbitrary minima count Goldbach representations.
- EXP020 independently checked the fixed-N correspondence for every even N from
  6 through 10,000 with no mismatch. The check supports the scope correction,
  but it is finite and does not prove a stronger Goldbach statement.
- Pollack's textbook makes the arbitrary-class construction standard background
  and explicitly names the Goldbach classes. Its asymptotic lower-bound exercise
  has a parameter B(k); this search did not verify B(k)>=1/2 for the exact
  EXP015/EXP019 boundary, so direct applicability is marked UNVERIFIED.
- The source-side ILP is structurally close to EXP015. EXP017 confirms the
  paired-Jacobsthal table, so the finite optimization direction is established
  prior art; only the fixed-window survivor-count objective remains a possible
  scope distinction, not a novelty claim.
- This is **not** evidence that the computations are novel. A broader search
  of books, papers, conference proceedings, and citation graphs is still
  required before any novelty statement.

## Integrity status

- No citation was invented.
- No theorem was attributed to Song beyond the arXiv abstract's stated scope.
- Publication status remains: technical-note/preprint candidate; novelty
  unestablished; Strong Goldbach open.
