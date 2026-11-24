# EXP028: counts-only pipeline to 10^7

Code: `03_CODE/goldbach_counts_1e7.py` (numpy, scipy; about 2 GB peak memory, about 5 s). Output: `RAW_OUTPUT.txt`. No per-n file is stored; the count array is identified by its SHA-256.

Convention: unordered pairs p <= q with p + q = n, equal primes and 2 included.

Method: FFT convolution of the prime indicator up to 10^7, converted to unordered counts. The largest distance of any FFT value from the nearest integer was 1.5e-10, so rounding is safe.

Validation:
1. Exact comparison on 4..10^6 with the independent C++ counts of EXP026: 499,999 rows, 0 mismatches.
2. Direct per-n counting (primes <= n/2 and a primality lookup of n - p) for 3,000 random even n in (10^6, 10^7]: 0 mismatches.

Observed results (finite computation only):
- 4,999,999 even n in 4..10^7: 0 zero counts, min G = 1, max G = 124,180 at n = 9,699,690 (= 2*3*5*7*11*13*17*19, a primorial).
- Smallest G for n >= 204 is 6 at n = 212, unchanged from the smaller ranges.
- G(n) / (n / ln^2 n) has minimum 0.724, 0.735, 0.744 and mean 1.226, 1.183, 1.152 on [10^4,10^5), [10^5,10^6), [10^6,10^7]. The minimum rises and the mean falls slowly with n, as lower-order terms in the heuristic predict.
- SHA-256 of the int32 count array (n = 4, 6, ..., 10^7 in order): d5163bee37f64e0c7ccf48abe50db08e195f93ad702a9853e055aa863fd9d5ac.

Limits: counts above 10^6 are covered by a sampled direct check (3,000 values), not by a full second implementation. No theorem, no novelty, nothing above 10^7. This range is far below the published verification bound of 4*10^18.
