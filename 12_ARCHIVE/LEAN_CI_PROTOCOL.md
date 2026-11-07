# Protocol: reproducing the Li–Liu `(1+1.9)` Lean formalization on Linux

Branch: `ci/lean-reproduction`. Question: RQ4 in `01_RESEARCH_QUESTIONS.md`.
Status: **workflow authored; NOT YET RUN.** Nothing in this file is a verification result.

## Why
The Windows attempt (PROOF_FRONTIER_004/005) failed for infrastructural reasons: a path-separator bug in
the upstream static checker, then cache/`.olean.private` errors. Neither says anything about the
mathematics. A Linux run is the intended environment of the upstream project.

## What the workflow does
`.github/workflows/lean-reproduction.yml` (manual trigger) fetches a pinned upstream commit
(default: the frozen commit `09b97db5764ade1246bfb77206baa1b124760958`, with its `scripts/check.py`
SHA-256 compared to the recorded value) and follows upstream `docs/VERIFICATION.md`:

| Job | Upstream gate | Command(s) |
|---|---|---|
| `static-gate` | 2 Source surface | `python3 scripts/check.py --static-only` (unchanged) |
| `build-and-replay` | 1 Source build | `lake exe cache get`; `lake --wfail build <target>` |
| | 3 Literal targets and axioms | `python3 scripts/check.py` |
| | 4 Independent replay | `lake env leanchecker --verbose Goldbach.OnePlusOneNine` (and `...Checks`) |

Gate 5 (isolated reconstruction) is not automated here. Exit codes are recorded, not enforced, so logs are
always uploaded.

## Limits to keep in mind
* The default target is the focused `Goldbach.OnePlusOneNine`, not the full four-library build.
* The workflow executes third-party code from the pinned commit with read-only repository permissions and no
  secrets. Review it before running.
* A passing run would show the build and probes succeed on the pinned commit. It would **not** establish that the
  formalized statement is binary Goldbach (it is not: `r` may exceed 1), and not paper-to-code equivalence.
* Local execution of the upstream checker was not possible in the authoring session.

## Recording a result
After a run, add `12_ARCHIVE/EXTERNAL_SOURCE/LEAN_LINUX_RUN_<date>.md` with the commit, the exit codes from
`build.log` / `static-gate.log`, artifact names and hashes, and any error text verbatim, then a log entry with a
Verification Checkpoint. Do not edit the earlier Windows records.
