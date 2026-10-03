# EXP003 — baseline scale-up

## Objective

Repeat the same correctness-first computation on a larger but still readily independently checked range after EXP001.

## Parameters

- Range: all even integers from 4 through 10000.
- Convention: unordered pairs; `p <= q`; equal primes and 2 allowed.
- Main method: sieve of Eratosthenes.
- Program-internal independent check: trial division for every input.
- Post-run check: pair arithmetic and grouped pair-count consistency.

## Result and limit

The run and stated checks completed successfully. See the raw-data manifest and processed summary for exact results. It establishes no theorem, conjecture, or novelty claim.
