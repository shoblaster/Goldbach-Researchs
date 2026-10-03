# Continuation handoff — 2026-09-09

## Non-negotiable rules

Read `GOLDBACH_RESEARCH_CODEX_HANDOFF.md` in full before work. Follow its Sections 20–22: verify sources directly, update the citation table, claim ledger, and master-log Verification Checkpoint at every meaningful stage; preserve raw data; never infer novelty, a theorem, or unrun computation.

## Current state

- Validated baseline datasets: EXP001 (`4..1000`), EXP003 (`4..10000`), EXP005 (`4..100000`).
- EXP005 is the current trusted dataset: 49,999 even inputs; 25,366,983 pair rows; 0 count-validator mismatches; 0 malformed pairs; 0 pair/count mismatches.
- This is finite computational evidence only. It is **not** a proof of Strong Goldbach or a novelty result.
- No conjecture is active. **NOVELTY NOT ESTABLISHED.**

## Important files

- `00_MASTER_RESEARCH_LOG.md`: authoritative chronological log and checkpoints.
- `03_CODE/goldbach_baseline.cpp`: generator. `versions/EXP005_v3.cpp` is the EXP005 snapshot.
- `03_CODE/validate_goldbach.cpp`: separate count validator.
- `03_CODE/validate_goldbach_pairs.cpp`: streaming pair validator.
- `04_RAW_DATA/EXP005/DATA_MANIFEST.md`: frozen raw-file hashes.
- `06_EXPERIMENTS/EXP005/VALIDATION.md`: exact independent-validation results; raw pair-validator stdout is `PAIR_VALIDATION_OUTPUT.txt`.
- `09_LITERATURE/CITATION_VERIFICATION.md` and `CLAIM_LEDGER.md`: mandatory ledgers.

## Do not use as evidence

- `04_RAW_DATA/EXP002`: metadata says EXP001 although output directory was EXP002; see `INVALID_METADATA_DO_NOT_USE.md`.
- `04_RAW_DATA/EXP004`: incomplete partial pair file after timeout; see `INCOMPLETE_DO_NOT_USE.md`.

## Build/run commands (from `03_CODE`)

```powershell
g++ -std=c++17 -O2 -Wall -Wextra goldbach_baseline.cpp -o goldbach_baseline.exe
g++ -std=c++17 -O2 -Wall -Wextra validate_goldbach.cpp -o validate_goldbach.exe
g++ -std=c++17 -O2 -Wall -Wextra validate_goldbach_pairs.cpp -o validate_goldbach_pairs.exe
```

For a new run, never reuse an output directory. Use a fresh experiment ID, e.g.:

```powershell
.\goldbach_baseline.exe 4 100000 ..\04_RAW_DATA\EXPXXX EXPXXX 0
.\validate_goldbach.exe ..\04_RAW_DATA\EXPXXX\goldbach_counts.csv
.\validate_goldbach_pairs.exe ..\04_RAW_DATA\EXPXXX\goldbach_pairs.csv ..\04_RAW_DATA\EXPXXX\goldbach_counts.csv
```

Argument `0` skips only the generator's expensive per-value trial-division check; it requires both separate validators and a recorded result before any interpretation.

## Literature stage reached

Sources actually inspected and recorded:

- Goldston & Yang, *The Average Number of Goldbach Representations*, arXiv:1601.06902 (2016): averages of Goldbach representations under RH.
- Ikeda & Suriajaya, *The average number of Goldbach representations over multiples of q*, arXiv:2405.04315v4 (revised 2025): averages over multiples of q, with stated GRH context.
- Saeli & Spano, *La cometa di Goldbach e ... le altre*, arXiv:1203.1282 (2012): the representation-count plot and its layered arithmetic structure are already studied.
- Languasco, *A singular series average and Goldbach numbers in short intervals*, Acta Arithmetica (1998), repository record checked: provides the stated Goldbach singular-series formula and an average result.
- Goldston & Suriajaya, *A singular series average and the zeros of the Riemann zeta-function*, Acta Arithmetica 200 (2021), DOI 10.4064/aa200821-24-2: source page inspected.

Crucial negative result: simple count plots, modular layering, singular-series normalization, and unrestricted/multiple-of-q averages are already established research territory. Do not describe an observation in these directions as new. This is not an exhaustive novelty search.

Additional screen completed after this handoff was created: the minimal Goldbach partition (least prime in a Goldbach pair) is also an established object; see CIT-006 (verified) and CIT-007 (partially verified) in the citation table. Do not use a basic minimum-summand computation as a novelty direction.

Current open lead: a specifically defined within-Goldbach-pair difference statistic. Its novelty is **UNVERIFIED**. CIT-008 has now been directly checked and covers related partition-count statistics, not necessarily the exact statistic; search the exact definition before any experiment or claim.

## Proof work completed after the initial handoff

- `08_PROOFS/PROOF_ATTEMPT_001_SIEVE_REDUCTION.md` formalizes a natural finite-sieve route and identifies its exact fatal step. It is labeled **PROOF GAP — NOT PROVED**.
- `08_PROOFS/LEMMA_001_LOCAL_SIEVE_COUNT.md` proves an elementary CRT formula for the local sieve residue count modulo an odd square-free modulus, with finite sanity checks.
- This lemma does **not** prove Strong Goldbach. The missing result is a global lower bound guaranteeing an actual simultaneous prime pair, not merely a locally admissible residue class.
- `08_PROOFS/PROVED_CASE_001_TWICE_A_PRIME.md` records the elementary restricted case `2p=p+p` for prime `p`; it is known and not novel.
- `08_PROOFS/PROOF_ATTEMPT_003_CONDITIONAL_ASYMPTOTIC.md` proves only the conditional implication from an eventually positive asymptotic representation formula; the asymptotic hypothesis remains a proof gap.
- EXP006 profiles the least prime summand in EXP005: maximum observed `293` at `63274=293+62981`; this is bounded computational evidence only.
- Proof Attempt 004 records the resulting finite counterexample to the shortcut `p<=281` for every even `E<=100000`; do not extrapolate it to a universal cutoff.
- Proof Attempt 005 gives a symbolic limitation: for any fixed sieve bound, a pair of large prime squares can survive all local tests while remaining composite. This is a proof-design barrier, not a Goldbach counterexample.
- A directly inspected 2026 arXiv preprint claims an unconditional `(1+1.9)` almost-prime theorem; see CIT-009 and `08_PROOFS/PROOF_FRONTIER_001_ONE_PLUS_1_9.md`. It is not binary Goldbach and its proof has not been independently checked here.
- A public third-party Lean-formalization report for that result was inspected on 2026-10-03; see CIT-010 and `08_PROOFS/PROOF_FRONTIER_002_FORMALIZATION_AUDIT.md`. The report is important provenance evidence, but it explicitly records a corrected-fibre discrepancy and says the complete paper argument was not audited line-by-line. At that earlier stage no Lean build or source replay had been performed. Treat the result as **PARTIALLY VERIFIED / SOURCE-REPORTED**, not as a proof certificate.
- A direct source audit then inspected the public Lean facade, theorem documentation, verification guide, README, and pinned toolchain; see CIT-011 through CIT-015 and `08_PROOFS/PROOF_FRONTIER_003_SOURCE_REPRODUCIBILITY_AUDIT.md`. That historical snapshot recorded no local checkout/build/replay; the later frozen-checkout and partial-build work is documented below. Current status remains **SOURCE INSPECTED; FULL REPRODUCTION NOT ACHIEVED**.
- A frozen checkout at commit `09b97db5764ade1246bfb77206baa1b124760958` was then tested. The published static checker fails unchanged on Windows because line 181 normalizes `/` but not `\\`; an in-memory separator-only diagnostic passes with `issues: []`. See `08_PROOFS/PROOF_FRONTIER_004_WINDOWS_VERIFIER_FAILURE.md`. This is a tooling portability failure, not a mathematical counterexample. Full Lean verification remains pending.
- On 2026-10-04, the pinned Lean toolchain `leanprover/lean4:v4.33.0-rc1` was installed and the cache command was run. Cache retrieval stalled after `8239/8679` decompressions with `393` failed decompressions and `10` failed downloads. Two focused `lake build Goldbach.OnePlusOneNine` attempts exited with `error: build failed` amid `.olean.private` read failures; a direct facade run failed because the required `MathlibNt.SieveTheory.LiLiuGoldbachG11AuthorQuantitative.olean` was unbuilt. One isolated Mathlib module later elaborated successfully, showing at least one first-run read error was transient/build-order related. A third parallel attempt was interrupted after `std::bad_alloc` (`3221226505`). See `08_PROOFS/PROOF_FRONTIER_005_LEAN_CACHE_REPRODUCTION.md`. Status remains **SOURCE INSPECTED; FULL REPRODUCTION NOT ACHIEVED**; no theorem conclusion follows.
- The separator-normalized in-memory static scan then reported `issues=[]` over all 2,514 source modules, including no prohibited lexical tokens under the repository scanner. This is only a source-surface audit. The `#print axioms` probes exist in `Goldbach/OnePlusOneNineChecks.lean`, but their kernel outputs were not obtained. See `08_PROOFS/PROOF_FRONTIER_006_SOURCE_AXIOM_SURFACE_AUDIT.md`; do not upgrade the external result beyond **SOURCE-SCAN PASSED IN MEMORY; KERNEL AXIOM REPORT UNVERIFIED**.

## Next safe action

First expand the literature log with exact-query searches for any narrowly proposed statistic. A potentially useful but untested direction is a precisely defined computational/algorithmic benchmark or a rigorously specified restricted statistic; its novelty is **UNVERIFIED**. Do not claim it is new until equivalent formulations and existing papers are checked.
