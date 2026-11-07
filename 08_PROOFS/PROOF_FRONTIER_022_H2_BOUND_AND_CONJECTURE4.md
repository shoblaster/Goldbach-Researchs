# Proof Frontier 022 — the paired-Jacobsthal bound and the tightened Goldbach statement

Status vocabulary as in `11_PAPER/RESEARCH_METHODS_AND_PROTOCOL.md`.
**NOVELTY NOT ESTABLISHED.** The implication in §2 is the source's
Proposition 3.2; §2 re-derives it to confirm the exact quantifiers. Strong
Goldbach: **OPEN; PROOF GAP — NOT PROVED.**

## 1. Statements (source-reported; CIT-029, CIT-030, CIT-041)

* `h2(k)` is the smallest `m` such that for every `(a,b)` with `2 | (b-a)` some
  `q in {1..m}` makes both `a+q` and `b+q` coprime to every prime `p_1..p_k`.
* **Hypothesis H** (the source's Conjecture 6): `h2(k) < p_k^2 - p_k` for all `k >= 3`.
* **Conjecture 4** (tightened Goldbach): for even `N = 2n`, `n >= 6`, let `p = p_k`
  be the prime with `p_k^2 + p_k <= N < p_{k+1}^2 + p_{k+1}`. Then there are
  primes `q1, q2` with `p_k < q1 < p_k^2` and `q1 + q2 = N`.
* **Proposition 3.2 (source):** H implies Conjecture 4.

## 2. Re-derivation of H ⇒ Conjecture 4 for `k_n >= 3` (**PROVED**, elementary)

Assume `h2(k) <= p^2 - p - 1` with `p = p_k`, `k >= 3`, and `p^2 + p <= N < p_{k+1}^2 + p_{k+1}`.
Take `(a,b) = (p, p - N)`; `b - a = -N` is even. By H there is `q <= p^2 - p - 1`
with `p+q` and `p-N+q` both coprime to `p_1..p_k`. Put `q1 = p + q` and `q2 = N - q1`
(so `p - N + q = -q2`).

1. `p + 1 <= q1 <= p^2 - 1`, so `q1 < p^2`. It has no prime factor `<= p`, and a composite
   `q1 < p^2` would have one, so `q1` is **prime**. Since `q1 > p` it is `>= p_{k+1}`.
2. `q2 = N - q1 >= p^2 + p - (p^2 - 1) = p + 1 > 1`, and `q2` has no prime factor `<= p`.
3. `q2 = N - q1 <= N - p_{k+1} < p_{k+1}^2`. A composite number with no prime factor
   `<= p_k` is `>= p_{k+1}^2`, so `q2` is **prime**.

Hence `q1 + q2 = N` with `p_k < q1 < p_k^2`, both prime. ∎ This uses only the
divisor argument; no analytic input. The case `k_n = 2` (`12 <= N <= 28`) is finite
and is covered by direct enumeration (EXP023 §B).

## 3. Boundary slip in the source's case split (**VERIFIED arithmetic**; source text as extracted)

The source's proof says "for `6 <= n < 30` we get `k_n = 2`, `p = 3`, `3 < q1 < 9`", lists examples up
to `28 = 5 + 23`, and then treats "`n >= 30`" with `k_n >= 3`. By the source's own definition,
`k_n = 2` exactly for `12 <= N <= 29` (`6 <= n <= 14`); `k_n = 3` for `30 <= N <= 55`
(`15 <= n <= 27`); `k_n = 4` for `56 <= N <= 131`. The thresholds are written in `n` but
behave like thresholds in `N = 2n`. Read literally, `n = 15..29` (`N = 30..58`) lie in
neither branch as stated. This is a harmless typo: with the thresholds read as
`N < 30` / `N >= 30`, every `N >= 12` is covered, and §2 applies for `k_n >= 3` including
`h2(3) = 18 < 20`. EXP023 §B confirms Conjecture 4 directly for all even `N` in `[12, 2e7]`,
including `N = 30..58`. *Caveat:* the source wording was read through two separate
WebFetch extractions of the arXiv PDF (the shell cannot reach arXiv), not from a downloaded copy.

## 4. Finite evidence on H (EXP023)

* Source Table 1 gives `h2(k)` for `k = 3..21` (transcribed, CIT-041); H holds on all 19 rows.
* `k = 3..9` independently re-certified with CP-SAT and (for `k <= 8`) HiGHS;
  `k = 10` status is recorded in `06_EXPERIMENTS/EXP023_H2_RATIO_FRONTIER/README.md`.
* The tightest rows are `k = 6` (`150` vs `156`; ratio `25/26`; margin `6`) and `k = 3`
  (`18` vs `20`). Writing `c_k = (p_k^2 - h2(k))/p_k`, the minimum over the table is
  `c_3 = 7/5`, then `c_6 = 19/13`; `c_k` grows to about `37` at `k = 21`.
  So on this table there is substantial room for `k >= 7`, but no bound of the form
  `p_k^2 - c p_k` with `c >= 7/5` holds at `k = 3`.
* For `k >= 7` the ratio `h2/(p_k^2 - p_k)` is `<= 0.7544` and is **not monotone** (it drifts toward
  about `0.5`). This is a description of 15 data points, not a trend claim.

## 5. What a proof of H would have to do (**analysis; not a result**)

* H is a **worst-case, universal** statement: by CRT (CIT-031) it ranges over every choice of two
  nonzero residue classes modulo each prime `5..p_k`. Conjecture 4 only needs the one
  progression `(p, p - N)`. EXP023 §B shows the gap on all tested instances: the least valid
  `q1` reaches at most `0.030 p^2` for `k = 20` and `0.0003 p^2` for `k = 600`, while the worst-case
  `h2/p^2` is about `0.5`. Proving H would therefore prove far more than Goldbach.
* H is a covering problem with **two** classes per prime, i.e. sieve dimension 2. The classical
  Jacobsthal function (one class per prime) has Iwaniec's bound `g(n) <= X (k log k)^2` with
  an unspecified constant `X`, `k = omega(n)` (CIT-042). Since `p_k ~ k log k`, that order equals
  `p_k^2`: even for the classical function, the order matches the needed bound and **the
  constant decides**. A dimension-2 analogue with an explicit constant `< 1` is the missing
  statement. Whether such an analogue is in the literature is **UNVERIFIED**; this repo has
  not found one. This ties RQ1 to RQ2 (`research/sieve-dimension-barrier`).

## 6. Next verification required

1. Search the primary literature for any dimension-2 (paired) analogue of Iwaniec's bound, and for any
   proved upper bound on `h2`; record the result either way.
2. Independently certify `h2(k)` for `k >= 10` (CP-SAT/HiGHS limits are noted in EXP023); do not
   treat transcribed `k >= 10` rows as verified.
3. Obtain the source PDF text locally and confirm §3 against it.

## 7. Update 2026-11-08
EXP030 (`06_EXPERIMENTS/EXP030_H2_EXACT_COVER_SEARCH/`) certifies `h2(k)` for `k = 3..10` with an exhaustive
solver-free search, including `h2(10) = 450`, which CP-SAT could not resolve in EXP023. So §4's "k = 10 status"
is now: certified. Rows `k >= 11` of the source table remain transcribed.
