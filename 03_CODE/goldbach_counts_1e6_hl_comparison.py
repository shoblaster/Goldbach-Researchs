"""EXP023: independent recompute of unordered Goldbach counts G(n) for even n in 4..10**6
and comparison with the simple Hardy-Littlewood form C2 * S(n) * n / ln(n)^2.

Convention (same as the repository): G(n) counts unordered prime pairs p <= q, p + q = n,
equal primes and the prime 2 included.

Usage (from repository root):
    python 03_CODE/goldbach_counts_1e6_hl_comparison.py 06_EXPERIMENTS/EXP023_COUNTS_TO_1E6_HL_COMPARISON

Requires numpy and scipy. The H-L comparison is heuristic and proves nothing.
"""
import sys, csv, math
import numpy as np
from scipy.signal import fftconvolve

N = 1_000_000
out = sys.argv[1]

s = np.ones(N + 1, dtype=bool); s[:2] = False
for i in range(2, int(N ** 0.5) + 1):
    if s[i]:
        s[i * i::i] = False
primes = np.nonzero(s)[0]
f = s.astype(np.float64)

# ordered counts r(n) = #{(p,q): p+q=n} by FFT convolution of the prime indicator
r = np.rint(fftconvolve(f, f)[: N + 1]).astype(np.int64)
evens = np.arange(4, N + 1, 2)
ordered = r[evens]
half_prime = s[evens // 2].astype(np.int64)
assert np.all((ordered + half_prime) % 2 == 0)
G = (ordered + half_prime) // 2

# validate against the frozen EXP005 count file (4..100000)
exp = {}
with open("04_RAW_DATA/EXP005/goldbach_counts.csv") as fh:
    rd = csv.reader(fh); next(rd)
    for n, c in rd:
        exp[int(n)] = int(c)
mism = sum(1 for n in exp if G[(n - 4) // 2] != exp[n])
print(f"EXP005 rows={len(exp)} mismatches_vs_recompute={mism}")
print(f"even n in 4..{N}: {len(evens)}; zero counts: {int((G == 0).sum())}; min G={int(G.min())}; max G={int(G.max())}")
k = int(np.argmin(G[100:])) + 100
print(f"smallest G for n>=204: {int(G[k])} at n = {int(evens[k])}")

C2 = 1.0
for p in primes[1:2000]:
    C2 *= 1 - 1 / (p - 1) ** 2

def singular(n):
    S, m, d, ps = 1.0, n, 3, []
    while d * d <= m:
        if m % d == 0:
            ps.append(d)
            while m % d == 0:
                m //= d
        d += 2
    if m > 2:
        ps.append(m)
    for p in ps:
        if p > 2:
            S *= (p - 1) / (p - 2)
    return S

sample = evens[evens >= 1000]
rows = []
for n in sample[:: max(1, len(sample) // 20000)]:
    H = C2 * singular(int(n)) * n / math.log(n) ** 2
    g = int(G[(n - 4) // 2])
    rows.append((int(n), g, H, g / H))
arr = np.array([x[3] for x in rows])
print(f"samples={len(rows)} mean G/H={arr.mean():.4f} min={arr.min():.4f} max={arr.max():.4f}")
for lo, hi in [(1e3, 1e4), (1e4, 1e5), (1e5, 5e5), (5e5, 1e6)]:
    sel = np.array([x[3] for x in rows if lo <= x[0] < hi])
    print(f"  n in [{lo:.0e},{hi:.0e}): mean G/H={sel.mean():.4f} sd={sel.std():.4f}")

with open(f"{out}/hl_ratio_sample.csv", "w") as fh:
    fh.write("n,G,H_simple,ratio\n")
    for n, g, h, q in rows:
        fh.write(f"{n},{g},{h:.3f},{q:.5f}\n")
