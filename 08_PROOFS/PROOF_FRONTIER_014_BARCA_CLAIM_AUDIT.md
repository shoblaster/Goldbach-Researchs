# Proof frontier 014 — source-level audit of Barca's binary Goldbach claim

**Date checked:** 2026-10-05  
**Source:** Ricardo G. Barca, *The binary Goldbach conjecture is also true*, arXiv:1207.4802v14 (22 April 2023), actual arXiv HTML inspected at [arXiv:1207.4802](https://arxiv.org/html/1207.4802).  
**Status:** PROOF GAP — NOT PROVED. This is an audit of the argument as written, not a claim that the cited author’s theorem is false.

## 1. What the source claims

The source states a Main Theorem that every even integer greater than 4 is a sum of two primes (HTML lines 26–41). Its conclusion says that the claimed lower bound for a left-block density implies every even (x>p_k^2) is a sum of two primes, and then combines this with a finite verification claim (HTML lines 400–406).

The relevant quantities are densities δ_h, δ_h^{L_k}, and δ_h^{R_k} in a period of a sieve-like sequence and in the intervals ([1,p_k^2]) and ([p_k^2+1,m_k]).

## 2. The exact inference audited

The source’s Lemma 1.2 states ordinary uniform convergence: for every **fixed** ε>0 there is an (N(ε)) such that, for (k>N(ε)), every level (1\le h\le k) satisfies

\[
 |\delta_h^{R_k}-\delta_h|<\varepsilon.
\]

This is stated at HTML lines 63–65 and concluded at lines 128–133. The displayed bounds used in that proof are at lines 81–97.

In Lemma 1.4, however, the argument introduces the (k)-dependent tolerance

\[
 \varepsilon_k=\Delta\frac{p_k^2}{m_k-p_k^2},
\]

which tends to zero (HTML lines 189–208). Step 5 then says that, for all levels (1\le h\le k), the convergence is fast enough that the errors are smaller than this shrinking ε_k (HTML lines 223–233). Lemma 3.1 repeats this as an assumption justified by the negligible ratio (p_k^2/m_k), and uses it to obtain the lower bound (HTML lines 368–379).

## 3. Why this is a proof gap

The implication

\[
\forall\varepsilon>0\;\exists N(\varepsilon)\;\forall k>N(\varepsilon): E_k<\varepsilon
\]

does **not** by itself imply

\[
\exists N\;\forall k>N: E_k<\varepsilon_k,
\qquad \varepsilon_k\to0.
\]

The latter requires a quantitative rate, such as (E_k=o(\varepsilon_k)). The source does not provide that rate for the full range (1\le h\le k). In fact, its Step 3 only establishes a rate comparison for the previously fixed low levels (1\le h\le h'\); Step 5 then extends that comparison to the moving range (h' < h\le k) without a new estimate. The source itself describes the transition as something that “seems reasonable” and then says it can “assume” the bound (HTML lines 368–374).

The displayed inequality (4) in the source makes the missing scale explicit. At (h=k), it gives only the upper allowance

\[
 \delta_k^{R_k}-\delta_k
 \le \delta_k\frac{p_k^2}{m_k-p_k^2}
 =\frac{\delta_k}{\Delta}\,\varepsilon_k.
\]

Thus the displayed estimate would imply an (<\varepsilon_k) bound only if an additional estimate controlling the factor δ_k/Δ were supplied. The source later uses Δ=0.1 and reports δ_k>102.62 (HTML lines 388–397), so its own displayed bound is not a proof of the required shrinking-tolerance inequality. This does not prove the inequality false; it shows that the cited steps do not establish it.

## 4. Consequence for the Goldbach project

The lower bound for δ_k^{L_k}, and therefore the claimed passage from permitted sieve tuples to a prime-plus-prime representation, remains unsupported at this step. The paper is a source-reported claimed proof, not an independently verified proof certificate. Strong Goldbach remains OPEN in this project; **PROOF GAP — NOT PROVED**.

No novelty claim is made. No computation, Lean build, or independent reconstruction was run for this audit.

## 5. What would be needed to repair the step

An acceptable repair would need an explicit, source-supported estimate uniform over the moving range (1\le h\le k), for example

\[
 \max_{1\le h\le k}|\delta_h^{R_k}-\delta_h|
 =o\!\left(\frac{p_k^2}{m_k-p_k^2}\right),
\]

or another direct lower bound that implies the required left-block density. Ordinary fixed-ε convergence is insufficient.

