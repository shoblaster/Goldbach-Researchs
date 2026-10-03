# EXP003 raw-data manifest

Raw files were generated once on 2026-09-09 and must not be modified in place.

| File | SHA-256 | Description |
|---|---|---|
| `goldbach_counts.csv` | `4396DA3ED42BD787F7CF35BE2A37CD378BD72E3B2E3AC130984FE64B1F01847F` | One unordered representation count for every even `n` from 4 through 10000. |
| `goldbach_pairs.csv` | `37228993F747B1F8396F826D4E880095388597715C6530E04EF7C7A30A88FF77` | Every counted pair `(p,q)`, with `p <= q`. |
| `metadata.txt` | `3A342B1CBFAB8B1F437F0735A564B04C5332CA514F742F0667561288F8D28140` | Program-recorded parameters, validation mode, and runtime. |

Code snapshot: `03_CODE/versions/EXP003_v2.cpp`, SHA-256 `2A44FACFF8AC51600422732937964875E4F1EC976F01D0EBED146351FDCB4E45`.

Compiler command: `g++ -std=c++17 -O2 -Wall -Wextra goldbach_baseline.cpp -o goldbach_baseline.exe`. Environment: `g++.exe (MinGW.org GCC-6.3.0-1) 6.3.0`.
