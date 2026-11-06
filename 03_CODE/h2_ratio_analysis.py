"""Descriptive analysis of the source-reported paired-Jacobsthal table.

Inputs are TRANSCRIBED from Table 1 of Ziller & Morack, arXiv:1706.03668
(CIT-029); k=3..9 are independently re-certified by h2_frontier_verify.py
(EXP017 + EXP023).  Nothing here is a theorem or an extrapolation.
Exact fractions are used throughout.
"""
from fractions import Fraction as F
from math import log

P = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
     67, 71, 73]
H2 = [2, 6, 18, 30, 66, 150, 192, 258, 366, 450, 570, 708, 894, 1044, 1284,
      1422, 1656, 1902, 2190, 2460, 2622]

print("k  p_k  h2    p^2-p  margin  h2/(p^2-p)  h2/p^2   h2/(p*k)  h2/(p*ln p)")
rows = []
for k in range(3, 22):
    p, h = P[k - 1], H2[k - 1]
    bound = p * p - p
    assert h < bound, k          # the source's conjectured bound, finite check
    r = F(h, bound)
    rows.append((k, p, h, bound, r))
    print(f"{k:<2} {p:<4} {h:<5} {bound:<6} {bound-h:<7} {float(r):.4f}     "
          f"{h/p/p:.4f}   {h/(p*k):.3f}     {h/(p*log(p)):.3f}")

mx = max(rows, key=lambda t: t[4])
print()
print("max ratio h2/(p^2-p) over k=3..21: k=%d, %s = %.6f" %
      (mx[0], mx[4], float(mx[4])))
tail = [t for t in rows if t[0] >= 7]
print("max ratio over k>=7: k=%d, %.6f" %
      (max(tail, key=lambda t: t[4])[0], float(max(t[4] for t in tail))))
dec = all(rows[i][4] > rows[i + 1][4] for i in range(len(rows) - 1))
print("ratio strictly decreasing over all k=3..21:", dec)
dec7 = all(tail[i][4] > tail[i + 1][4] for i in range(len(tail) - 1))
print("ratio strictly decreasing over k=7..21:", dec7)
viol = [(tail[i][0], float(tail[i][4]), float(tail[i+1][4]))
        for i in range(len(tail) - 1) if tail[i][4] <= tail[i + 1][4]]
print("non-decreasing steps for k>=7:", viol)
print("last five ratios:", [round(float(t[4]), 4) for t in rows[-5:]])

# Largest c such that h2(k) <= p_k^2 - c*p_k holds on the table, per k.
print()
print("headroom c_k = (p_k^2 - h2(k)) / p_k  (the bound p^2-p needs c_k > 1):")
cs = [(t[0], F(t[3] + t[1] - t[2], t[1])) for t in rows]   # p^2 - h2 = bound + p - h
for k, c in cs:
    print(f"  k={k:<2} c_k={float(c):.4f}")
low = sorted(cs, key=lambda t: t[1])[:3]
print("three smallest c_k:", [(k, str(c), round(float(c), 4)) for k, c in low])
print("min over table: k=%d, c=%s" % (low[0][0], low[0][1]))
