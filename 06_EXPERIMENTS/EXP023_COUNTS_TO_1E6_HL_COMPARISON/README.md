# EXP023: counts to 10^6 and Hardy-Littlewood comparison

Code: `03_CODE/goldbach_counts_1e6_hl_comparison.py` (numpy, scipy). Output: `RAW_OUTPUT.txt`, `hl_ratio_sample.csv`.

Convention: same as the baseline. G(n) counts unordered prime pairs p <= q with p + q = n; equal primes and 2 included.

Method: ordered counts from an FFT convolution of the prime indicator up to 10^6, converted to unordered counts. This is a different method from the sieve and trial-division paths used for EXP001-EXP005.

Observed results (finite computation only):
- Recomputed G(n) matches all 49,999 rows of the frozen `04_RAW_DATA/EXP005/goldbach_counts.csv` with 0 mismatches.
- All 499,999 even n in 4..10^6 have G(n) >= 1. Maximum G(n) = 15,594. Smallest G(n) for n >= 204 is 6 at n = 212.
- Ratio G(n) / (C2 * S(n) * n / ln^2 n) on 20,813 sampled n >= 1000: mean 1.33 on [10^3,10^4), 1.24 on [10^4,10^5), 1.20 on [10^5,5*10^5), 1.18 on [5*10^5,10^6]. The simple form is a heuristic with known lower-order terms, so a ratio above 1 that falls with n is expected.

Not claimed: no theorem, no novelty, nothing beyond 10^6. Counts and the H-L comparison have prior art (see CIT-001 to CIT-005). The FFT result was not cross-checked against a second implementation above 10^5.
