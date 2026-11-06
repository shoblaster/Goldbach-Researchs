# Experiment index

Next free ID: **EXP026**. Raw data for EXP001–EXP005 lives in `04_RAW_DATA/`; EXP005 and EXP006 have no README in this folder (see `VALIDATION.md` and `05_PROCESSED_DATA/EXP006/`).

| ID | Subject | Status | Code (`03_CODE/`) |
|---|---|---|---|
| EXP001 | 4–1000 baseline counts | validated | 03_CODE/goldbach_baseline.cpp |
| EXP002 | 4–10000 attempt | INVALID (metadata) | — |
| EXP003 | 4–10000 baseline | validated (independent validator) | goldbach_baseline.cpp, validate_goldbach.cpp |
| EXP004 | 4–100000 attempt | INCOMPLETE | — |
| EXP005 | 4–100000 counts and pairs | validated (separate validators) | goldbach_baseline.cpp, validate_goldbach*.cpp |
| EXP006 | least Goldbach prime profile (max 293 at 63274) | derived from EXP005 | analyze_minimal_prime.cpp |
| EXP007 | Sieve II finite audit, k≤5 | exact | barca_sieve2_exhaustive.py |
| EXP008 | targeted k=6 extension | targeted only | barca_sieve2_k6_extension.py |
| EXP009 | exhaustive k=6 | exact | barca_sieve2_k6_exhaustive_bitmask.py |
| EXP010 | exact k=7 by final-prime optimization | exact | barca_sieve2_k7_extension_search.py |
| EXP011 | distribution statistics k≤6 | exact | barca_sieve2_distribution_stats.py |
| EXP012 | C++ cross-check of k=6 distribution | cross-check | barca_sieve2_k6_distribution_cpp.cpp |
| EXP013 | exact moments k≤7 | exact (Lemma 002) | barca_sieve2_moments.py |
| EXP014 | k=8 heuristic | heuristic | barca_sieve2_k8_heuristic.py |
| EXP015 | k=8 exact MILP | exact (single solver) | barca_sieve2_milp_exact.py |
| EXP016 | k=8 moments | exact (has CORRECTION.md) | barca_sieve2_k8_moments.py |
| EXP017 | paired-Jacobsthal ILP cross-check k=3…8 | cross-check of source table | paired_jacobsthal_ilp_crosscheck.py |
| EXP018 | fixed-window M_k vs h2 comparison | derived | fixed_window_vs_h2_comparison.py |
| EXP019 | exact k=9 MILP | exact (single solver) | barca_sieve2_milp_exact.py |
| EXP020 | fixed-N residue sieve ↔ prime pairs | exact finite check | goldbach_fixed_residue_mapping_check.py |
| EXP021 | primorial lower-window identity | exact finite check | primorial_window_identity_check.py |
| EXP022 | primorial-multiple offset audit | exact finite check | primorial_multiple_offset_audit.py |
| EXP023 | counts to 10^6 by FFT convolution, H-L ratio comparison | derived; matches EXP005 | goldbach_counts_1e6_hl_comparison.py |
| EXP024 | independent C++ pair-accumulation check of counts to 10^6 | validated (0 mismatches vs EXP023 and EXP005) | goldbach_pair_accumulate_1e6.cpp, compare_counts_exp024.py |
| EXP025 | position of smaller prime in Goldbach pairs vs 1/(ln p ln q) weight | derived heuristic check (flat ratio 3.998 vs 3.9995) | pair_position_distribution.cpp |
