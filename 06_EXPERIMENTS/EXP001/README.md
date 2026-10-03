# EXP001 — Goldbach baseline

## Objective

Validate a reproducible, explicit computation of unordered Goldbach representation counts before undertaking any pattern or novelty investigation.

## Parameters

- Range: even integers 4 through 1000, inclusive.
- Convention: count a pair once when `p <= q`; equal primes and 2 are allowed.
- Main method: sieve of Eratosthenes.
- Independent check: trial-division count for every tested value.
- Fixed checks: `G(4)=1`, `G(10)=2`, `G(28)=2` under this convention.

## Result

Completed successfully. See the raw-data manifest and processed summary. The only conclusion is that this implementation and its saved output passed the stated checks over the stated range.

## Limitation

No theorem, proof, conjecture, literature claim, or novelty claim resulted from EXP001.
