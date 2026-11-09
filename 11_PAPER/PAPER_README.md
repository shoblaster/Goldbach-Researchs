# Paper draft (v0.1) — reproducible note

`paper.tex` / `paper.pdf`: "Exact certification of a paired Jacobsthal bound and the dimension-2 sieve barrier".
**No proof of Goldbach's conjecture is claimed. Novelty NOT established.**

Reproduce (python3 + matplotlib; g++ for the recompute step):
```
python3 11_PAPER/make_figures.py        # regenerates figures/*.pdf|png from data/*.csv
python3 11_PAPER/verify_data.py         # table consistency + recompute k<=8 node counts (~1 min)
python3 11_PAPER/verify_data.py --fast  # table consistency only
cd 11_PAPER && latexmk -pdf paper.tex
```
Data provenance: `data/h2_table.csv` (source Table 1, k<=10 re-certified by EXP030), `data/infeasibility_nodes.csv`
(EXP030 RAW_OUTPUT), `data/mk_minima.csv` (EXP024/019), `data/sieve_limits.csv` (source-reported beta_2, CIT-043; not re-derived).
Author name in the .tex is a placeholder.
