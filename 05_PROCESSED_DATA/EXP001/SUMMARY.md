# EXP001 derived summary

Derived from the frozen raw CSV files listed in `04_RAW_DATA/EXP001/DATA_MANIFEST.md`.

| Quantity | Value |
|---|---:|
| Tested even integers | 499 (`4` through `1000`, inclusive) |
| Sum of stored representation counts | 8,222 |
| Minimum stored `G(n)` | 1 |
| Maximum stored `G(n)` | 52 |
| Values with `G(n)=0` | 0 |
| Stored pair rows | 8,222 |
| Program-reported elapsed time | 0.013137 seconds |

Post-run integrity checks actually run:

- every stored pair satisfied `p <= q` and `p + q = n`;
- grouping `goldbach_pairs.csv` by `n` exactly matched every count in `goldbach_counts.csv` (0 mismatches);
- the program itself compared every count in this range with a trial-division implementation and completed without a validation failure.

This is a computational observation about this bounded experiment only. It is not a proof of the Strong Goldbach Conjecture, a claim about values above 1000, or a novelty claim.
