# Proof Frontier 023 — why a dimension-2 sieve cannot reach the window boundary

Status vocabulary as in `11_PAPER/RESEARCH_METHODS_AND_PROTOCOL.md`.
**NOVELTY NOT ESTABLISHED** (this is standard sieve theory, recorded to close open item RQ2).
Strong Goldbach: **OPEN; PROOF GAP — NOT PROVED.**

## 1. The question
The repo's window problem sifts the integers `n` in `[1, x]` with `x = p_k^2` and asks that `n` and `N - n`
both avoid every prime `<= p_k = x^(1/2)`. That is two residue classes removed per prime, i.e. sieve
**dimension kappa = 2**, with a sifting range up to `z = x^(1/2)`. Can a standard lower-bound sieve certify a
positive count there? (Open item from CIT-036.)

## 2. Source-reported facts (CIT-043, CIT-044)
* The **sifting limit** `beta_kappa` is the parameter beyond which a lower-bound sieve yields a positive lower bound
  (Franze, arXiv:1012.3809, Introduction).
* For `kappa = 2`: `beta_2 = 4.266` for the Diamond–Halberstam–Richert sieves and `beta_2 = 4.516` for the
  `Lambda^2 Lambda^-` sieve (Franze, Table 1); Blight (PhD thesis, 2010, as cited there) gives `beta_2 < 4.45`.
* **Parity problem:** "sieve procedures cannot distinguish between numbers with an even number of prime factors and an
  odd number of prime factors" (Ford, arXiv:math/0401215, Introduction).

## 3. Arithmetic consequence (**derived by exact arithmetic; convention noted**)
Convention (standard; the source's displayed exponent was garbled in extraction, so confirm it in the primary text):
with level of distribution equal to the sequence length `x`, a lower-bound sieve of dimension `kappa` is
positive for `z <= x^(1/beta_kappa)`. Reaching `z = x^(1/2)` then needs `beta_kappa <= 2`; equivalently a level of
distribution `x^(beta_kappa/2)`.

| Sieve (kappa = 2) | `beta_2` | Reachable `z` | Level needed for `z = x^(1/2)` |
|---|---:|---:|---:|
| DHR | 4.266 | `x^0.234` | `x^2.13` |
| `Lambda^2 Lambda^-` | 4.516 | `x^0.221` | `x^2.26` |
| Blight bound | 4.45 | `x^0.225` | `x^2.23` |

A level of distribution above `x^1` is not available for an arbitrary sequence of length `x`, so **no dimension-2 sieve of
the types above can give a positive lower bound for the window at `z = x^(1/2)`**, whatever the constants. For comparison,
`beta_1 = 2` is the usual value for dimension 1 (stated from memory, UNVERIFIED here): dimension 1 reaches exactly
`z = x^(1/2)` with level `x`, and no further.

## 4. What this does and does not explain
* It is consistent with EXP007–EXP019 and EXP024: the exact minima `M_k` are small but positive for every computed
  `k <= 9` (`2, 1, 2, 2, 3, 2, 4, 4, 5`), yet no sieve-only argument can prove positivity for all `k`. The empirical
  positivity is **not** explained by any sieve bound.
* Together with the parity problem (§2), it gives two independent reasons that elementary or classical sieve
  arguments stop short of Goldbach. Parity concerns what sieves can detect at all; the sifting limit concerns how far a
  dimension-2 lower-bound sieve can sift.
* It does **not** bear on results that use extra input beyond a plain sieve (weighted sieves, bilinear forms, as in the
  Chen and Li–Liu `(1+2)` and `(1+1.9)` statements): they prove almost-prime, not prime, summands.
* It does not show the window statement is false: the exact data say it holds for `k <= 9`.

## 5. Link to RQ1
The paired-Jacobsthal bound (PROOF_FRONTIER_022 §5) is also a two-class covering problem. An Iwaniec-type bound for the
classical (one-class) function has order `(k log k)^2`, the order of `p_k^2`, so the constant decides. The barrier above is the
sieve-side counterpart: dimension 2 loses the factor needed to reach `sqrt(x)`.

## 6. Next verification required
1. Confirm the sifting-range convention (§3) and `beta_2 = 4.266` in Diamond–Halberstam, *A higher-dimensional sieve
   method* (2008), chapter 17, or Halberstam–Richert; record exact theorem numbers.
2. Verify `beta_1 = 2` in a primary source before relying on the dimension-1 comparison.
3. Locate any claim of a dimension-2 lower-bound result reaching `sqrt(x)`; as far as this repo has found, none exists.
