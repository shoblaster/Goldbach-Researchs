# EXP020 — fixed-N Goldbach residue mapping

This experiment checks the exact finite correspondence between the
Goldbach-specific residue sieve for a fixed even N and prime pairs

    N = p + q,  p,q > sqrt(N).

It removes even offsets and offsets divisible, in either coordinate, by a prime
p with p^2 < N. The script then compares the survivors with direct primality
and interval tests. Its sieve prime list is independently checked by trial
division before the range comparison. The proof and scope limitation are in
`08_PROOFS/PROOF_FRONTIER_018_FIXED_GOLDBACH_RESIDUE_SCOPE.md`.

Command:

    python 03_CODE/goldbach_fixed_residue_mapping_check.py

This is a finite consistency check, not a Goldbach proof.
