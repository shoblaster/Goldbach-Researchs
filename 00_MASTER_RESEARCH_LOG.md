# Master research log

## Project status

- Current research question: Can EXP001 reliably compute the stated representation-count convention on a small range?
- Current hypothesis/conjecture: None.
- Current status: EXP005 has a separately validated, frozen baseline dataset for 4 through 100000. EXP002 and EXP004 are preserved invalid/incomplete attempts.
- Most important result so far: A complete count-and-pair dataset independently validated at 100000; it is not a theorem or novelty result.
- Next action: Define one narrow candidate statistic or algorithmic question, then conduct exact-formulation literature searches before computing it.

## Timeline

### 2026-09-09 — repository initialization and EXP001 setup

- Objective: Establish an auditable directory structure and a correctness-first baseline implementation.
- Work performed: Created the project structure, documented a fixed counting convention, implemented a sieve-based counter that saves all representations, added fixed-case checks, and added an independent trial-division validation path.
- Results: Code prepared only; no experiment output or numerical result is claimed in this entry.
- Interpretation: The implementation must execute successfully before any computational statement can be made.
- Literature status: No external source was used in this stage.
- Next step: Compile and run the small-range baseline; retain all generated raw data.

### Verification Checkpoint

**Claims made:**
- EXP001 has a specified counting convention and an implementation prepared for validation.
- No mathematical result, novelty claim, or proof is asserted.

**Sources used:**
- None.

**Citations verified:**
- None.

**Claims not independently verified:**
- The program has not yet been compiled or executed.

**Computations actually run:**
- None.

**Data generated:**
- No experimental data. Project documentation and source files only.

**Proof status:**
- No proof attempted.

**Novelty status:**
- NOVELTY NOT ESTABLISHED; no novelty proposition has been made.

**Known uncertainties:**
- Compiler behavior and output validation are pending execution.

**Next verification required:**
- Compile, execute, independently validate the actual saved output, and add a new checkpoint.

### 2026-09-09 — EXP001 execution and output validation

- Objective: Run the small baseline range and verify the generated files.
- Work performed: Initial compilation failed because the available MinGW compiler lacks `<filesystem>`; no data was generated. The program was revised to use the Windows-compatible `_mkdir` routine. It was compiled with `g++ -std=c++17 -O2 -Wall -Wextra`, then run on 4 through 1000. A source snapshot was copied to `03_CODE/versions/EXP001_v1.cpp` after the successful run.
- Results: 499 even integers were processed. The program reported minimum `G(n)=1`, maximum `G(n)=52`, and 0 values with `G(n)=0`. It saved 8,222 pair rows. A post-run check confirmed 0 invalid pair rows and 0 mismatches between pair-file group totals and count-file values.
- Interpretation: The exact program version and exact frozen output passed the specified checks for this finite range. This supports only the correctness of this bounded computation under its stated convention.
- Literature status: No external source was used or cited.
- Next step: Preserve this baseline intact; any scaling should use a new experiment dataset/version rather than overwrite EXP001.

### Verification Checkpoint

**Claims made:**
- EXP001 computed and saved a bounded dataset for the stated convention and range.
- Its stored counts and pairs passed the documented independent checks.
- No unbounded mathematical proposition, proof, or novelty claim follows.

**Sources used:**
- None.

**Citations verified:**
- None.

**Claims not independently verified:**
- Performance and correctness beyond the 4–1000 range have not been established.
- No literature-related claim has been investigated.

**Computations actually run:**
- One successful EXP001 run: 4–1000, using the frozen source snapshot and compiler command recorded in the raw-data manifest.
- One program-internal trial-division validation for every tested value.
- One post-run CSV integrity check.

**Data generated:**
- `04_RAW_DATA/EXP001/goldbach_counts.csv`, `goldbach_pairs.csv`, and `metadata.txt`; checksums are in `DATA_MANIFEST.md`.
- Derived summary only in `05_PROCESSED_DATA/EXP001/SUMMARY.md`.

**Proof status:**
- No proof attempted. Finite computational verification is not a proof of Strong Goldbach.

**Novelty status:**
- NOVELTY NOT ESTABLISHED. EXP001 was not designed to establish it.

**Known uncertainties:**
- The implementation has not yet been stress-tested at a larger range or with a separately written executable.
- The code snapshot is not associated with a git commit; its SHA-256 is recorded instead.

**Next verification required:**
- Before scaling, independently review the code and choose a distinct output directory/experiment ID. Before any research claim, perform documented literature verification.

### 2026-09-09 — EXP002 rejected output and EXP003 corrected scale-up

- Objective: Scale the baseline to 4 through 10000 without altering EXP001.
- Work performed: A first output was written to `04_RAW_DATA/EXP002`, but immediately found to be audit-invalid because the program hard-coded EXP001 in metadata and console text. The files were preserved unchanged and marked `INVALID_METADATA_DO_NOT_USE`. The program was corrected to take an explicit experiment ID, recompiled, frozen as `EXP003_v2.cpp`, and run into the new `EXP003` directory.
- Results: EXP003 processed 4,999 even values. It reported minimum `G(n)=1`, maximum `G(n)=329`, and 0 zero counts. The pair file has 425,751 rows. The program's trial-division cross-check completed without failure; external post-run checks found 0 malformed pairs and 0 grouped-count mismatches.
- Interpretation: EXP003 is the valid 4–10000 baseline dataset. The rejected EXP002 files cannot support any reported computational claim. The valid result remains a finite computation only.
- Literature status: No external source was used or cited.
- Next step: Conduct an independent implementation/code review before further scale-up or analyzing patterns.

### Verification Checkpoint

**Claims made:**
- EXP002 is unsuitable as a validated dataset due to self-inconsistent experiment identity metadata.
- EXP003 completed the stated bounded computation and passed the stated checks.
- No theorem, novelty claim, or assertion beyond the stated range is made.

**Sources used:**
- None.

**Citations verified:**
- None.

**Claims not independently verified:**
- The program is not independently implemented in a second executable.
- No result above 10000 has been tested in EXP003.

**Computations actually run:**
- One EXP002 attempt on 4–10000; preserved but excluded from validated use due to metadata defect.
- One successful EXP003 run on 4–10000, with program-internal trial-division checking and a post-run CSV integrity check.

**Data generated:**
- Preserved rejected attempt: `04_RAW_DATA/EXP002`.
- Valid frozen dataset: `04_RAW_DATA/EXP003`; SHA-256 manifest provided.
- Derived report: `05_PROCESSED_DATA/EXP003/SUMMARY.md`.

**Proof status:**
- No proof attempted. Finite computation does not prove Strong Goldbach.

**Novelty status:**
- NOVELTY NOT ESTABLISHED. No novelty investigation has started.

**Known uncertainties:**
- The validity checks share some implementation context with the main program; a wholly separate executable remains to be written/reviewed.
- Trial division at much larger ranges may make this configuration impractical.

**Next verification required:**
- Create or review a genuinely separate validation path before increasing the range. Document any literature claims before making them.

### 2026-09-09 — independent validation of EXP003 counts

- Objective: Remove dependence on the baseline program's internal trial-division check before further scaling or interpretation.
- Work performed: Wrote a separate validator that reads only the saved count CSV, uses a different byte-based sieve representation, and iterates through every candidate addend rather than using the baseline program's prime list or functions. Its first compile was blocked by unsupported structured bindings in the available compiler; that non-experiment compatibility issue was corrected. The validator then compiled and ran successfully.
- Results: Actual validator output: `Validated rows=4999, mismatches=0`.
- Interpretation: Two independently written implementations agree on every saved EXP003 count. This is strong finite-dataset validation, not a proof beyond the dataset.
- Literature status: No external source was used or cited.
- Next step: The count engine is ready for a carefully logged larger baseline run, with a fresh code/data version.

### Verification Checkpoint

**Claims made:**
- The independently written validator recomputed all EXP003 count rows with zero mismatches.
- No claim beyond EXP003's finite range is made.

**Sources used:**
- None.

**Citations verified:**
- None.

**Claims not independently verified:**
- The validator's sieve implementation has not been reviewed by an external party; its result is an independent programmatic check, not formal verification.

**Computations actually run:**
- One successful independent count-file validation of EXP003: 4,999 rows, 0 mismatches.

**Data generated:**
- Validation record only: `06_EXPERIMENTS/EXP003/INDEPENDENT_VALIDATION.md`. The EXP003 raw data was not modified.

**Proof status:**
- No proof attempted.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- No separate implementation yet validates the complete pair CSV from primality alone.

**Next verification required:**
- Use a new experiment ID/data directory for any scale-up; validate its counts with the independent validator before analysis.

### 2026-09-09 — EXP004 incomplete attempt and EXP005 validated scale-up

- Objective: Scale the baseline to 100000 while preserving all prior output.
- Work performed: EXP004 began with per-value trial-division validation enabled but exceeded the execution window and left only a partial pair file. Its process was stopped; the partial output is preserved and marked unusable. The baseline was revised to permit the expensive in-process full-range validation to be disabled only when external validation is required. EXP005 ran in a fresh directory with that option disabled, then the count file and complete pair file were separately validated.
- Results: EXP005 processed 49,999 values, with minimum `G(n)=1`, maximum `G(n)=2168`, and 0 zero counts. It generated 25,366,983 pair rows. Independent validation reported 49,999 count rows with 0 mismatches and 25,366,983 pair rows with 0 malformed rows and 0 per-count mismatches.
- Interpretation: EXP005 is a validated finite baseline at 100000. The incomplete EXP004 file is not evidence. No inference beyond the explicit finite range is permitted.
- Literature status: No external source was used or cited.
- Next step: Search and inspect authoritative literature before framing any research claim around representation counts.

### Verification Checkpoint

**Claims made:**
- EXP004 is incomplete and unusable.
- EXP005's frozen count and pair files passed separately written validators.
- No theorem, novelty claim, or unbounded inference is made.

**Sources used:**
- None.

**Citations verified:**
- None.

**Claims not independently verified:**
- No formal proof of program correctness exists; validation is computational.
- The mechanism behind observed count variation has not been investigated.

**Computations actually run:**
- Incomplete EXP004 run (preserved, excluded).
- Successful EXP005 generation for 4–100000.
- Independent count validation: 49,999 rows, 0 mismatches.
- Independent pair validation: 25,366,983 rows, 0 malformed and 0 count mismatches.

**Data generated:**
- Incomplete output: `04_RAW_DATA/EXP004`.
- Valid frozen output: `04_RAW_DATA/EXP005`, with checksums in its manifest.
- Validation captures and documentation: `06_EXPERIMENTS/EXP005`.

**Proof status:**
- No proof attempted.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- No literature survey has yet established which representation-count questions are already known.
- The 100000 data may reveal familiar arithmetic structure; it must not be treated as new without source verification.

**Next verification required:**
- Inspect primary or authoritative literature on Goldbach representation counts before formulating a potentially new question.

### 2026-09-09 — initial literature triage

- Objective: Determine whether obvious representation-count, modular, and singular-series directions can be treated as unexplored.
- Work performed: Searched and inspected five sources recorded as CIT-001 through CIT-005 in `09_LITERATURE/CITATION_VERIFICATION.md`.
- Results: The inspected literature covers average representation counts, averages over multiples of q, the Goldbach-comet count plot and its layers, and singular-series averages. EXP005's raw count plot or elementary modular stratification therefore cannot be treated as a novel observation merely because it appears in this repository.
- Interpretation: This is a crucial scope constraint, not a mathematical result: the obvious directions have prior art. The search was not exhaustive, so no broad novelty conclusion is made.
- Literature status: Five sources directly inspected; all citations listed as VERIFIED for their narrow recorded claims.
- Next step: Formulate one exact, limited candidate question and search its exact and equivalent formulations before running a targeted experiment.

### Verification Checkpoint

**Claims made:**
- Prior work exists on the narrow topics listed in CLM-LIT-001 through CLM-LIT-003.
- Novelty of any future restricted statistic or algorithm is not established.

**Sources used:**
- CIT-001 through CIT-005, with direct URLs and checks in the citation-verification table.

**Citations verified:**
- CIT-001 through CIT-005, for the claims stated in that table.

**Claims not independently verified:**
- The literature search is not exhaustive.
- No claim is made about whether a particular new statistic or algorithm is novel.

**Computations actually run:**
- None in this literature stage.

**Data generated:**
- Citation and claim-ledger additions; `12_ARCHIVE/CONTINUATION_HANDOFF_2026-09-09.md`.

**Proof status:**
- No proof attempted.

**Novelty status:**
- NOVELTY NOT ESTABLISHED. Obvious count-plot/modular/singular-series directions have known prior work.

**Known uncertainties:**
- A candidate research question has not yet been selected or searched exhaustively.

**Next verification required:**
- Search the exact statement and equivalent formulations of any candidate question before calling it possibly new.

### 2026-09-09 — candidate screen: least Goldbach summand

- Objective: Test whether the least prime in an unordered Goldbach representation could support a fresh computational research direction.
- Work performed: Searched exact phrases including “least Goldbach partition,” “minimal Goldbach representation,” and “smallest prime Goldbach representation.” Inspected the arXiv preprint CIT-006 directly. Located the 2013 Mathematics of Computation paper CIT-007, but its AMS PDF returned 403, so its record remains only partially verified.
- Results: CIT-006 explicitly defines the minimal Goldbach prime as the least possible small prime in a Goldbach pair and studies a search protocol for it. The CIT-007 search result identifies an earlier algorithm for the minimal Goldbach partition.
- Interpretation: Computing minimum Goldbach summands is not a safe novelty direction. A materially more specific question would require its own exact literature search.
- Literature status: CIT-006 VERIFIED; CIT-007 PARTIALLY VERIFIED.
- Next step: Do not run an experiment on this statistic as a novelty project. Screen a different, precisely stated candidate before computing it.

### Verification Checkpoint

**Claims made:**
- The minimal Goldbach partition is a previously studied object.
- No novelty claim is made for any refinement.

**Sources used:**
- CIT-006 and CIT-007.

**Citations verified:**
- CIT-006.

**Claims not independently verified:**
- CIT-007's full contents are not independently inspected due to access failure.
- No exhaustive review of every variant of minimal-partition statistics was conducted.

**Computations actually run:**
- None in this literature stage.

**Data generated:**
- Citation/claim-ledger additions and this master-log checkpoint.

**Proof status:**
- No proof attempted.

**Novelty status:**
- NOVELTY NOT ESTABLISHED. Simple minimum-summand computation is likely known.

**Known uncertainties:**
- A sufficiently narrow and potentially useful research question has not yet been selected.

**Next verification required:**
- Define a candidate before coding; search its exact statement, aliases, and equivalent formulations.

### 2026-09-09 — candidate screen: Goldbach-pair differences

- Objective: Assess whether a statistic based on the differences `|p-q|` in Goldbach pairs is sufficiently unexplored to justify computation.
- Work performed: Searched phrases including “Goldbach partition differences distribution,” “Goldbach separation data,” and “Goldbach representation difference.”
- Results: A direct arXiv record for CIT-008 was subsequently inspected. It studies statistics of the Goldbach partition-count series and discusses a sum/difference symmetry, but it does not settle the exact question of a chosen within-pair difference statistic.
- Interpretation: The exact candidate remains UNVERIFIED; no experiment, conjecture, or novelty statement is justified.
- Literature status: CIT-008 is VERIFIED for its narrow recorded claim.
- Next step: Formally define one within-pair difference statistic, then search that exact definition before computing it.

### Verification Checkpoint

**Claims made:**
- No mathematical or novelty claim. The candidate's status is UNVERIFIED.

**Sources used:**
- Search results only; CIT-008 recorded as an unchecked lead.

**Citations verified:**
- None in this stage.

**Claims not independently verified:**
- All substantive claims about Goldbach-pair difference statistics.

**Computations actually run:**
- None in this stage.

**Data generated:**
- Literature-ledger and master-log entries only.

**Proof status:**
- No proof attempted.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- The field and terminology for difference-based statistics have not been adequately mapped.

**Next verification required:**
- Inspect primary literature before investing computation in this candidate.

### 2026-09-09 — proof attempt 001: finite sieve reduction

- Objective: Test a direct small-prime sieve route toward a proof of Strong Goldbach.
- Work performed: Formalized the candidate set after sieving possible addends and checked the logical transition from “free of small factors” to “prime.”
- Results: The route has an explicit fatal gap. A sieve below square-root scale cannot certify primality; a square-root-scale sieve makes the remaining-survivor claim equivalent to the original existence problem.
- Interpretation: This is a useful negative proof result: the stated elementary sieve outline is not a proof strategy unless a genuinely new, rigorous lower bound is supplied.
- Literature status: CIT-006 supports only the background statement that Strong Goldbach is unproven. No theorem was imported to conceal the gap.
- Next step: Do not patch this gap with heuristic prime-density reasoning. Any next proof attempt must name its exact new lemma and separately prove it.

### Verification Checkpoint

**Claims made:**
- The recorded finite-sieve route contains a precise proof gap and proves no Goldbach statement.

**Sources used:**
- CIT-006 only for the background open-status statement.

**Citations verified:**
- CIT-006.

**Claims not independently verified:**
- No claimed new lower bound or proof lemma exists.

**Computations actually run:**
- None in this proof stage.

**Data generated:**
- `08_PROOFS/PROOF_ATTEMPT_001_SIEVE_REDUCTION.md`.

**Proof status:**
- PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- Whether a different, rigorously justified route can yield a restricted theorem remains open in this project.

**Next verification required:**
- Before pursuing a new proof lemma, state it precisely and search for known equivalents.

### 2026-09-09 — Lemma 001: exact local sieve count

- Objective: Turn the valid local part of the failed sieve outline into a precise lemma.
- Work performed: Counted, using the Chinese remainder theorem, the residue classes modulo an odd square-free modulus for which neither `a` nor `E-a` has a factor from that modulus.
- Results: The exact product formula in `08_PROOFS/LEMMA_001_LOCAL_SIEVE_COUNT.md` was proved, including the coincident exclusion when a prime divides `E` and the `M=1` edge case.
- Interpretation: This rigorously explains the local arithmetic contribution to a sieve. It does not bridge the global primality/existence gap and is not claimed as novel.
- Literature status: No external result beyond the standard Chinese remainder theorem was required; novelty has not been investigated because the lemma is elementary.
- Next step: Any attempt to turn local density into a Goldbach proof must explicitly prove a non-local survivor bound; it may not silently assume one.

### Verification Checkpoint

**Claims made:**
- Lemma 001 is proved under its stated assumptions.
- It does not prove Strong Goldbach.

**Sources used:**
- None for the lemma's proof.

**Citations verified:**
- None newly required.

**Claims not independently verified:**
- Novelty of the elementary lemma is not checked and is not claimed.

**Computations actually run:**
- None.

**Data generated:**
- `08_PROOFS/LEMMA_001_LOCAL_SIEVE_COUNT.md` and ledger/log entries.

**Proof status:**
- Lemma 001: PROVED RESULT.
- Strong Goldbach: OPEN; PROOF GAP remains in proof attempt 001.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- No global survivor theorem is available in this project.

**Next verification required:**
- Literature-check any proposed strengthened local-to-global lemma before attempting to prove it.

### 2026-09-09 — Lemma 001 finite sanity checks

- Objective: Independently check selected instances and edge cases of Lemma 001 without mistaking computation for proof.
- Work performed: Directly enumerated residue classes for `(E,M)=(30,105)`, `(26,105)`, and `(10,1)`.
- Results: Formula and enumeration agreed: `40=40`, `15=15`, and `1=1`, respectively.
- Interpretation: These checks catch basic implementation/algebra slips in representative cases; the written CRT proof remains the reason Lemma 001 is proved.
- Literature status: No external source used.
- Next step: Do not infer a global prime-pair result from the local lemma.

### Verification Checkpoint

**Claims made:**
- Three finite checks agree with Lemma 001's formula.
- No stronger mathematical claim follows.

**Sources used:**
- None.

**Citations verified:**
- None.

**Claims not independently verified:**
- No global Goldbach consequence of the lemma.

**Computations actually run:**
- Exact finite residue enumeration for the three stated `(E,M)` pairs.

**Data generated:**
- The check table appended to `LEMMA_001_LOCAL_SIEVE_COUNT.md`.

**Proof status:**
- Lemma 001 remains PROVED RESULT; Strong Goldbach remains OPEN.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- The key local-to-global step remains absent.

**Next verification required:**
- Any proposed global lower bound must be stated precisely and literature-checked before proof work.

### 2026-09-11 — proof attempt 002: midpoint formulation

- Objective: Test whether ordinary information about primes near the midpoint of an even integer could force a Goldbach pair.
- Work performed: Rewrote candidate pairs symmetrically around `E/2` and audited the inference from “primes occur nearby” to “a reflected pair is prime.”
- Results: The approach requires the nonempty intersection `P ∩ (E-P)`, a two-set correlation statement. Separate facts about the presence of primes near the midpoint do not establish it.
- Interpretation: This rules out a common invalid proof move: replacing the simultaneous primality condition with two unrelated local prime-existence claims.
- Literature status: No external theorem was invoked.
- Next step: Any proposed global correlation estimate must be written precisely, literature-checked, and either proved or marked as an unresolved assumption.

### Verification Checkpoint

**Claims made:**
- Proof Attempt 002 has a specific proof gap and proves no Goldbach statement.

**Sources used:**
- None newly used.

**Citations verified:**
- None newly required.

**Claims not independently verified:**
- No global prime-pair correlation estimate is available in this project.

**Computations actually run:**
- None.

**Data generated:**
- `08_PROOFS/PROOF_ATTEMPT_002_MIDPOINT_APPROACH.md`.

**Proof status:**
- PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- A nontrivial restricted theorem suitable for an elementary proof has not been selected.

**Next verification required:**
- Before claiming a correlation lemma, define it and identify its relationship to known Goldbach representation results.

## Research ledger

| Experiment ID | Dataset version | Code version | Parameters | Result | Reproducibility status | Novelty status |
|---|---|---|---|---|---|---|
| EXP001 | `04_RAW_DATA/EXP001` (SHA-256 manifest) | `versions/EXP001_v1.cpp` SHA-256 `9B062266…E3D80` | 4–1000, unordered pairs | 499 values; 0 zero counts; max 52 | Program trial division + post-run CSV check passed | Not applicable |
| EXP002 | `04_RAW_DATA/EXP002` (preserved) | pre-ID-fix source | 4–10000, unordered pairs | Excluded: metadata says EXP001 | Not valid for use | Not applicable |
| EXP003 | `04_RAW_DATA/EXP003` (SHA-256 manifest) | `versions/EXP003_v2.cpp` SHA-256 `2A44FACF…B4E45` | 4–10000, unordered pairs | 4,999 values; 0 zero counts; max 329 | Program trial division + post-run CSV check passed | Not applicable |
| EXP004 | `04_RAW_DATA/EXP004` (partial) | pre-EXP005 source | Intended: 4–100000 | Incomplete; no count/metadata | Not valid for use | Not applicable |
| EXP005 | `04_RAW_DATA/EXP005` (SHA-256 manifest) | `versions/EXP005_v3.cpp` SHA-256 `4F70C888…A4038` | 4–100000, unordered pairs | 49,999 values; 0 zero counts; max 2,168 | Separate count and pair validators passed | Not applicable |

## Important discoveries

- Known facts: None recorded in this repository yet.
- Computational observations: EXP001 has no zero count among the 499 tested inputs. This is bounded computational evidence only.
- Computational observations: EXP003 has no zero count among the 4,999 tested inputs. This is bounded computational evidence only.
- Computational observations: EXP005 has no zero count among the 49,999 tested inputs. This is bounded computational evidence only.
- Conjectures: None.
- Proved results: The elementary restricted case `E=2p` for prime `p` is recorded in `08_PROOFS/PROVED_CASE_001_TWICE_A_PRIME.md`. It is known/trivial and does not approach the full conjecture.

### 2026-10-03 — proved restricted case: twice a prime

- Objective: Record a completely rigorous subfamily without overstating its scope.
- Work performed: Proved directly that `2p=p+p` for every prime `p`, under the project's convention allowing equal prime summands.
- Results: The Strong Goldbach statement holds for all even integers of the form `2p` with `p` prime.
- Interpretation: This is an elementary known restricted case. It does not address even integers with composite half and does not reduce the central correlation gap.
- Literature status: No external source used; no novelty claim.
- Next step: Continue only with a precisely stated nontrivial restricted theorem or a proof attempt whose missing implication is explicit.

### Verification Checkpoint

**Claims made:**
- `2p=p+p` proves the stated restricted case for prime `p`.
- The result is not claimed as new and does not prove Strong Goldbach.

**Sources used:**
- None.

**Citations verified:**
- None required.

**Claims not independently verified:**
- None beyond the explicit elementary proof.

**Computations actually run:**
- None.

**Data generated:**
- `08_PROOFS/PROVED_CASE_001_TWICE_A_PRIME.md`.

**Proof status:**
- Restricted case: PROVED RESULT.
- Full Strong Goldbach: OPEN; proof gaps remain.

**Novelty status:**
- NOVELTY NOT ESTABLISHED; case is elementary and known.

**Known uncertainties:**
- No extension to the composite-half cases has been proved.

**Next verification required:**
- Any proposed extension must be checked for the same hidden simultaneous-primality gap.

### 2026-10-03 — proof attempt 003: conditional asymptotic route

- Objective: Separate the easy positivity implication from the difficult analytic hypothesis.
- Work performed: Defined the unordered representation count `R(E)` and proved that if `R(E)=(1+o(1))H(E)` with an eventually positive `H(E)`, then `R(E)>0` for all sufficiently large even `E`.
- Results: The conditional implication is complete. The asymptotic hypothesis itself remains unproved here, and finite computation cannot replace it.
- Interpretation: This identifies the exact analytic dependency instead of silently treating a heuristic formula as a theorem. A finite check would still be needed below the asymptotic threshold even if the hypothesis were proved.
- Literature status: The project's earlier literature records Hardy–Littlewood-type representation asymptotics as conjectural/conditional context; no such theorem is asserted here.
- Next step: Do not claim progress toward the full conjecture unless an independently verified theorem supplies the missing unconditional asymptotic or an alternative global argument.

### Verification Checkpoint

**Claims made:**
- The stated positive-asymptotic hypothesis implies eventual Goldbach representations.
- The hypothesis has not been proved in this project.

**Sources used:**
- Existing project literature records for context; no new source claim is needed for the self-contained implication.

**Citations verified:**
- None newly added.

**Claims not independently verified:**
- The unconditional asymptotic hypothesis remains unverified and is explicitly not assumed as fact.

**Computations actually run:**
- None.

**Data generated:**
- `08_PROOFS/PROOF_ATTEMPT_003_CONDITIONAL_ASYMPTOTIC.md`.

**Proof status:**
- Conditional implication: PROVED under its stated hypothesis.
- Strong Goldbach: OPEN; unconditional proof gap remains.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- No unconditional theorem closing the asymptotic gap has been identified or verified here.

**Next verification required:**
- Any claimed analytic theorem must be checked directly against its source and hypotheses before use.

### 2026-10-03 — EXP006 least Goldbach prime profile

- Objective: Test the finite behavior of the smallest prime summand, as a diagnostic for overly strong small-prime proof ideas.
- Work performed: Streamed the frozen EXP005 pair file with `analyze_minimal_prime.cpp`; recorded the first (least-`p`) row for each `n` and computed the maximum of those minima.
- Results: 49,999 derived rows. Maximum least prime `p_min=293`, at `63274=293+62981`. Derived CSV hash: `6EED86DE1D75BEF224E9B74626CC358DC1E1248AAE3DCDDB49A5C453028D0FCF`.
- Interpretation: The bound `p_min<=293` holds on this exact finite range. This is an observation, not a universal bound, theorem, or novelty claim. Existing literature on minimal Goldbach partitions makes a basic profile analysis unsuitable as a novelty claim.
- Literature status: No new external claim used; prior minimal-partition literature remains recorded as CIT-006/CIT-007.
- Next step: Do not extrapolate this finite maximum. If pursuing a proof, use it only to test candidate lemmas and record counterexamples to any stronger proposed finite bound.

### Verification Checkpoint

**Claims made:**
- EXP006 has one derived row for each even `n` in 4–100000 and maximum observed least prime 293 at the stated witness.

**Sources used:**
- Frozen EXP005 pair dataset and its existing validation records.

**Citations verified:**
- No new citation.

**Claims not independently verified:**
- No statement about ranges beyond 100000.
- No claim that 293 is a global maximum.

**Computations actually run:**
- One streaming analyzer over all 25,366,983 validated EXP005 pair rows.
- Derived profile integrity: 49,999 rows.

**Data generated:**
- `05_PROCESSED_DATA/EXP006/minimal_prime_by_n.csv` and summary.

**Proof status:**
- No proof advanced; prior proof gaps remain.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- The statistic is already studied in prior literature; this finite profile has not undergone an exhaustive comparison to every published table.

**Next verification required:**
- Any proposed universal or asymptotic bound for the least prime must be literature-checked and proved separately.

### 2026-10-03 — proof attempt 004: fixed small-prime cutoff

- Objective: Test whether a proof shortcut using only a fixed list of small primes can cover the validated finite range.
- Work performed: Used the EXP006 first-row profile to test the cutoff `p<=281`.
- Results: The claim fails at `63274`, whose first validated representation has smaller prime `293`; no smaller-prime pair appears in the complete ordered pair file.
- Interpretation: This is a finite computational counterexample to that cutoff, not a theorem about all cutoffs or all integers. It rules out one overly strong proof shortcut.
- Literature status: No new external claim used.
- Next step: Do not replace the missing global argument with an arbitrary larger fixed cutoff.

### Verification Checkpoint

**Claims made:**
- The cutoff `p<=281` fails at `E=63274` in the validated EXP005 range.

**Sources used:**
- EXP005 raw data, EXP006 derived profile, and independent validation records.

**Citations verified:**
- None newly required.

**Claims not independently verified:**
- No statement about any cutoff above 281 or values above 100000.

**Computations actually run:**
- EXP006 streaming analysis over the complete validated pair file.

**Data generated:**
- `08_PROOFS/PROOF_ATTEMPT_004_FIXED_CUTOFF.md`.

**Proof status:**
- The tested cutoff proposition is computationally disproved; Strong Goldbach remains open.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- No universal bound for the least prime summand follows.

**Next verification required:**
- Any stronger finite or asymptotic cutoff must be stated and tested independently.

### 2026-10-03 — proof insight 005: adversarial local-sieve survivors

- Objective: Determine whether a fixed finite set of congruence tests could certify that both Goldbach addends are prime.
- Work performed: Constructed, for any sieve bound `B`, an even `E=q^2+r^2` with `q,r>B` odd primes and a candidate `a=q^2`.
- Results: Both `a` and `E-a` avoid every prime divisor at most `B`, yet both are composite. The construction is proved in `PROOF_ATTEMPT_005_ADVERSARIAL_SIEVE_SURVIVOR.md`.
- Interpretation: This is a rigorous limitation on local-sieve-only proof strategies. It does not challenge Goldbach; it shows exactly why “survives small moduli” cannot be silently converted into “is prime.”
- Literature status: No external source used.
- Next step: Any viable proof must add a genuinely global prime-correlation or primality-certification argument.

### Verification Checkpoint

**Claims made:**
- The adversarial construction proves the stated fixed-sieve limitation.
- It is not a counterexample to Strong Goldbach.

**Sources used:**
- None.

**Citations verified:**
- None required.

**Claims not independently verified:**
- No claim about the existence of a successful global method.

**Computations actually run:**
- None; this is a symbolic construction.

**Data generated:**
- `08_PROOFS/PROOF_ATTEMPT_005_ADVERSARIAL_SIEVE_SURVIVOR.md`.

**Proof status:**
- Limitation: PROVED RESULT.
- Strong Goldbach: OPEN; proof gap remains.

**Novelty status:**
- NOVELTY NOT ESTABLISHED; the limitation is elementary.

**Known uncertainties:**
- The construction does not address methods using stronger global information.

**Next verification required:**
- State any future global lemma explicitly and distinguish it from local admissibility.

### 2026-10-03 — proof insight 005 sanity check

- Objective: Check one concrete instance of the symbolic local-sieve limitation.
- Work performed: Tested `B=10`, `q=11`, `r=13`, giving `E=290`, `a=121`, and `E-a=169`.
- Results: Both composite squares avoid divisibility by every prime at most 10 (`2,3,5,7`), as predicted.
- Interpretation: The check illustrates the construction but adds no theorem beyond the written proof.
- Literature status: No external source used.
- Next step: Keep the result as a proof-design barrier; do not mistake it for a Goldbach counterexample.

### Verification Checkpoint

**Claims made:**
- The concrete instance satisfies the conditions in Proof Attempt 005.

**Sources used:**
- None.

**Citations verified:**
- None.

**Claims not independently verified:**
- None beyond the scope limits already stated.

**Computations actually run:**
- Direct divisibility check for `B=10`, `E=290`, `a=121`.

**Data generated:**
- Sanity-check details appended to the proof artifact.

**Proof status:**
- Symbolic limitation: PROVED RESULT.
- Strong Goldbach: OPEN.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- None affecting the stated construction.

**Next verification required:**
- Any future proof proposal must supply information beyond finite local divisibility tests.

### 2026-10-03 — literature frontier: source-reported Proposition (1+1.9)

- Objective: Identify the strongest directly relevant modern proof frontier before attempting another elementary proof.
- Work performed: Inspected Li–Liu's arXiv preprint `2606.05224`, including its definition of Proposition `(1+a)` and stated Theorem 1.1.
- Results: The source states an unconditional `(1+1.9)` result: sufficiently large even `N` can be written `N=p+rq` with `p,q` prime and `r=1` or prime satisfying `r<=q^0.9`. It identifies `(1+1)` with binary Goldbach and `(1+2)` with Chen's theorem. The source also states a conditional `(1+1.4)` result under an Elliott–Halberstam-type assumption.
- Interpretation: This is a crucial frontier constraint. Even a claimed modern improvement still allows an almost-prime factor and therefore does not prove binary Goldbach. Our elementary sieve attempts are far below the analytic machinery involved.
- Literature status: CIT-009 is verified for what the source says; the proof itself is not independently checked by this project.
- Next step: Do not present the preprint as a solved theorem without independent mathematical review. Use it to guide a precise proof-frontier map, not to claim Goldbach progress.

### Verification Checkpoint

**Claims made:**
- The inspected preprint states the `(1+1.9)` proposition and its relation to `(1+1)` and `(1+2)`.
- The source-reported result does not imply Strong Goldbach because `r` may exceed 1.

**Sources used:**
- CIT-009, directly inspected arXiv HTML.

**Citations verified:**
- CIT-009 verified for source metadata and stated claims; proof not independently verified.

**Claims not independently verified:**
- Correctness of the preprint's proof.
- Any numerical threshold hidden in “sufficiently large.”
- The conditional `(1+1.4)` claim beyond the source's statement.

**Computations actually run:**
- None.

**Data generated:**
- `08_PROOFS/PROOF_FRONTIER_001_ONE_PLUS_1_9.md`.

**Proof status:**
- No new proof. Strong Goldbach remains OPEN.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- The preprint requires independent expert verification before being treated as established literature.

**Next verification required:**
- If relying on this frontier result, inspect the full paper and obtain independent mathematical review; do not substitute it for a proof of `(1+1)`.

### 2026-10-03 — formalization-report audit of the `(1+1.9)` frontier

- Objective: Determine whether the public formalization report upgrades the Li–Liu source claim to an independently verified proof.
- Work performed: Inspected the third-party report at `https://subfish-zhou.github.io/goldbach-lean/report/index.html`; compared its stated public Lean interface with the arXiv source claim in CIT-009. Attempted to inspect linked GitHub/source pages, but those pages were unavailable in the browsing environment.
- Results: The report describes a public threshold/witness interface and the inequality `r^10 <= q^9`. It also explicitly says that an implemented corrected tenth fibre differs from the paper's printed fibre and that the complete global Buchstab-majorant argument was not audited line-by-line.
- Interpretation: This is crucial provenance evidence, but not an independently verified proof certificate. The theorem remains SOURCE-REPORTED/PARTIALLY VERIFIED in this repository. The almost-prime statement still does not imply binary Goldbach.
- Literature status: CIT-010 is verified only for the report's own contents. No claim that the Lean formalization or Li–Liu theorem is correct has been added.
- Next step: Obtain exact source/build provenance and reproduce the formalization before upgrading the status.

### Verification Checkpoint

**Claims made:**
- The public report describes a Lean-facing interface for the Li–Liu `(1+1.9)` result.
- The report itself records a corrected-fibre discrepancy and limits the scope of its audit.
- These facts do not establish the correctness of the theorem or solve Strong Goldbach.

**Sources used:**
- CIT-009, directly inspected arXiv HTML.
- CIT-010, directly inspected public formalization report.

**Citations verified:**
- CIT-010 verified for the statements made by the report; it is third-party/source-reported evidence only.

**Claims not independently verified:**
- Completeness, reproducibility, and correctness of the Lean formalization.
- Equivalence of the corrected tenth fibre to the printed paper fibre.
- Correctness of Li–Liu's global proof and any implied theorem beyond the source-reported statement.

**Computations actually run:**
- None. No Lean build, replay, or formal proof checker was run.

**Data generated:**
- `08_PROOFS/PROOF_FRONTIER_002_FORMALIZATION_AUDIT.md`.

**Proof status:**
- Formalization audit: PARTIALLY VERIFIED / SOURCE-REPORTED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- Exact source/build provenance was not available in this session.

**Next verification required:**
- Reproduce the formalization from exact source and inspect the fibre discrepancy before treating it as a proof certificate.

### 2026-10-03 — public source and reproducibility-protocol audit

- Objective: Replace the earlier report-only assessment with direct inspection of the formalization's published source and verification instructions.
- Work performed: Inspected the public README (CIT-011), `Goldbach/OnePlusOneNine.lean` facade (CIT-013), `docs/VERIFICATION.md` (CIT-012), `docs/THEOREMS.md` (CIT-014), and `lean-toolchain` (CIT-015). Checked local availability of `lake`, `elan`, and `lean`.
- Results: The facade visibly states the natural-power `(1+1.9)` interface `N=p+r*q`, `r=1` or prime, `r^10<=q^9`, and count endpoints. The verification guide documents five gates: source build, static source checks, theorem/axiom probes, separate module replay, and isolated reconstruction. The pinned toolchain file states Lean `v4.33.0-rc1`.
- Interpretation: This is materially stronger provenance than the earlier web report alone. It still does not constitute an independent verification in this repository because no external checkout, build, replay, CI-log capture, or immutable revision comparison was performed. The source theorem remains almost-prime and does not imply binary Goldbach.
- Local execution status: No `lake`, `elan`, or `lean` executable was found in the local environment; no computation or formal proof replay was run.
- Next step: Obtain an immutable source revision, install the pinned toolchain, execute all documented checks in a clean directory, preserve logs/hashes, and compare the formalized contracts with the paper and corrected-fibre note.

### Verification Checkpoint

**Claims made:**
- The public project contains inspectable source for the `(1+1.9)` facade and documents a five-part verification protocol.
- The source facade's public statement permits `r>1`, so it is not binary Goldbach.
- This repository has not independently reproduced the formalization.

**Sources used:**
- CIT-011, CIT-012, CIT-013, CIT-014, CIT-015.
- Earlier CIT-009 and CIT-010 for the paper/report comparison.

**Citations verified:**
- CIT-011 through CIT-015 verified for the contents of the cited published files; execution and mathematical correctness remain separate questions.

**Claims not independently verified:**
- That the current main revision passes every documented gate.
- That the imported implementation proofs are equivalent to the Li–Liu paper in every detail.
- That the corrected tenth-fibre discrepancy has been resolved.

**Computations actually run:**
- Only a local executable-availability check; no Lean/Lake build or proof replay.

**Data generated:**
- `08_PROOFS/PROOF_FRONTIER_003_SOURCE_REPRODUCIBILITY_AUDIT.md`.

**Proof status:**
- External formalization: SOURCE INSPECTED; REPRODUCTION NOT RUN.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- Mutable `main` branch and possible report/API/source revision mismatch.

**Next verification required:**
- Reproduce the pinned source build and all checks from an immutable revision, with preserved raw logs and hashes.

### 2026-10-03 — frozen-checkout Windows verifier audit

- Objective: Execute the first documented verification gate from a frozen source revision and determine whether any failure is mathematical or infrastructural.
- Work performed: Cloned the public repository at commit `09b97db5764ade1246bfb77206baa1b124760958` into `12_ARCHIVE/EXTERNAL_SOURCE/goldbach-lean-main`; recorded source hashes; ran `python -u scripts/check.py --static-only` unchanged; then ran an in-memory diagnostic changing only `/` normalization to handle both `\\` and `/`.
- Results (unchanged checker): Exit code `1`; `source_modules=2514`, but `reachable_modules=3`, `default_library_glob_modules=3`, `default_build_modules=3`; the instrumented summary counted `4478` issues, beginning with missing local modules whose names contain Windows backslashes. The relevant source expression is line 181 of `scripts/check.py`.
- Results (in-memory diagnostic): Exit code `0`; `source_modules=2514`, `reachable_modules=1745`, `default_library_glob_modules=2514`, `default_build_modules=2514`, `issues=[]`.
- Interpretation: The first gate is not portable to this Windows environment at the frozen revision. The one-line diagnostic isolates a path-normalization bug in the checker. This is not evidence against the Li–Liu theorem and does not substitute for a Lean build.
- Literature status: CIT-016 verified for source text and the observed runtime behavior. No theorem-correctness claim added.
- Next step: Use the intended Unix/CI environment or obtain an accepted portability fix, then run the full Lean build, theorem/axiom probes, module replay, and isolated reconstruction; preserve all logs.

### Verification Checkpoint

**Claims made:**
- The unmodified static checker failed in the frozen Windows checkout.
- The failure is caused by path-separator handling, as shown by the separator-only in-memory diagnostic.
- The failure is infrastructural and does not prove or disprove the mathematics.

**Sources used:**
- CIT-016 and frozen external checkout at commit `09b97db5764ade1246bfb77206baa1b124760958`.

**Citations verified:**
- CIT-016 verified against the frozen source and actual run.

**Claims not independently verified:**
- Any full Lean build or theorem/axiom report.
- The mathematical correctness of imported proof implementations.

**Computations actually run:**
- Unmodified static checker: exit `1`.
- In-memory separator-only diagnostic: exit `0`.
- No Lean/Lake build was run.

**Data generated:**
- Frozen external checkout under `12_ARCHIVE/EXTERNAL_SOURCE/goldbach-lean-main`.
- `08_PROOFS/PROOF_FRONTIER_004_WINDOWS_VERIFIER_FAILURE.md`.

**Proof status:**
- External formalization: SOURCE INSPECTED; STATIC CHECKER NOT PORTABLE ON WINDOWS AT FROZEN REVISION.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- Whether the project's Unix/CI environment passes the unchanged checker.
- Whether the current upstream revision after the frozen commit contains a portability fix.

**Next verification required:**
- Re-run in intended environment or with an upstream-approved portability fix, then execute the remaining gates.

### 2026-10-04 — pinned Lean toolchain/cache reproduction

- Objective: Continue the external formalization audit using the immutable checkout and the repository-declared Lean toolchain.
- Work performed: Installed elan and `leanprover/lean4:v4.33.0-rc1`; verified Lean/Lake versions; ran `lake exe cache get`; preserved the partial cache; started `lake build Goldbach.OnePlusOneNine`.
- Results: Cache retrieval announced `8679` files, reached approximately 99%, decompressed `8239`, reported `393` failed decompressions and `10` failed downloads, then stalled with connection-reset/path/decompression errors and was terminated with Ctrl-C (exit `1`). The first focused build exited `1` with 23 failed targets and `.olean.private` read errors. An incremental rerun also exited with `error: build failed` and further `.olean.private` failures. Direct `lake env lean Mathlib/Data/Int/Log.lean` exited `0`, but direct `lake env lean Goldbach/OnePlusOneNine.lean` exited `1` because `MathlibNt.SieveTheory.LiLiuGoldbachG11AuthorQuantitative.olean` was not built. A third parallel attempt was interrupted after a native `std::bad_alloc` (`3221226505`) and further missing-private-artifact errors.
- Interpretation: This is an environment/cache/build reproducibility result, not a mathematical result. The direct module success shows at least one earlier read error was transient or build-order related; the facade and complete target remain unreproduced. A successful focused build would still not independently establish the paper correspondence or binary Goldbach.
- Literature status: CIT-015 remains verified for the declared toolchain; no new external theorem claim is added. Local process evidence is recorded as CLM-REPRO-002.
- Data generated: partial cache under the user toolchain/cache locations and `08_PROOFS/PROOF_FRONTIER_005_LEAN_CACHE_REPRODUCTION.md`.

### Verification Checkpoint

**Claims made:**
- The pinned toolchain was installed and its reported versions were observed.
- The cache retrieval partially failed with the recorded counts and errors.
- The focused build attempts exited unsuccessfully; the direct Mathlib module succeeded, while the direct facade elaboration did not.

**Sources used:**
- CIT-015 for the upstream toolchain declaration; local frozen checkout and terminal output for the reproduction facts.

**Citations verified:**
- No new external citation; CIT-015 was previously verified against the published `lean-toolchain` file.

**Claims not independently verified:**
- Any theorem correctness, paper-to-code equivalence, or full verification-gate completion.
- Whether the failed build behavior is specific to this Windows/cache environment or reproducible in the intended CI/Unix environment.

**Computations actually run:**
- `lake exe cache get`: exit `1` after partial retrieval and Ctrl-C.
- `lake build Goldbach.OnePlusOneNine`: exit `1` on the first run; incremental rerun also exit `1`.
- `lake env lean Mathlib/Data/Int/Log.lean`: exit `0`.
- `lake env lean Goldbach/OnePlusOneNine.lean`: exit `1` due to an unbuilt `MathlibNt` object.
- Third parallel attempt: interrupted after a native `std::bad_alloc`; no success claimed.

**Proof status:**
- External formalization: SOURCE INSPECTED; FULL REPRODUCTION NOT ACHIEVED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- Whether a reliable cache or intended CI/Unix environment can complete the focused build and subsequent theorem/axiom/replay gates.

**Next verification required:**
- Re-run from a reliable complete cache or intended CI/Unix environment, then run the documented theorem/axiom, module replay, and isolated reconstruction gates if the environment permits.

### 2026-10-04 — source/axiom surface audit

- Objective: Extract the strongest conclusion available without overstating failed Lean execution.
- Work performed: Inspected `Goldbach/OnePlusOneNine.lean`, `Goldbach/OnePlusOneNineChecks.lean`, `Goldbach/Theorem.lean`, and the axiom/static-check sections of `scripts/check.py`; reran the static checker in memory with separator normalization only.
- Results: The in-memory static scan reported `source_modules=2514`, `reachable_modules=1745`, `default_library_glob_modules=2514`, `default_build_modules=2514`, and `issues=[]`. The scan masks comments/strings and checks for `sorry`, `admit`, `axiom`, `native_decide`, `unsafe`, and `debug.skipKernelTC`.
- Interpretation: This is a source-surface negative audit only. It does not provide the `#print axioms` outputs, kernel replay, theorem correctness, paper correspondence, or a binary Goldbach proof.
- Literature status: CIT-011 through CIT-015 remain the verified external source records; no new external theorem claim is made. Local result is CLM-REPRO-003.
- Data generated: `08_PROOFS/PROOF_FRONTIER_006_SOURCE_AXIOM_SURFACE_AUDIT.md`.

### Verification Checkpoint

**Claims made:**
- The separator-normalized in-memory source scan found no reported static issues.
- The source files expose `#print axioms` probes, but their kernel outputs were not obtained.

**Sources used:**
- CIT-011 through CIT-015 and the frozen checkout at commit `09b97db5764ade1246bfb77206baa1b124760958`.

**Citations verified:**
- No new external citation; source contents were rechecked locally against the frozen checkout.

**Claims not independently verified:**
- Any allowed-axiom result, semantic proof correctness, paper equivalence, or Strong Goldbach theorem.

**Computations actually run:**
- In-memory separator-normalized static scan: `issues=[]`.
- No kernel `#print axioms` or `leanchecker` completion.

**Proof status:**
- External formalization: SOURCE-SCAN PASSED IN MEMORY; KERNEL AXIOM REPORT UNVERIFIED; FULL REPRODUCTION NOT ACHIEVED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- Whether the source compiles completely and whether all public declarations have only the three documented standard axioms.

**Next verification required:**
- Obtain a complete reproducible build/cache, then capture the four theorem-type/axiom reports, module replay, and isolated reconstruction outputs.

### 2026-10-04 — binary circle-method proof frontier

- Objective: Continue the proof analysis by isolating a concrete sufficient inequality for a binary circle-method proof and verifying the literature statement about the missing minor-arc estimate.
- Work performed: Inspected Helfgott's arXiv PDF *The ternary Goldbach problem* (CIT-017), including the Chen-theorem summary and equations (1.2)--(1.4). Wrote `08_PROOFS/PROOF_FRONTIER_007_BINARY_CIRCLE_METHOD.md`, which derives the major-arc domination condition from Fourier inversion and the triangle inequality.
- Results: For any nonnegative finitely supported prime-supported weight, if the real part of the major-arc contribution exceeds the absolute minor-arc bound `integral_m |S(alpha)|^2`, then the weighted binary representation count is positive and supplies a prime pair. No uniform proof of this inequality was obtained. The cited source explicitly identifies this binary minor-arc comparison as the point where the circle method fails; this is recorded as a proof gap, not as an impossibility result.
- Literature status: CIT-017 verified against the actual arXiv PDF. Its historical Chen statement is source-reported as prime plus a product of at most two primes, so it does not close the binary gap.
- Data generated: `08_PROOFS/PROOF_FRONTIER_007_BINARY_CIRCLE_METHOD.md`; no numerical experiment or Lean build was run in this stage.

### Verification Checkpoint

**Claims made:**
- The conditional major-arc domination lemma follows from Fourier orthogonality and the triangle inequality under the file's stated finite-support weight assumptions.
- Helfgott's source states that the binary circle-method route fails at the corresponding minor-arc comparison and describes the lack of sufficient minor-arc control.
- Chen's theorem as summarized by the source is an almost-prime result, not a binary Goldbach proof.

**Sources used:**
- CIT-017, the arXiv PDF inspected at the cited sections/pages.
- Self-contained derivation in `08_PROOFS/PROOF_FRONTIER_007_BINARY_CIRCLE_METHOD.md`.

**Citations verified:**
- CIT-017 source and the narrow claims above were checked against the PDF text on 2026-10-04.

**Claims not independently verified:**
- The underlying proofs of Chen's theorem or Helfgott's cited historical results.
- Any claim that the binary minor-arc obstacle is logically impossible to overcome.
- Any Strong Goldbach theorem.

**Computations actually run:**
- No numerical computation, Lean build, or external formalization replay was run in this stage.

**Proof status:**
- Conditional major-arc implication: PROVED under the explicitly stated assumptions.
- Uniform minor-arc domination: PROOF GAP — NOT PROVED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED; the file is an audit of a standard analytic step.

**Known uncertainties:**
- Whether newer work has established a different sufficient estimate; this stage did not perform an exhaustive literature search.

**Next verification required:**
- Any proposed replacement estimate must be checked against its exact hypotheses, quantifiers, and error terms before it can be used in the proof.

### 2026-10-04 — exceptional-set quantifier frontier

- Objective: Check whether a current exceptional-set theorem closes the remaining all-even-integers quantifier in Strong Goldbach.
- Work performed: Inspected Zhao's arXiv HTML v2 (CIT-018), including the abstract, definition of `E(X)`, and Theorem 1.1. Added `08_PROOFS/PROOF_FRONTIER_008_EXCEPTIONAL_SET.md` with the exact source-reported statement and an elementary quantifier audit.
- Results: The source reports `E(X)=O(X^(7/10))` with an ineffective implied constant, where `E(X)` counts even integers up to `X` not representable as two odd primes. Dividing by `X` gives density zero, but a sublinear nonnegative integer-valued exceptional count need not become zero; hence this does not prove Strong Goldbach or provide a computable threshold.
- Literature status: CIT-018 was verified against the actual arXiv HTML v2. The theorem is recorded as SOURCE-REPORTED; its proof was not independently checked.
- Data generated: `08_PROOFS/PROOF_FRONTIER_008_EXCEPTIONAL_SET.md`; no numerical computation or Lean build was run in this stage.

### Verification Checkpoint

**Claims made:**
- Zhao's source states the exact exceptional-set definition and `O(X^(7/10))` bound with ineffective constant.
- The bound implies density zero by division by `X`.
- The bound alone does not imply eventual absence of exceptions; this is an elementary quantifier observation.

**Sources used:**
- CIT-018, arXiv HTML v2 inspected on 2026-10-04.
- Self-contained logical analysis in `08_PROOFS/PROOF_FRONTIER_008_EXCEPTIONAL_SET.md`.

**Citations verified:**
- CIT-018 checked against the abstract and Section 1 of the actual source.

**Claims not independently verified:**
- Zhao's underlying proof of Theorem 1.1.
- Any effective value of the implied constant or a finite threshold.
- Any Strong Goldbach theorem.

**Computations actually run:**
- No numerical computation, Lean build, or formalization replay was run in this stage.

**Proof status:**
- Density-zero consequence: PROVED conditional on the source-reported big-O statement.
- Eventual-zero exceptional set: PROOF GAP — NOT PROVED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED; this is a literature/quantifier audit.

**Known uncertainties:**
- Whether a later paper improves the exceptional-set exponent or makes the bound effective; no exhaustive search was performed.

**Next verification required:**
- Any attempt to turn an exceptional-set estimate into Strong Goldbach must establish eventual zero exceptions, not merely a sublinear count, and must verify all constants and quantifiers.

### 2026-10-04 — `(1+1.9)` witness-count split

- Objective: Test whether the source-reported Li--Liu `(1+1.9)` theorem can be converted into a binary Goldbach proof by counting its witnesses.
- Work performed: Inspected Li--Liu arXiv HTML v2 (CIT-019), including the exact definition of Proposition `(1+a)` and Theorem 1.1. Added `08_PROOFS/PROOF_FRONTIER_009_ALMOST_PRIME_SPLIT.md` with an exact partition into `r=1` and `r>1` witnesses.
- Results: The source reports `D_(1,1.9)(N)>0.0004*C(N)*N/log^2(N)` for sufficiently large even `N`, but the count includes prime `r>1`, so `r*q` can be composite. Binary Goldbach would follow if the composite-witness subcount were strictly smaller than that lower bound; no such estimate was found or proved.
- Literature status: CIT-019 verified against the actual arXiv HTML v2. The source theorem is recorded as SOURCE-REPORTED; its analytic proof was not independently checked.
- Data generated: `08_PROOFS/PROOF_FRONTIER_009_ALMOST_PRIME_SPLIT.md`; no numerical computation or Lean build was run in this stage.

### Verification Checkpoint

**Claims made:**
- Li--Liu's source defines the witness form with `r=1` or prime and states the quoted positive lower bound for the total count.
- The total count partitions exactly into `r=1` and `r>1` subcounts.
- An upper bound on the `r>1` subcount below the positive lower bound would imply a binary representation; that estimate is not proved here.

**Sources used:**
- CIT-019, arXiv HTML v2 inspected on 2026-10-04.
- Self-contained counting reduction in `08_PROOFS/PROOF_FRONTIER_009_ALMOST_PRIME_SPLIT.md`.

**Citations verified:**
- CIT-019 checked against the exact definition and Theorem 1.1 in the source.

**Claims not independently verified:**
- Li--Liu's underlying analytic proof and all imported constants.
- Any estimate controlling the composite-witness subcount.
- Any Strong Goldbach theorem.

**Computations actually run:**
- No numerical computation, Lean build, or formalization replay was run in this stage.

**Proof status:**
- Witness-count partition and conditional implication: PROVED as elementary counting logic.
- Composite-witness upper bound: PROOF GAP — NOT PROVED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED; this is a source audit and logical reduction.

**Known uncertainties:**
- Whether the Li--Liu paper or later work supplies a sufficiently small uniform composite-witness bound; this stage did not independently reprove the analytic estimates.

**Next verification required:**
- Any claimed conversion from `(1+1.9)` to binary Goldbach must explicitly bound `D_comp(N)` with matching constants and quantifiers.

### 2026-10-04 — Li--Liu source-boundary audit

- Objective: Check the Li--Liu proof text for any hidden step that converts its `(1+1.9)` mixed witness count into an `r=1` binary witness.
- Work performed: Inspected the source's definition of `D_(1,a)(N)` and the proof's sieve-weight case analysis in CIT-019, especially equations (4.4)--(4.7) and the explicit `w(n)=1` characterization.
- Results: The source weight is explicitly one on either a prime or a product of two primes in the relevant range. The displayed lower bound therefore counts a mixed prime/semiprime set; no `r=1` extraction appears in the inspected step. This confirms the conditional split in `PROOF_FRONTIER_009_ALMOST_PRIME_SPLIT.md` and does not provide a binary proof.
- Literature status: CIT-019 was rechecked against the actual HTML v2 source at the cited locations. The analytic estimates remain source-reported and were not independently rederived.
- Data generated: `08_PROOFS/PROOF_FRONTIER_010_LIL_SOURCE_BOUNDARY.md`; no numerical computation or Lean build was run in this stage.

### Verification Checkpoint

**Claims made:**
- The source defines `D_(1,a)` using `N-p=r*q` with `r=1` or prime.
- The displayed sieve weight counts a prime or a two-prime product in the relevant case.
- No `r=1` conversion is present in the inspected source step; this is a scope audit, not a claim that no other future argument could exist.

**Sources used:**
- CIT-019, arXiv HTML v2 inspected on 2026-10-04.
- Self-contained source audit in `08_PROOFS/PROOF_FRONTIER_010_LIL_SOURCE_BOUNDARY.md`.

**Citations verified:**
- CIT-019 rechecked at the definition, theorem, and sieve-weight locations.

**Claims not independently verified:**
- The correctness of Li--Liu's analytic estimates and numerical constants.
- Any estimate controlling the semiprime portion.
- Any Strong Goldbach theorem.

**Computations actually run:**
- No numerical computation, Lean build, or formalization replay was run in this stage.

**Proof status:**
- Source-scope audit: VERIFIED for the inspected text.
- `r>1` elimination: PROOF GAP — NOT PROVED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- Whether an uninspected later argument in the paper yields a separate `r=1` estimate; none appears in the audited definition/lower-bound step.

**Next verification required:**
- Any proposed `r=1` extraction must be located explicitly and checked with its exact hypotheses and constants.

### 2026-10-04 — elementary composite-witness bound

- Objective: Attempt to bound the `r>1` part of the Li--Liu witness count using only factor enumeration.
- Work performed: Added `08_PROOFS/PROOF_FRONTIER_011_ELEMENTARY_COMPOSITE_BOUND.md`, counting possible `(r,q)` pairs by splitting at `sqrt(N)` and applying the harmonic-sum bound.
- Results: For the composite-witness count, `D_comp(N) <= 2N + N log N` after dropping primality and exponent restrictions. This is valid but far too weak for the `N/log^2(N)`-scale bound required by the conditional reduction; simultaneous primality/correlation information is unavoidable.
- Literature status: No new external source was used in this stage. The result is a self-contained proved limitation.
- Data generated: `08_PROOFS/PROOF_FRONTIER_011_ELEMENTARY_COMPOSITE_BOUND.md`; no numerical computation or Lean build was run.

### Verification Checkpoint

**Claims made:**
- The factor-pair split at `sqrt(N)` and harmonic estimate give `D_comp(N) <= 2N + N log N`.
- This bound does not reach the scale needed to subtract composite witnesses from Li--Liu's lower bound.

**Sources used:**
- Self-contained derivation in `08_PROOFS/PROOF_FRONTIER_011_ELEMENTARY_COMPOSITE_BOUND.md`.

**Citations verified:**
- No new external citation was used.

**Claims not independently verified:**
- Any sharper sieve or prime-correlation estimate for `D_comp(N)`.
- Any Strong Goldbach theorem.

**Computations actually run:**
- No numerical computation, Lean build, or formalization replay was run in this stage.

**Proof status:**
- Crude factor-pair limitation: PROVED.
- Required composite-witness upper bound: PROOF GAP — NOT PROVED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- Whether an external theorem supplies the needed correlation estimate; no new theorem was substituted without verification.

**Next verification required:**
- Any sharper bound must retain the primality of `p=N-r*q` and be compared with Li--Liu's exact constants and quantifiers.

### 2026-10-04 — prime-density composite-witness bound

- Objective: Strengthen the elementary `D_comp(N)` limitation using a source-verified prime-counting estimate.
- Work performed: Inspected Bennett--Martin--O'Bryant--Rechnitzer (CIT-020), Theorem 1.3, and derived its fixed-modulus consequence `pi(x)=O(x/log x)` by summing the two reduced classes modulo 3. Applied this to the factor split in `08_PROOFS/PROOF_FRONTIER_012_PRIME_DENSITY_BOUND.md`.
- Results: The composite-witness count improves from `O(N log N)` to `O(N)` after using prime density, but this remains far above the `N/log^2(N)` scale needed to force an `r=1` witness. The missing ingredient is correlation involving `p=N-r*q`, not prime density alone.
- Literature status: CIT-020 verified against the actual arXiv HTML theorem statement. The analytic proof and constants were not independently rederived.
- Data generated: `08_PROOFS/PROOF_FRONTIER_012_PRIME_DENSITY_BOUND.md`; no numerical computation or Lean build was run.

### Verification Checkpoint

**Claims made:**
- CIT-020 supplies a fixed-modulus `pi(x)=O(x/log x)` input after an elementary reduction.
- Combining it with the factor split gives `D_comp(N)=O(N)`.
- This bound is insufficient for the Li--Liu subtraction target.

**Sources used:**
- CIT-020, Theorem 1.3.
- Self-contained deduction in `08_PROOFS/PROOF_FRONTIER_012_PRIME_DENSITY_BOUND.md`.

**Citations verified:**
- CIT-020 checked against the actual arXiv HTML on 2026-10-04.

**Claims not independently verified:**
- The proof of CIT-020's analytic estimate.
- Any correlation estimate for `p=N-r*q`.
- Any Strong Goldbach theorem.

**Computations actually run:**
- No numerical computation, Lean build, or formalization replay was run in this stage.

**Proof status:**
- `D_comp(N)=O(N)` deduction: PROVED conditional on CIT-020.
- Required `N/log^2(N)` composite-witness bound: PROOF GAP — NOT PROVED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- Whether stronger correlation results can lower the composite-witness count to the required scale; no such result was substituted without verification.

**Next verification required:**
- Seek a theorem controlling simultaneous primality of `r`, `q`, and `N-r*q` with matching uniformity and constants.

### 2026-10-04 — source-stated switching barrier

- Objective: Determine whether the Li--Liu source itself describes why elementary counting cannot control the composite-witness range.
- Work performed: Inspected Section 8.1 of CIT-019, including the term `G` with `p` up to `N^(1/2)` and the discussion of Chen's switching principle.
- Results: The source states that an upper bound without switching has the wrong order in the large-prime range, calls switching indispensable there, and reports that avoiding it leaves constants too poor for a nontrivial lower bound. This corroborates the current proof frontier but does not provide an `r=1` extraction or a `D_comp(N)` upper bound.
- Literature status: CIT-019 reverified against the actual HTML v2 at the cited lines. The analytic estimates remain source-reported.
- Data generated: `08_PROOFS/PROOF_FRONTIER_013_SOURCE_STATED_SIEVE_BARRIER.md`; no numerical computation or Lean build was run.

### Verification Checkpoint

**Claims made:**
- The Li--Liu source explicitly identifies a large-prime switching barrier and poor constants without it.
- This is relevant evidence for the missing composite-witness estimate, not a proof that no alternative method exists.

**Sources used:**
- CIT-019, Section 8.1.
- Self-contained interpretation in `08_PROOFS/PROOF_FRONTIER_013_SOURCE_STATED_SIEVE_BARRIER.md`.

**Citations verified:**
- CIT-019 checked at lines 2180--2197 of the actual arXiv HTML v2.

**Claims not independently verified:**
- The correctness of the source's switching estimates and constants.
- Any `D_comp(N)` correlation bound or Strong Goldbach theorem.

**Computations actually run:**
- No numerical computation, Lean build, or formalization replay was run in this stage.

**Proof status:**
- Source-stated sieve barrier: VERIFIED for the cited text.
- Composite-witness elimination: PROOF GAP — NOT PROVED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- Whether a different, non-switching correlation argument could overcome the stated barrier.

**Next verification required:**
- Any proposed replacement must be checked for the same large-prime range and constant loss.

## Failed approaches

- EXP002: A hard-coded experiment ID meant the output directory and metadata disagreed. Preserved in `04_RAW_DATA/EXP002`; see `INVALID_METADATA_DO_NOT_USE.md`. The correction was an explicit experiment-ID argument and a rerun into a new directory.
- EXP004: Per-value trial-division validation caused a 4–100000 run to exceed the execution window. A partial pair file was preserved and marked unusable. EXP005 deferred full validation to separately executed validators.

### 2026-10-05 — Barca arXiv proof-claim audit

- Objective: Audit an actual arXiv source that claims to prove binary Goldbach, without treating the claim as established.
- Work performed: Inspected the source HTML for the Main Theorem, Lemma 1.2, Lemma 1.4, and Lemma 3.1. Compared the quantifiers in the fixed-ε convergence statement with the later (k)-dependent tolerance ε_k = Δ p_k^2/(m_k-p_k^2). Checked the source's displayed density inequality at the moving level h=k.
- Result: The source supplies ordinary fixed-ε convergence but then asserts a shrinking-ε_k estimate uniformly over 1≤h≤k. The source's Step 5/Step 4 transition does not provide the required quantitative rate; its own text says the extension is “reasonable”/an assumption. The displayed bound at h=k allows an error factor δ_k/Δ times ε_k, so it does not establish the needed error <ε_k. This is a concrete PROOF GAP — NOT PROVED, not a disproof of the theorem.
- Literature status: CIT-021 added and checked against the actual arXiv HTML on 2026-10-05. The paper remains a source-reported claimed proof; no independent proof verification or novelty claim is made.
- Data generated: `08_PROOFS/PROOF_FRONTIER_014_BARCA_CLAIM_AUDIT.md`; no numerical computation, Lean build, or formalization replay was run.

### Verification Checkpoint

**Claims made:**
- Barca's source states a binary Goldbach theorem and a density argument involving Lemmas 1.2, 1.4, and 3.1.
- The source does not justify the required shrinking-tolerance estimate uniformly over the moving range (1\le h\le k).
- The resulting lower-bound step is a PROOF GAP — NOT PROVED; this does not show the source theorem false.

**Sources used:**
- CIT-021, actual arXiv HTML for arXiv:1207.4802v14.
- Self-contained logical audit in `08_PROOFS/PROOF_FRONTIER_014_BARCA_CLAIM_AUDIT.md`.

**Citations verified:**
- CIT-021 checked at HTML lines 26--41, 63--133, 189--253, and 337--397 on 2026-10-05.

**Claims not independently verified:**
- Any prior-paper lemma cited by Barca.
- The source's sieve-density estimates beyond the displayed text.
- Any Strong Goldbach theorem.

**Computations actually run:**
- No numerical computation, Lean build, or formalization replay was run in this stage.

**Proof status:**
- Source-level quantifier/rate diagnosis: PROVED as a logical insufficiency of the cited steps.
- Barca's claimed lower-bound step: PROOF GAP — NOT PROVED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- A separate quantitative estimate might conceivably repair the source's argument; none was found or substituted here.

**Next verification required:**
- If pursuing this line, reconstruct the exact permitted-tuple definitions from the cited prior paper and test whether an explicit uniform rate can be proved. Do not treat the current source claim as a theorem until that step is independently established.

### 2026-10-06 — author-exposition density-transfer audit

- Objective: Check whether the author’s own explanatory material identifies the density-transfer step used in the claimed proof.
- Work performed: Inspected Ricardo Barca’s explanatory page and verified its definitions of the periodic permitted-tuple sequence, the full-period density, and the transition to the left/right subintervals.
- Result: The page explicitly says to suppose that permitted tuples are approximately regularly placed, then uses that supposition to infer that both subinterval densities are close to the full-period density and to conclude a positive left-block count. A full-period average alone does not imply a positive count in a specified initial subinterval; an elementary periodic-set construction demonstrates this logical non-implication. This corroborates the arXiv quantifier/rate gap in PROOF_FRONTIER_014.
- Literature status: CIT-022 added and checked against the actual author page on 2026-10-06. It is used as source documentation, not as peer-reviewed confirmation of the theorem.
- Data generated: `08_PROOFS/PROOF_FRONTIER_015_BARCA_AUTHOR_EXPOSITION_GAP.md`; no numerical computation, Lean build, or formalization replay was run.

### Verification Checkpoint

**Claims made:**
- The author’s own exposition uses an approximately-regular-placement supposition to transfer full-period density to the initial interval.
- That transfer is not a consequence of the full-period average alone.
- The claimed Goldbach proof therefore retains a SOURCE-CONFIRMED PROOF GAP — NOT PROVED at this bridge.

**Sources used:**
- CIT-022, actual author exposition at `ricardobarca.wordpress.com/very-easy/`.
- `08_PROOFS/PROOF_FRONTIER_015_BARCA_AUTHOR_EXPOSITION_GAP.md`.
- CIT-021 and `08_PROOFS/PROOF_FRONTIER_014_BARCA_CLAIM_AUDIT.md` for the arXiv follow-up audit.

**Citations verified:**
- CIT-022 checked at HTML lines 82--94 on 2026-10-06.

**Claims not independently verified:**
- The truth of Barca’s theorem or any cited prior-paper lemma.
- Any quantitative distribution estimate for the CRT-constrained permitted set.
- Any Strong Goldbach theorem.

**Computations actually run:**
- No numerical computation, Lean build, or formalization replay was run in this stage.

**Proof status:**
- Full-period density ⇒ initial-interval density: NOT VALID WITHOUT AN ADDITIONAL DISTRIBUTION THEOREM.
- Barca’s claimed lower-bound bridge: PROOF GAP — NOT PROVED.
- Strong Goldbach: OPEN; PROOF GAP — NOT PROVED.

**Novelty status:**
- NOVELTY NOT ESTABLISHED.

**Known uncertainties:**
- A separate, rigorous distribution estimate for the particular permitted set might repair the bridge; none was supplied or substituted here.

**Next verification required:**
- Reconstruct the exact CRT-permitted set and seek a quantitative interval-distribution estimate. Any such estimate must be proved for the moving (k)-dependent interval, not inferred from the period average.
