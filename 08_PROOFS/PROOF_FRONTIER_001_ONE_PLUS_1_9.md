# Proof frontier 001 — source-reported Proposition (1+1.9)

**Status: SOURCE-REPORTED FRONTIER RESULT; not independently proof-checked here.**

## Direct source inspected

Li and Liu, *Theorem (1+1.9) on the Goldbach Conjecture*, arXiv:2606.05224. The arXiv HTML was inspected on 2026-10-03.

## What the source states

The paper defines Proposition `(1+a)` for `1 <= a <= 2` as the assertion that every sufficiently large even `N` can be written

```
N = p + r q,
```

where `p` and `q` are prime and `r` is either `1` or prime with `r <= q^(a-1)`. The source says:

- `(1+1)` is essentially binary Goldbach;
- `(1+2)` is Chen's theorem;
- it proves unconditionally that `(1+1.9)` is true;
- under a stated Elliott–Halberstam-type assumption, it claims `(1+1.4)`.

## Why this matters

This is a meaningful proof-frontier result if the preprint's proof is correct: it narrows the allowed almost-prime factor from the full Chen range toward a prime. But `(1+1.9)` still permits `r>1`, so it does not imply `N=p+q` and does not solve Strong Goldbach.

## Integrity limits

- This repository has not checked the paper's 2026 proof line by line.
- The statement is recorded as “the source claims/proves,” not as an independently verified theorem of this project.
- No numerical threshold or hidden constants are inferred from the source's phrase “sufficiently large.”
- The conditional `(1+1.4)` claim is not used in any proof attempt.

## Consequence for our proof program

The local-sieve obstruction is not merely an implementation issue. Current research continues to require sophisticated weighted-sieve and distribution arguments even to obtain an almost-prime result near, but still distinct from, binary Goldbach. Our elementary proof attempts do not address that missing analytic machinery.
