"""EXP028: counts-only G(n) for even n in 4..10**7 by FFT convolution, with two validations:
(1) exact comparison with the independent C++ counts of EXP026 on 4..10**6;
(2) direct per-n counting (set membership over primes <= n/2) for 3000 random even n in (10**6, 10**7].
Stores a summary only (no per-n pairs). Usage (repository root):
    python 03_CODE/goldbach_counts_1e7.py 06_EXPERIMENTS/EXP028_COUNTS_TO_1E7
Memory: about 2 GB peak. Requires numpy and scipy.
"""
import sys, csv, hashlib, random
import numpy as np
from scipy.signal import fftconvolve

N = 10_000_000
out = sys.argv[1]
s = np.ones(N + 1, dtype=bool); s[:2] = False
for i in range(2, int(N ** 0.5) + 1):
    if s[i]: s[i*i::i] = False
f = s.astype(np.float64)
r = fftconvolve(f, f)[: N + 1]
rr = np.rint(r).astype(np.int64)
print("max |fft - rint| =", float(np.max(np.abs(r - rr))))
del r, f
ev = np.arange(4, N + 1, 2)
G = ((rr[ev] + s[ev // 2].astype(np.int64)) // 2).astype(np.int32)
assert np.all((rr[ev] + s[ev // 2].astype(np.int64)) % 2 == 0)
del rr

# (1) exact comparison on 4..1e6 with EXP026 C++ counts
bad = 0; rows = 0
with open("06_EXPERIMENTS/EXP026_INDEPENDENT_CROSSCHECK_TO_1E6/goldbach_counts_1e6.csv") as fh:
    rd = csv.reader(fh); next(rd)
    for n, c in rd:
        rows += 1
        if G[(int(n) - 4) // 2] != int(c): bad += 1
print(f"EXP026 rows={rows} mismatches={bad}")

# (2) direct per-n counting on random n in (1e6, 1e7]
primes = np.nonzero(s)[0]
random.seed(7)
sample = sorted(random.sample(range(500_001, N // 2 + 1), 3000))
bad2 = 0
for h in sample:
    n = 2 * h
    ps = primes[: np.searchsorted(primes, n // 2, side="right")]
    cnt = int(np.count_nonzero(s[n - ps]))
    if cnt != int(G[(n - 4) // 2]): bad2 += 1
print(f"direct per-n check: samples={len(sample)} mismatches={bad2}")

print(f"even n in 4..{N}: {len(ev)}; zero counts: {int((G == 0).sum())}; min G={int(G.min())}; max G={int(G.max())} at n={int(ev[np.argmax(G)])}")
k = 100 + int(np.argmin(G[100:]))
print(f"smallest G for n>=204: {int(G[k])} at n={int(ev[k])}")
# decade summaries of the minimum of G(n)/(n/ln(n)^2) for n >= 1e4
nn = ev.astype(np.float64); q = G / (nn / np.log(nn) ** 2)
for lo, hi in [(1e4, 1e5), (1e5, 1e6), (1e6, 1e7 + 1)]:
    m = (nn >= lo) & (nn < hi)
    print(f"  n in [{lo:.0e},{hi:.0e}): min G/(n/ln^2 n) = {q[m].min():.4f}, mean = {q[m].mean():.4f}")
print("sha256 of int32 count array:", hashlib.sha256(G.tobytes()).hexdigest())
