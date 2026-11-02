# Lemma 003 — exact 0–1 formulation of the finite Sieve II minimum

**Status:** proved equivalence for a finite instance; no asymptotic consequence.  
**Date:** 2026-11-02

Fix primes (P=(p_1,ldots,p_k)) and (L=p_k^2). For every prime (p), let
(F_p) be the selected forbidden residue set: (|F_2|=1) and
(|F_p|=2) for odd (p). The finite survivor count is

[
C(F)=\#\{n\in[1,L]: n\bmod p\notin F_p\text{ for every }p\in P\}.
]

Introduce binary variables (x_{p,r}) for (0\le r<p), with

[
\sum_r x_{2,r}=1,\qquad \sum_r x_{p,r}=2\quad(p>2),
]

and binary variables (y_n) for (1\le n\le L). Impose, for each (n),

[
y_n+\sum_{p\in P}x_{p,n\bmod p}\ge1.
]

Then minimizing (sum_{n=1}^L y_n) gives exactly
(\min_F C(F)).

## Proof

For a fixed selection (F), set (x_{p,r}=1) exactly when (r\in F_p).
If (n) is a survivor, no selected residue matches it, so the coverage sum
is zero and the constraint forces (y_n=1). If (n) is not a survivor, at
least one selected residue matches, so the constraint allows (y_n=0), and
the objective sets (y_n=0) in an optimum. Thus, for every fixed (F), the
minimum feasible (y)-objective is (C(F)). Conversely, every feasible
integer (x) satisfies the prescribed cardinalities and therefore defines a
valid selection (F). Minimizing over all feasible (x) is consequently the
same finite optimization problem as minimizing (C(F)).

The script `03_CODE/barca_sieve2_milp_exact.py` solves this 0–1 model with
`scipy.optimize.milp`/HiGHS and independently recomputes the survivors from
the returned residue witness. The solver certificate is computational, not a
formal proof object, and the lemma does not imply any lower bound outside the
finite instance.
