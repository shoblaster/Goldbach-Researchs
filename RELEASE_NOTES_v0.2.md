# Release v0.2.0 — working note (not a proof)

**What this is:** a reproducible computational note (`11_PAPER/paper.pdf`) on a published reduction of a tightened Goldbach
statement to the paired Jacobsthal bound h2(k) < p_k^2 - p_k. **What it is not:** a proof of Goldbach's conjecture or of that bound.

**Contents:** elementary re-derivation of the reduction; exhaustive certification of h2(k), k = 3..11 (k = 11: one implementation, no
independent re-run); minima M_k; a sieve-barrier discussion built on source-reported constants; data, scripts and figures.
**Not verified:** rows k >= 12 (transcribed); novelty; sieve constants against primary books.
**AI assistance:** code, drafting and checks were done with Claude; the author directed the project.

Reproduce: `python3 11_PAPER/make_figures.py && python3 11_PAPER/verify_data.py`.
