# EXP003 independent validation

Date: 2026-09-09

`03_CODE/validate_goldbach.cpp` was compiled and run against the frozen `goldbach_counts.csv` file.

- Validator source SHA-256: `4E979D87B315F6024743D60672703F5D6C40B649535FDE0FC8B69FA04F9B4A25`
- Command: `g++ -std=c++17 -O2 -Wall -Wextra validate_goldbach.cpp -o validate_goldbach.exe`, followed by `validate_goldbach.exe ../04_RAW_DATA/EXP003/goldbach_counts.csv`
- Actual output: `Validated rows=4999, mismatches=0`

The validator reads only the count CSV, constructs its own byte-based sieve, and loops over every potential addend `p` from 2 through `n/2`. It does not call or include any baseline-program functions and does not consume the pair CSV.

This materially improves confidence in the finite EXP003 count dataset. It remains neither a proof of an unbounded statement nor a novelty claim.
