# Continuation handoff — 2026-10-04

## Non-negotiable research rules

The full `GOLDBACH_RESEARCH_CODEX_HANDOFF.md` was read before this work. Sections 20–22 are mandatory: verify external claims against the actual source; update `09_LITERATURE/CITATION_VERIFICATION.md`, `09_LITERATURE/CLAIM_LEDGER.md`, and the Verification Checkpoint in `00_MASTER_RESEARCH_LOG.md`; preserve raw data; mark UNVERIFIED and PROOF GAP — NOT PROVED; never invent citations, results, or novelty.

## Current mathematical status

- Strong Goldbach remains **OPEN; PROOF GAP — NOT PROVED**.
- No novelty claim is established.
- Validated finite computation remains EXP005 (`4..100000`, 49,999 even inputs, 25,366,983 pair rows, zero validator mismatches) and EXP006 (`max least summand 293`, witness `63274=293+62981`). These are finite observations only.
- Existing proof attempts and their gaps are recorded under `08_PROOFS/`.

## External formalization audit

Frozen checkout:

`12_ARCHIVE/EXTERNAL_SOURCE/goldbach-lean-main`

Commit:

`09b97db5764ade1246bfb77206baa1b124760958`

Key source hashes:

- `scripts/check.py`: `BF381C6676357D490C00E972C0D6FD125ED83E247B35FD1E1F78DECF09B65015`
- `Goldbach/OnePlusOneNine.lean`: `FCD30B5C85984BDE811293EF38B17A79AD74AD3F6F982609D89FD6B015854560`
- `docs/VERIFICATION.md`: `3A9E1ADA6DF848A26AFFA96D0125075D6934331824E61D6CB3BA940BC0795414`

Published source records are CIT-011 through CIT-015; the Li–Liu paper is CIT-009; the report/fibre discrepancy is CIT-010.

## Crucial reproducibility findings

1. Unmodified `python -u scripts/check.py --static-only` exits `1` on Windows. It reports 2,514 source files but only 3 reachable/default-library modules and 4,478 issues because line 181 replaces `/` but not Windows `\\` in module names. An in-memory separator-only fix reports `source_modules=2514`, `reachable_modules=1745`, `default_library_glob_modules=2514`, `default_build_modules=2514`, `issues=[]`. This is a checker portability issue, not a mathematical counterexample. See `PROOF_FRONTIER_004_WINDOWS_VERIFIER_FAILURE.md`.

2. The repository declares `leanprover/lean4:v4.33.0-rc1` (CIT-015). Elan/Lean/Lake were installed. `lake exe cache get` announced 8,679 files, reached about 99%, decompressed 8,239, reported 393 failed decompressions and 10 failed downloads, then stalled with connection-reset/path/decompression errors and was stopped (exit 1). Partial cache remains; nothing was deleted.

3. `lake build Goldbach.OnePlusOneNine` exited `1` with `error: build failed`; dependency jobs reported transient/missing `.olean.private` reads. An incremental rerun also exited `1`. Direct `lake env lean Mathlib/Data/Int/Log.lean` later exited `0`, so at least one first-run read error was transient/build-order related. Direct `lake env lean Goldbach/OnePlusOneNine.lean` exited `1` because `MathlibNt.SieveTheory.LiLiuGoldbachG11AuthorQuantitative.olean` was not built. A third parallel attempt was interrupted after further private-artifact errors and native `std::bad_alloc` (`3221226505`). No full build succeeded.

4. A source-only audit of `Goldbach/OnePlusOneNine.lean`, `Goldbach/OnePlusOneNineChecks.lean`, `Goldbach/Theorem.lean`, and `scripts/check.py` found the public wrappers and `#print axioms` probes. The separator-corrected lexical scan found no prohibited-token/static issue. Kernel axiom output was **NOT OBTAINED**; do not claim the allowed-axiom gate passed. See `PROOF_FRONTIER_006_SOURCE_AXIOM_SURFACE_AUDIT.md`.

## Files updated in this continuation

- `08_PROOFS/PROOF_FRONTIER_004_WINDOWS_VERIFIER_FAILURE.md`
- `08_PROOFS/PROOF_FRONTIER_005_LEAN_CACHE_REPRODUCTION.md`
- `08_PROOFS/PROOF_FRONTIER_006_SOURCE_AXIOM_SURFACE_AUDIT.md`
- `12_ARCHIVE/EXTERNAL_SOURCE/LEAN_REPRO_RUN_LOG_2026-10-04.txt`
- `09_LITERATURE/CITATION_VERIFICATION.md`
- `09_LITERATURE/CLAIM_LEDGER.md`
- `00_MASTER_RESEARCH_LOG.md`
- this handoff file

## Safe next steps

Use a reliable complete cache or intended Unix/CI environment, then run and preserve:

```text
lake --wfail build
python3 scripts/check.py --static-only
lake env lean Goldbach/OnePlusOneNineChecks.lean
lake env leanchecker --verbose Goldbach.OnePlusOneNine
```

Also run the repository's isolated reconstruction gate from `docs/VERIFICATION.md`. Only after those outputs are captured may the external formalization be upgraded beyond **SOURCE INSPECTED; FULL REPRODUCTION NOT ACHIEVED**. None of these steps can by themselves prove binary Goldbach unless the exact theorem statement is checked to be binary (`r=1`), which the inspected facade is not.
