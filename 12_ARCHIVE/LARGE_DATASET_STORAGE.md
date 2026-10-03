# Large raw dataset storage

The raw pair files below are preserved locally but intentionally excluded from the initial Git commit because each is approximately 468 MB and the current disk has no free space for Git LFS staging:

- `04_RAW_DATA/EXP004/goldbach_pairs.csv` — incomplete; **DO NOT USE**.
- `04_RAW_DATA/EXP005/goldbach_pairs.csv` — validated EXP005 pair output.

EXP005's SHA-256 is recorded in `04_RAW_DATA/EXP005/DATA_MANIFEST.md`:

`51D55924731830C713E2C4284C18BAAC65E084A83854AD234285B3188C65D1F9`

Git LFS patterns are already recorded in `.gitattributes`. On a machine with sufficient free space and an authenticated GitHub remote, remove these two ignore lines, run `git add` and `git lfs status`, then push the LFS objects. Do not delete or modify the local files before hashing and uploading them.
