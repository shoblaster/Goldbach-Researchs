# EXP001 code

`goldbach_baseline.cpp` is a correctness-first C++17 program for the baseline experiment.

Counting convention: `G(n)` counts each unordered prime pair once, with `p <= q`; equal primes and the prime 2 are included.

Build from `03_CODE`:

```powershell
g++ -std=c++17 -O2 -Wall -Wextra goldbach_baseline.cpp -o goldbach_baseline.exe
```

Run the validated baseline from `03_CODE`:

```powershell
.\goldbach_baseline.exe 4 1000 ..\04_RAW_DATA\EXP001 EXP001
```

The program creates immutable raw-output candidates: `goldbach_counts.csv`, `goldbach_pairs.csv`, and `metadata.txt`. It uses an Eratosthenes sieve for the main calculation and checks each value in this first small range with a separate trial-division implementation. It also checks `G(4)=1`, `G(10)=2`, and `G(28)=2` before saving output.

Do not overwrite a completed raw dataset. Use a new experiment directory for a rerun or changed parameter set.

The optional fifth argument is `1` (default) to run a trial-division check for every count, or `0` to skip that expensive in-process check. `0` is permitted only when the separate validator is run and its result is recorded before interpreting the dataset.

`validate_goldbach.cpp` is a separate count-file validator. It uses a byte sieve and loops across every candidate addend rather than reusing the baseline program's functions or pair file. Build and run from `03_CODE`:

```powershell
g++ -std=c++17 -O2 -Wall -Wextra validate_goldbach.cpp -o validate_goldbach.exe
.\validate_goldbach.exe ..\04_RAW_DATA\EXP003\goldbach_counts.csv
```

`validate_goldbach_pairs.cpp` separately streams a pair CSV, checks pair arithmetic and primality, and compares pair totals with the saved count CSV. It is intended for full raw-pair validation without loading the pair file into memory.
