import itertools, math, random
import numpy as np
PR=[2,3,5,7,11,13,17,19,23,29,31,37,41,43]
def choices(k):
    ls=[]
    for q in PR[:k]:
        ls.append([(r,) for r in range(2)] if q==2 else list(itertools.combinations(range(q),2)))
    return ls
def min_surv(k,lo,L):
    """min survivors in window [lo, lo+L-1] over all class choices (exhaustive), numpy over windows"""
    ns=np.arange(lo,lo+L)
    best=10**9
    for ch in itertools.product(*choices(k)):
        alive=np.ones(L,bool)
        for q,c in zip(PR[:k],ch):
            r=ns%q
            for x in c: alive&=(r!=x)
        s=int(alive.sum())
        if s<best: best=s
    return best
# Fact A: translation invariance, exhaustive for k=3,4
for k in (3,4):
    L=PR[k-1]**2
    vals={a:min_surv(k,a+1,L) for a in (0,1,7,100,12345)}
    print("A translation invariance k=%d L=%d:"%(k,L),vals, "OK" if len(set(vals.values()))==1 else "FAIL")
# Fact B: h2(k)-1 = max coverable L (exhaustive k=1..4; k=5 too) via min_surv==0
H2=[2,6,18,30,66,150,192,258,366,450,570,708,894,1044,1284,1422,1656,1902,2190,2460,2622]
for k in range(1,5):
    L=1
    while min_surv(k,1,L)==0: L+=1
    print("B k=%d max coverable L=%d, h2=%d: %s"%(k,L-1,H2[k-1],"OK" if L==H2[k-1] else "FAIL"))
# Fact C: h2 non-decreasing; h2>=h (classical Jacobsthal, scan period) for k<=8; M_k >= floor(p^2/h2)
print("C monotone h2:",all(H2[i]<=H2[i+1] for i in range(20)))
def jacobsthal(k):
    P=1
    for q in PR[:k]: P*=q
    n=np.arange(P,dtype=np.int64); cop=np.ones(P,bool)
    for q in PR[:k]: cop&=(n%q!=0)
    idx=np.flatnonzero(cop); idx=np.append(idx,idx[0]+P)
    return int(np.diff(idx).max())   # h(k): longest gap between integers coprime to P
for k in range(1,9):
    h=jacobsthal(k); print("  k=%d h=%d h2=%d  h2>=h: %s"%(k,h,H2[k-1],H2[k-1]>=h))
M={3:2,4:2,5:3,6:2,7:4,8:4,9:5,10:10,11:8,12:13,13:16,14:14}
P=lambda k:PR[k-1]
print("D floor(p^2/h2) <= M_k:",all((P(k)**2)//H2[k-1]<=M[k] for k in M if k<=14))
print("  ratios h2/p^2:",[round(H2[k-1]/P(k)**2,2) for k in range(3,15)])
print("  H margin p^2-p-h2:",[P(k)**2-P(k)-H2[k-1] for k in range(3,15)])
