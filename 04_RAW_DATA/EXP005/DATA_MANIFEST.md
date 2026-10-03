# EXP005 raw-data manifest

Raw files were generated once on 2026-09-09 and must not be modified in place.

| File | SHA-256 | Description |
|---|---|---|
| `goldbach_counts.csv` | `B83E4D04647F574E2C264755A9F1C76889C4011B4679546F86C9D8D94BADBCAF` | One unordered representation count for each even `n` from 4 through 100000. |
| `goldbach_pairs.csv` | `51D55924731830C713E2C4284C18BAAC65E084A83854AD234285B3188C65D1F9` | Every counted pair `(p,q)`, with `p <= q`. |
| `metadata.txt` | `7C408E18F260CA8E16D1AC18C5DC5EE1CE441F2B00B25BA65D80B1FF0552E81E` | Program-recorded parameters and runtime. |

Baseline snapshot: `03_CODE/versions/EXP005_v3.cpp`, SHA-256 `4F70C8885A07DE7CF1E191711CE6B440ED2CA980F87EFE9305926022E16A4038`.

The main run did **not** perform per-value trial division. This was intentional and is not a substitute for validation: the saved counts and pair rows were subsequently validated by separate programs. See `06_EXPERIMENTS/EXP005/VALIDATION.md`.
