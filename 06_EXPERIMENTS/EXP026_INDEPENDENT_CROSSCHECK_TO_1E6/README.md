# EXP026: independent cross-check of counts to 10^6

Closes the open item from EXP025 (counts above 10^5 had no second implementation).

Code: `03_CODE/goldbach_pair_accumulate_1e6.cpp` (counts), `03_CODE/compare_counts_exp026.py` (comparison).
Raw output: `RAW_OUTPUT_cpp.txt`, `RAW_OUTPUT_compare.txt`. Data: `goldbach_counts_1e6.csv`.

Method: the C++ program sieves primes to 10^6 and, for every prime pair p <= q with p + q <= 10^6, increments a counter at p + q. It uses no FFT and no per-n search, so it shares no code or method with EXP025 (FFT convolution) or with the EXP001-EXP005 sieve/trial-division path. Convention is unchanged: unordered pairs p <= q, equal primes and 2 included.

Observed results (finite computation only):
- 499,999 even n in 4..10^6: 0 zero counts, min G = 1, max G = 15,594.
- 0 mismatches between the C++ counts and the EXP025 FFT counts over all 499,999 values.
- 0 mismatches between the C++ counts and all 49,999 rows of frozen `04_RAW_DATA/EXP005/goldbach_counts.csv`.
- SHA-256 of `goldbach_counts_1e6.csv`: 4073b54273ee5f18cd5218579e768e9eb1bacb29846a2ca52c916b5112cb644c.
- Runtime about 3.5 s (single thread, g++ -O2).

Not claimed: no theorem, no novelty, nothing above 10^6. Agreement of two programs is strong evidence the counts are right, not a formal proof of program correctness.
