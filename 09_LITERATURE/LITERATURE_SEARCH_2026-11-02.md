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
