"""Finite check of the Ziller-Morack tightened Goldbach statement (CIT-030,
Conjecture 4).

For even N=2n with n>=6 let p=p_k be the unique prime with
p^2+p <= N < p_{k+1}^2 + p_{k+1}.  Claim: there are primes q1,q2 with
p < q1 < p^2 and q1+q2 = N.

This script (a) checks the claim for every even N in [12, NMAX] with a numpy
sieve, (b) cross-checks N <= 100000 with an independent pure-python trial
division search, (c) records the k_n ranges for small N (relevant to the
source's case split "6<=n<30 => k_n=2"), and (d) reports, per k, how deep into
the window (p, p^2) the least valid q1 must be taken (max over N of least q1,
divided by p^2).  A finite check is NOT a proof of the conjecture.
"""
import sys
from bisect import bisect_right
import numpy as np

NMAX = int(sys.argv[1]) if len(sys.argv) > 1 else 20_000_000

sieve = np.ones(NMAX + 1, dtype=bool)
sieve[:2] = False
for i in range(2, int(NMAX ** 0.5) + 1):
    if sieve[i]:
        sieve[i * i::i] = False
primes = np.nonzero(sieve)[0]
plist = [int(p) for p in primes]
thr = [p * p + p for p in plist]          # p_k^2 + p_k, k = index+1


def k_of(N):
    return bisect_right(thr, N)           # number of primes with p^2+p <= N


# (c) k_n structure for small N
print("N range for each k (N even, N>=12):")
for k in range(2, 6):
    lo = thr[k - 1]
    hi = thr[k] - 1
    print(f"  k={k} p_k={plist[k-1]}: {lo} <= N <= {hi}"
          f"  (n = N/2 in [{lo//2}, {hi//2}])")
assert k_of(12) == 2 and k_of(29) == 2 and k_of(30) == 3 and k_of(55) == 3
assert k_of(56) == 4
print("  => k_n=2 holds exactly for 6<=n<=14; for 15<=n<=29 (30<=N<=58) k_n>=3")

# (a) vectorised check
fail = 0
total = 0
per_k = {}
k = 2
while True:
    lo = thr[k - 1]
    if lo > NMAX:
        break
    hi = min(thr[k] - 1, NMAX)
    p = plist[k - 1]
    Ns = np.arange(lo + (lo & 1), hi + 1, 2, dtype=np.int64)
    if Ns.size:
        Q = primes[(primes > p) & (primes < p * p)] if p * p <= NMAX else \
            primes[primes > p]
        least = np.zeros(Ns.size, dtype=np.int64)
        rem = np.arange(Ns.size)
        for q in Q:
            q = int(q)
            if q >= p * p:
                break
            hit = sieve[Ns[rem] - q]
            least[rem[hit]] = q
            rem = rem[~hit]
            if rem.size == 0:
                break
        fail += int(rem.size)
        total += int(Ns.size)
        per_k[k] = (p, int(Ns.size), int(least.max()), int(rem.size))
    k += 1
print(f"\n(a) sieve check: even N in [12,{NMAX}] checked={total} failures={fail}")

# (b) independent pure-python cross-check
def isp(m):
    if m < 2:
        return False
    d = 2
    while d * d <= m:
        if m % d == 0:
            return False
        d += 1
    return True

bad = 0
cnt = 0
for N in range(12, 100_001, 2):
    kk = k_of(N)
    p = plist[kk - 1]
    ok = any(isp(q) and isp(N - q) for q in range(p + 1, p * p))
    bad += (not ok)
    cnt += 1
print(f"(b) independent trial-division check N<=100000: checked={cnt} failures={bad}")

# (d) depth into window
print("\n(d) per-k summary (k, p_k, #N, max over N of least q1, that/p_k^2, fails):")
for k in sorted(per_k):
    p, c, m, f = per_k[k]
    if k <= 20 or k % 100 == 0:
        print(f"  k={k:<4} p_k={p:<5} N_count={c:<9} max_least_q1={m:<6} "
              f"max_least_q1/p^2={m/(p*p):.4f} fails={f}")
overall = max(per_k.items(), key=lambda t: t[1][2] / (t[1][0] ** 2))
k, (p, c, m, f) = overall
print(f"\nlargest max_least_q1/p^2 over all k<= {max(per_k)}: k={k}, "
      f"p={p}, value={m/(p*p):.4f}")
