# EXP005 validation record

## Count-file validation

The independently written `validate_goldbach.cpp` was run on the frozen count CSV.

- Validator source SHA-256: `4E979D87B315F6024743D60672703F5D6C40B649535FDE0FC8B69FA04F9B4A25`
- Actual output: `Validated rows=49999, mismatches=0`

It builds its own byte sieve and recomputes each count by checking every candidate addend through `n/2`.

## Pair-file validation

The separately written streaming `validate_goldbach_pairs.cpp` was run on the frozen pair and count files. Its captured raw output is `PAIR_VALIDATION_OUTPUT.txt`.

- Validator source SHA-256: `DDE1A5C63E2E3A3464F98F5F4075C18051B99D38DC85969C22129ADF24521590`
- Actual output: `Validated pair rows=25366983, malformed=0, count_mismatches=0`

It builds its own byte sieve, checks every row for `p <= q`, `p+q=n`, and primality of both addends, then compares per-`n` pair totals to the count file.

These checks improve confidence in this finite output. They do not constitute a proof beyond 100000 or a novelty claim.
