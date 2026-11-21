#!/usr/bin/env python3
"""Randomised soundness test of the pruning bound used in h2_cover_search.cpp (see 08_PROOFS/PROOF_FRONTIER_024).
For random partial states (some primes already given 0/1/2 classes, a random subset of positions already covered) of small
instances, compute the TRUE maximum number of additional positions the remaining quotas can cover by full enumeration, and
check it never exceeds the bound  sum_p (sum of the t_p largest class gains among uncovered positions, excluding used classes).
usage: python3 bound_soundness_test.py [trials] [seed]"""
import itertools, random, sys
primes_all=[5,7,11,13,17]
def run(trials,seed):
    rnd=random.Random(seed); viol=0; tight=0; checked=0
    for _ in range(trials):
        k=rnd.choice([3,4,5,6]); P=primes_all[:k-2]; L=rnd.choice([10,16,24,30])
        chosen={p:set(rnd.sample(range(1,p),rnd.choice([0,1,2]))) for p in P}
        unc=set(q for q in range(1,L+1) if not any(q%p in chosen[p] and q%p for p in P))
        unc={q for q in unc if rnd.random()<0.9}
        gains={}
        bound=0; opts=[]
        for p in P:
            t=2-len(chosen[p])
            if t==0: continue
            g={r:sum(1 for q in unc if q%p==r) for r in range(1,p) if r not in chosen[p]}
            bound+=sum(sorted(g.values(),reverse=True)[:t])
            opts.append([ [r for r in c] for c in itertools.combinations(sorted(g),t)])
        best=0
        for combo in itertools.product(*opts):
            cov=set()
            for p,rs in zip([p for p in P if len(chosen[p])<2],combo):
                for q in unc:
                    if q%p in rs: cov.add(q)
            best=max(best,len(cov))
        checked+=1
        if best>bound: viol+=1; print("VIOLATION",P,L,chosen,best,bound)
        if best==bound: tight+=1
    print(f"trials {checked} violations {viol} tight(best==bound) {tight}")
    return viol
if __name__=="__main__":
    t=int(sys.argv[1]) if len(sys.argv)>1 else 300; s=int(sys.argv[2]) if len(sys.argv)>2 else 1
    sys.exit(1 if run(t,s) else 0)
