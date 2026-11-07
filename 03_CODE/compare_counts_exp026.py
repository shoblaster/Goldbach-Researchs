"""EXP026: compare the C++ pair-accumulation counts with the FFT counts (EXP025 method)
and with the frozen EXP005 count file. Usage (repository root):
    python 03_CODE/compare_counts_exp026.py 06_EXPERIMENTS/EXP026_INDEPENDENT_CROSSCHECK_TO_1E6/goldbach_counts_1e6.csv
"""
import sys, csv, hashlib
import numpy as np
from scipy.signal import fftconvolve

N = 1_000_000
path = sys.argv[1]
s = np.ones(N + 1, dtype=bool); s[:2] = False
for i in range(2, int(N ** 0.5) + 1):
    if s[i]: s[i*i::i] = False
f = s.astype(np.float64)
r = np.rint(fftconvolve(f, f)[: N + 1]).astype(np.int64)
ev = np.arange(4, N + 1, 2)
G = (r[ev] + s[ev // 2].astype(np.int64)) // 2

cpp = {}
with open(path) as fh:
    rd = csv.reader(fh); next(rd)
    for n, c in rd: cpp[int(n)] = int(c)
print(f"cpp rows={len(cpp)}")
mm = sum(1 for n in ev if cpp[int(n)] != int(G[(n - 4) // 2]))
print(f"mismatches C++ vs FFT over 4..{N}: {mm}")
e5 = {}
with open("04_RAW_DATA/EXP005/goldbach_counts.csv") as fh:
    rd = csv.reader(fh); next(rd)
    for n, c in rd: e5[int(n)] = int(c)
print(f"EXP005 rows={len(e5)} mismatches C++ vs EXP005: {sum(1 for n in e5 if cpp[n] != e5[n])}")
print("sha256 of C++ counts file:", hashlib.sha256(open(path, 'rb').read()).hexdigest())
