# Proof frontier 015 — author exposition confirms the density-transfer gap

**Date checked:** 2026-10-06  
**Source:** Ricardo Barca, “Very easy explanation of the main ideas of the proof,” [Ricardo Barca Blog](https://ricardobarca.wordpress.com/very-easy/).  
**Status:** SOURCE-CONFIRMED PROOF GAP. The page is an explanatory blog, not a peer-reviewed proof; it is used only to document what the author’s own exposition assumes.

## 1. Source passage

The page defines a periodic sequence of permitted \(k\)-tuples with period \(m_k=p_1p_2\cdots p_k\) (HTML lines 19–20 and 30–32). It says that the average density in the full period is \(\delta_k\) (lines 82–86). It then introduces the key step:

> “suppose that the permitted \(k\)-tuples are placed in positions that follow an approximately regular pattern along the interval \([1,m_k]\)” (HTML line 87).

The page uses that supposition to conclude that the densities in both \([1,p_k^2]\) and \([p_k^2+1,m_k]\) are close to the full-period density (lines 87–90), then claims a positive lower bound in the left interval and the binary Goldbach conclusion (lines 91–94).

## 2. Exact logical issue

A positive count or density in a full period does not, by itself, imply a positive count in a specified initial subinterval. For any period \(M>L\) and any \(0<d<1\), one can place all permitted positions in \((L,M]\); the full-period density is positive while the initial interval \([1,L]\) is empty. This is an elementary counterexample to the inference pattern, not a counterexample to the Goldbach sieve itself.

Therefore the required statement is a quantitative distribution theorem for the particular CRT-constrained permitted set, not a consequence of its full-period average. The blog page does not prove such a distribution theorem; it explicitly introduces it as a supposition.

## 3. Relation to the arXiv audit

The later arXiv paper (CIT-021) attempts to replace this supposition with Lemmas 1.2, 1.4, and 3.1. `PROOF_FRONTIER_014_BARCA_CLAIM_AUDIT.md` records the remaining quantifier/rate gap: fixed-tolerance convergence is upgraded to the shrinking tolerance ε_k uniformly over (1\le h\le k) without the necessary quantitative rate. The author’s own exposition therefore independently identifies the same density-transfer step as the essential bridge.

## 4. Research status

- This source confirms the location and role of the unproved density-transfer assumption.
- It does not disprove Strong Goldbach and does not establish any new theorem.
- Strong Goldbach remains OPEN; **PROOF GAP — NOT PROVED**.
- No numerical computation, Lean build, or independent reconstruction was run in this stage.
