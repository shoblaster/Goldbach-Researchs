# Goldbach Research

Auditable computational and proof research on the Goldbach conjecture.

## Current status

Strong Goldbach is **not proved here**. The repository distinguishes:

- validated finite computations;
- source-reported literature claims;
- proved elementary lemmas;
- conditional implications;
- explicit **PROOF GAP — NOT PROVED** steps;
- reproducibility and tooling failures.

The external Lean formalization examined in October 2026 is a `(1+1.9)` almost-prime statement, not binary Goldbach: its public interface allows `N = p + r*q` with `r = 1` or prime. Its complete Lean verification was not independently reproduced in this Windows environment.

## Start here

- `00_MASTER_RESEARCH_LOG.md` — chronological research record and verification checkpoints.
- `09_LITERATURE/CITATION_VERIFICATION.md` — source-by-source citation audit.
- `09_LITERATURE/CLAIM_LEDGER.md` — factual, computational, and proof-status ledger.
- `08_PROOFS/` — proof attempts, proved elementary cases, and documented gaps.
- `12_ARCHIVE/CONTINUATION_HANDOFF_2026-10-04.md` — precise continuation state.
- `12_ARCHIVE/EXTERNAL_SOURCE/LEAN_REPRO_RUN_LOG_2026-10-04.txt` — preserved Lean/cache run summary.

## Reproducibility policy

No result is presented as proved unless the source, computation, or proof step is actually checked. Unverified claims are labeled **UNVERIFIED**; failed proof steps are labeled **PROOF GAP — NOT PROVED**; unrun computations are never reported as run. The external checkout is intentionally ignored by Git and can be reconstructed from the frozen commit and URLs recorded in the audit files.

## Publication boundary

This repository is a research checkpoint, not a claim of a new proof or a resolved conjecture. Any future publication must preserve the citation verification, claim ledger, raw data, and uncertainty labels.
