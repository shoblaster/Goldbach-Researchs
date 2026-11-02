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
   are constrained by a fixed pair difference, so this is related prior art,
   not the same arbitrary-residue model.
5. Mario Ziller and John F. Morack, *Divisibility in paired progressions,
   Goldbach's conjecture, and the infinitude of prime pairs*,
   [arXiv:1706.00317](https://arxiv.org/abs/1706.00317). The source states a
   conditional bound on the paired Jacobsthal function sufficient for a
   tightened Goldbach statement. This connection is recorded for scope and
   does not verify the source's proof independently.

## Search outcome

- Related Goldbach sieve literature exists.
- The paired-Jacobsthal literature is directly relevant to the general
  two-class-per-prime theme, and it substantially weakens any novelty claim.
  The exact equivalence to the arbitrary-residue EXP015 MILP was not
  established: the paired papers constrain the two classes to arise from a
  fixed pair difference, whereas EXP015 allows any two distinct classes.
- No directly matching publication was verified for the exact EXP007–EXP015
  arbitrary-residue optima or full histograms.
- This is **not** evidence that the computations are novel. A broader search
  of books, papers, conference proceedings, and citation graphs is still
  required before any novelty statement.

## Integrity status

- No citation was invented.
- No theorem was attributed to Song beyond the arXiv abstract's stated scope.
- Publication status remains: technical-note/preprint candidate; novelty
  unestablished; Strong Goldbach open.
