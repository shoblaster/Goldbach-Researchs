# Proof insight 005 — adversarial survivors of any fixed local sieve

**Status: PROVED LIMITATION; not a Goldbach theorem.**

## Statement

Fix any finite sieve bound `B >= 2`. There exist an even integer `E` and an integer candidate `a` such that:

1. neither `a` nor `E-a` is divisible by any prime `r <= B`; and
2. both `a` and `E-a` are composite.

Thus avoiding all prime divisors up to a fixed bound cannot, by itself, certify that both addends are prime.

## Construction

Choose odd primes `q,r > B`; such primes exist by the standard infinitude of primes. Set

```
a = q^2,
E = q^2 + r^2.
```

Because `q` and `r` are odd, `E` is even. Also `E-a=r^2`.

## Proof

Every prime divisor of `a=q^2` is `q`, and `q>B`. Therefore no prime `<=B` divides `a`. Likewise, the only prime divisor of `E-a=r^2` is `r>B`, so no prime `<=B` divides `E-a`.

But `a=q^2` and `E-a=r^2` are both composite because `q,r>1`. This proves the statement.

## Interpretation

The construction does not produce a counterexample to Goldbach: `a` is intentionally composite, so it is not a valid Goldbach summand. Its role is narrower and exact: a fixed local sieve can leave composite survivors that look prime to every tested small modulus.

If a procedure begins with actual primes `a`, this obstruction moves to the complementary value `E-a`: checking only small divisors of the complement still cannot certify primality unless the sieve reaches its square-root threshold.

Therefore any proof based on local congruence information needs an additional global argument about actual primes and their correlations. Local admissibility alone is insufficient.

## Concrete sanity check (not part of proof)

For `B=10`, choose `q=11`, `r=13`. Then `E=290`, `a=121`, and `E-a=169`. Neither 121 nor 169 is divisible by 2, 3, 5, or 7, while both are visibly composite squares.
