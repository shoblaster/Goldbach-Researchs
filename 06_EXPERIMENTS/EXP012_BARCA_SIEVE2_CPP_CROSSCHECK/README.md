# EXP012 — independent C++ cross-check of the (k=6) distribution

**Run date:** 2026-11-02  
**Source code:** `03_CODE/barca_sieve2_k6_distribution_cpp.cpp`  
**Raw output:** `RAW_OUTPUT.txt`

EXP012 reimplements the complete (k=6) bit-mask enumeration in C++17,
independently of the Python code. It checks all 5,405,400 residue selections
and records the minimum, maximum, total count, and complete histogram. The
output is compared with EXP011's Python histogram.
