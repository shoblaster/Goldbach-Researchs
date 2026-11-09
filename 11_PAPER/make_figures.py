#!/usr/bin/env python3
"""Regenerate every figure in the paper from the CSVs in data/ (no hidden inputs).
usage: python3 make_figures.py   -> figures/fig{1..4}.pdf and .png"""
import csv, os, matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
D=os.path.join(os.path.dirname(os.path.abspath(__file__)),"data"); F=os.path.join(os.path.dirname(os.path.abspath(__file__)),"figures")
rd=lambda n:list(csv.DictReader(open(os.path.join(D,n))))
plt.rcParams.update({"font.size":9,"axes.spines.top":False,"axes.spines.right":False,"axes.grid":True,"grid.alpha":.25})
def save(fig,n):
    fig.tight_layout(); fig.savefig(f"{F}/{n}.pdf"); fig.savefig(f"{F}/{n}.png",dpi=160); plt.close(fig)
T=rd("h2_table.csv"); k=[int(r["k"]) for r in T]; h=[int(r["h2_source"]) for r in T]; b=[int(r["bound_pk2_minus_pk"]) for r in T]
cert=[r["status"].startswith("certified") for r in T]
fig,ax=plt.subplots(1,2,figsize=(7.2,2.9))
ax[0].plot(k,b,"o-",ms=3,c="#b45309",label=r"$p_k^2-p_k$"); ax[0].plot(k,h,"s-",ms=3,c="#4338ca",label=r"$h_2(k)$ (source)")
ax[0].scatter([x for x,c in zip(k,cert) if c],[y for y,c in zip(h,cert) if c],s=36,facecolors="none",edgecolors="#047857",lw=1.4,label="re-certified (k$\\leq$10)")
ax[0].set_xlabel("k"); ax[0].set_ylabel("value"); ax[0].legend(frameon=False); ax[0].set_title("(a) $h_2(k)$ vs. the bound")
ax[1].plot(k,[x/y for x,y in zip(h,b)],"o-",ms=3,c="#4338ca"); ax[1].axhline(1,c="#b91c1c",ls="--",lw=1); ax[1].text(k[-1],1.01,"H fails above 1",ha="right",c="#b91c1c",fontsize=8)
ax[1].set_ylim(0,1.1); ax[1].set_xlabel("k"); ax[1].set_ylabel(r"$h_2(k)/(p_k^2-p_k)$"); ax[1].set_title("(b) ratio (max 0.9615 at k=6)")
save(fig,"fig1_h2_vs_bound")
N=rd("infeasibility_nodes.csv"); fig,ax=plt.subplots(figsize=(3.6,2.9))
ax.bar([int(r["k"]) for r in N],[int(r["nodes"]) for r in N],color="#4338ca"); ax.set_yscale("log"); ax.set_xlabel("k"); ax.set_ylabel("search nodes (log)")
ax.set_title("Cost of refuting $L=\\omega_2(k)+1$"); save(fig,"fig2_search_nodes")
M=rd("mk_minima.csv"); col={"two_methods":"#047857","CPSAT_only":"#9ca3af"}
fig,ax=plt.subplots(figsize=(3.6,2.9)); ax.bar([int(r["k"]) for r in M],[int(r["M_k"]) for r in M],color=[col.get(r["status"],"#b45309") for r in M])
ax.set_xlabel("k"); ax.set_ylabel("$M_k$"); ax.set_title("Fixed-window minima (green: 2 methods; orange: 1)"); ax.title.set_fontsize(8); save(fig,"fig3_mk")
S=rd("sieve_limits.csv"); fig,ax=plt.subplots(figsize=(5,2.2))
ax.barh([r["sieve"] for r in S],[float(r["reach_exponent_1_over_beta2"]) for r in S],color="#4338ca"); ax.axvline(.5,c="#b91c1c",ls="--"); ax.set_xlim(0,.55)
ax.set_xlabel("reachable sifting level $z=x^{e}$ (e=1/$\\beta_2$, source-reported $\\beta_2$)"); ax.text(.5,-.45,"needed: $x^{1/2}$",c="#b91c1c",ha="right",fontsize=8); save(fig,"fig4_sieve_barrier")
print("ok")
