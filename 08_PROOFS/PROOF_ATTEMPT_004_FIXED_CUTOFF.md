# Proof attempt 004 — fixed small-prime cutoff

**Status: DISPROVED AS A FINITE-RANGE STRATEGY for the tested cutoff.**

## Candidate shortcut

Consider the proposed finite-range statement:

> Every even `E` in `4..100000` has a Goldbach representation with smaller prime summand `p <= 281`.

The cutoff `281` is the largest prime below the observed witness value `293`.

## Counterexample from validated data

The EXP006 derived profile reports that the first representation for

```
E = 63274
```

has

```
63274 = 293 + 62981.
```

Because the EXP005 generator enumerates candidate primes in increasing order and the complete pair file was independently validated, the first row for `63274` certifies that no pair with smaller prime `p < 293` occurs in that frozen dataset. Therefore the proposed cutoff `p <= 281` fails at `E=63274`.

## Scope

This is a computational counterexample to one finite cutoff on one finite range. It does not prove that no larger cutoff works, does not establish a universal lower bound, and does not disprove Strong Goldbach.

## Proof-design lesson

A proof that checks only a fixed list of small primes cannot cover even this finite range unless its cutoff is at least 293. More importantly, increasing the cutoff does not itself solve the global simultaneous-primality problem; it only moves the same unresolved search farther out.
