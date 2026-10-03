# EXP001 raw-data manifest

Raw files were generated once on 2026-09-09. They must not be modified in place.

| File | SHA-256 | Description |
|---|---|---|
| `goldbach_counts.csv` | `3D23112780DEDFCA15D247CB419B4EC022C4AA24CC1E28052D1430DB75E684E5` | One unordered representation count for each even `n` from 4 through 1000. |
| `goldbach_pairs.csv` | `61B31EE3D924AA5859CC1A29764B43B90DDFF4976A73B31A1C3E1D431120DF33` | Every counted pair `(p,q)`, with `p <= q`. |
| `metadata.txt` | `54B51DD6218410A5DA8A8473BCED4D4B7DEADB3C1F0505DB50450C36ED7CEA49` | Program-recorded parameters, validation mode, and runtime. |

The code snapshot used was `03_CODE/versions/EXP001_v1.cpp`, SHA-256 `9B062266D1ED95D070096B802D22CF39348259F06D23CF5C98950CD407AE3D80`.

Compilation environment recorded after the run: `g++.exe (MinGW.org GCC-6.3.0-1) 6.3.0`; compiler command: `g++ -std=c++17 -O2 -Wall -Wextra goldbach_baseline.cpp -o goldbach_baseline.exe`.
