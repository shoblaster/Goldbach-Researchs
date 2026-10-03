# Lemma 001 — exact local count for Goldbach sieve candidates

**Status: PROVED RESULT (elementary); novelty not claimed.**

## Statement

Let `E` be an even integer and let `M` be an odd square-free positive integer. Define

```
R_E(M) = { a (mod M) : gcd(a(E-a), M) = 1 }.
```

Then

```
|R_E(M)| = product over primes r dividing M of c_r(E),
```

where

```
c_r(E) = r-1  if r divides E,
         r-2  if r does not divide E.
```

The empty product (when `M=1`) is `1`.

## Proof

Because `M` is square-free, the Chinese remainder map identifies residue classes modulo `M` with independent choices of residue classes modulo each prime `r | M`.

For a fixed odd prime `r | M`, the condition

```
r does not divide a(E-a)
```

is equivalent to requiring simultaneously

```
a != 0 (mod r)  and  a != E (mod r).
```

If `r | E`, the two excluded classes coincide, so exactly `r-1` of the `r` classes remain. If `r` does not divide `E`, they are distinct, so exactly `r-2` classes remain. Multiplying these independent counts over all `r | M` gives the formula.

For `M=1`, there is one residue class and the stated empty product is 1. This handles the edge case.

## Scope and limitation

This counts residue classes that avoid **only the prime divisors of M**. It does not prove that an integer in a surviving class is prime, nor that any integer in a particular finite interval lies in a surviving class. It therefore does not prove a Goldbach representation for any unverified `E`.

## Proof check

- Variables and assumptions are explicit: `E` even; `M` odd, square-free.
- The only structural tool used is the Chinese remainder theorem.
- The coincident-exclusion case `r | E` and the edge case `M=1` are handled.
- No unproved analytic estimate is used.

## Independent finite sanity checks

The formula was enumerated directly (not used as proof) for:

| E | M | product value | enumerated residue classes |
|---:|---:|---:|---:|
| 30 | 105 | 40 | 40 |
| 26 | 105 | 15 | 15 |
| 10 | 1 | 1 | 1 |

These checks include the `r | E` case and the `M=1` edge case. They do not replace the proof.
