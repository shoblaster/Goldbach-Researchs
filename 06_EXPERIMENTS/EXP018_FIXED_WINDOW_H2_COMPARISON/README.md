# EXP018 — fixed-window minima versus paired-Jacobsthal h2

This derived experiment checks the elementary inequality

    M_k >= floor(p_k^2 / h2(k)),

where M_k is the exact EXP015 minimum survivor count in [1,p_k^2] and h2(k)
is the Ziller--Morack paired-Jacobsthal value reproduced by EXP017.

The script does not rerun an optimizer. It reads the preserved raw outputs of
EXP015 and EXP017, computes the deterministic floor bound, and asserts that the
bound is satisfied. The mathematical justification and limitations are in
`08_PROOFS/PROOF_FRONTIER_017_OBJECTIVE_COMPARISON.md`.

Command:

    python 03_CODE/fixed_window_vs_h2_comparison.py

This is not a Goldbach proof and does not establish novelty.
