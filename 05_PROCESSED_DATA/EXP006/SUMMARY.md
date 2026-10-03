# EXP006 — least Goldbach prime profile

## Input and method

This derived analysis streamed the frozen `EXP005/goldbach_pairs.csv`. The generator writes rows in increasing `n`, and for each fixed `n` in increasing prime `p`; therefore the first row for each `n` is its least prime summand under the project convention. The raw EXP005 files were not modified.

Analyzer source: `03_CODE/analyze_minimal_prime.cpp`, SHA-256 `6F726D7F1C5268CEB5087F1395C901AA4A6C7CCA4333CBAD59A11326775E9441`.

## Actual result

- Rows in derived profile: 49,999, one for every even `n` from 4 through 100000.
- Maximum observed least prime: `293`.
- Witness: `63274 = 293 + 62981`.
- Derived file SHA-256: `6EED86DE1D75BEF224E9B74626CC358DC1E1248AAE3DCDDB49A5C453028D0FCF`.

The witness and all pair rows come from the independently validated EXP005 pair dataset. This is a bounded computational observation. It is not a theorem, a new bound, or a novelty claim.

## Interpretation limit

The result refutes only finite-range claims stronger than “the least prime is at most 293” on this exact range. It does not imply a bound for larger even integers and does not address the existence of a universal bound.
