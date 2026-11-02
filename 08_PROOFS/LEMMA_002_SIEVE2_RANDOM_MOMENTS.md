# Lemma 002 — exact random-choice moments for the finite Sieve II model

**Status:** Proved elementary identity for the finite model; no novelty claim.  
**Date:** 2026-11-02

## Statement

Choose one forbidden residue uniformly modulo 2 and two distinct forbidden
residues uniformly modulo each odd prime (p\le p_k), independently across
primes. Let (C_k) be the number of permitted indices in
([1,p_k^2]).

For one index, the local survival probability is

\[
a_p=\begin{cases}1/2,&p=2,\\(p-2)/p,&p>2.\end{cases}
\]

For two indices (n,m), the local joint survival probability is

\[
b_p(n,m)=
\begin{cases}
1/2,&p=2\text{ and }n\equiv m\pmod 2,\\
0,&p=2\text{ and }n\not\equiv m\pmod 2,\\
(p-2)/p,&p>2\text{ and }n\equiv m\pmod p,\\
\dfrac{(p-2)(p-3)}{p(p-1)},&p>2\text{ and }n\not\equiv m\pmod p.
\end{cases}
\]

Consequently,

\[
\mathbb E[C_k]=p_k^2\prod_{p\le p_k}a_p,
\qquad
\mathbb E[C_k^2]=
\sum_{n=1}^{p_k^2}\sum_{m=1}^{p_k^2}
\prod_{p\le p_k}b_p(n,m),
\]

and (operatorname{Var}(C_k)=mathbb E[C_k^2]-mathbb E[C_k]^2).

## Proof

For (p=2), exactly one of the two residue classes is forbidden. A fixed
residue survives with probability (1/2). Two distinct residues cannot both
survive, while identical residues survive with probability (1/2).

For odd (p), two distinct forbidden residues are selected uniformly from
(inom p2) pairs. A fixed residue survives in
(inom{p-1}{2}) choices, giving ((p-2)/p). If (n\not\equiv m\pmod p), both fixed residues survive in
(inom{p-2}{2}) choices, giving
((p-2)(p-3)/(p(p-1))). If the residues coincide, the one-point probability
applies. Independence across primes multiplies the local probabilities.
Summing the indicator expectations over one index and over ordered pairs of
indices gives the formulas.

This lemma concerns only the finite random-residue model. It gives no
asymptotic lower bound for the minimum over residue choices and no conclusion
about Strong Goldbach.
