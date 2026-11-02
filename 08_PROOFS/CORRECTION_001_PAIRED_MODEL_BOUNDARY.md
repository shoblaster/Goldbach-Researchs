# Correction 001 — paired-model relation

The earlier version of `PROOF_FRONTIER_016_PAIRED_MODEL_BOUNDARY.md` stated
that the paired-Jacobsthal model constrained the two residue classes by one
global difference and therefore was not equivalent to the arbitrary-residue
model. That statement was too strong and is withdrawn.

The inspected Ziller–Morack ancillary file explicitly says that paired
progressions can be characterized by choosing two residue classes for each
odd prime, and proves the correspondence using the Chinese remainder theorem
(arXiv ancillary `full_details.pdf`, Proposition 1.5, pp. 6–7 / extracted
lines 327–353). For finite survivor minimization, coincident classes can be
refined by adding a second class, so the minimum over the distinct-class model
agrees with the corresponding minimum over paired residue assignments.

The remaining distinction is functional: their h_2 is a worst-translation
maximum-gap quantity, while EXP015 counts survivors in the single fixed window
`[1,p_k^2]`. The repository therefore keeps EXP015 as a finite computation,
but no longer describes the paired residue model as merely a constrained
subset. The old claim is preserved here as a correction record rather than
silently deleted.
