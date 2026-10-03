# EXP003 derived summary

Derived from the frozen files listed in `04_RAW_DATA/EXP003/DATA_MANIFEST.md`.

| Quantity | Value |
|---|---:|
| Tested even integers | 4,999 (`4` through `10000`, inclusive) |
| Sum of stored representation counts | 425,751 |
| Minimum stored `G(n)` | 1 |
| Maximum stored `G(n)` | 329 |
| Values with `G(n)=0` | 0 |
| Stored pair rows | 425,751 |
| Program-reported elapsed time | 0.518024 seconds |

Checks actually run after file generation: every stored row obeyed `p <= q` and `p+q=n`; grouping all pair rows by `n` yielded exactly the stored count for every `n` (0 mismatches). The executable also ran its separate trial-division count for every tested input without reporting a validation failure.

This is limited computational evidence for this finite range and convention. It is neither a proof of Strong Goldbach nor a novelty claim.
