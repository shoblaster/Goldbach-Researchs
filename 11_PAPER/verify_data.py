#!/usr/bin/env python3
"""Independent consistency checks for the paper's data. Exit code 0 = all pass.
 1. p_k recomputed by a prime sieve; bound p_k^2-p_k; omega2=(h-6)/6 integral; H holds on all rows
 2. node counts k=3..8 recomputed by compiling and running 03_CODE/h2_cover_search.cpp (needs g++, <1 min)
    (pass --fast to skip step 2)"""
import csv, os, subprocess, sys, re
R=os.path.dirname(os.path.abspath(__file__)); rd=lambda n:list(csv.DictReader(open(f"{R}/data/{n}")))
pr=[];n=2
while len(pr)<30:
    if all(n%p for p in pr): pr.append(n)
    n+=1
bad=0
for r in rd("h2_table.csv"):
    k=int(r["k"]); p=pr[k-1]; h=int(r["h2_source"])
    ok=(int(r["p_k"])==p and (h-6)%6==0 and int(r["omega2"])==(h-6)//6 and int(r["bound_pk2_minus_pk"])==p*p-p and h<p*p-p)
    bad+=not ok
    if not ok: print("FAIL row",k)
print("table rows ok" if not bad else "TABLE FAILURES")
if "--fast" not in sys.argv:
    exe="/tmp/h2_cs"; subprocess.check_call(["g++","-std=c++17","-O3",f"{R}/../03_CODE/h2_cover_search.cpp","-o",exe])
    for r in rd("infeasibility_nodes.csv"):
        k=int(r["k"])
        if k>8: continue
        o=subprocess.run([exe,str(k),r["L_infeasible"]],capture_output=True,text=True).stdout
        m=re.search(r"INFEASIBLE nodes (\d+)",o); got=int(m.group(1)) if m else None
        ok=got==int(r["nodes"]); bad+=not ok; print("k",k,"nodes",got,"expected",r["nodes"],"OK" if ok else "FAIL")
sys.exit(1 if bad else 0)
