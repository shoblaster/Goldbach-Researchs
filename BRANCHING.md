# Branching and review model

`main` holds only reviewed, reproducible state. All work happens on topic
branches that merge by pull request.

| Prefix | Purpose | Example |
|---|---|---|
| `research/` | New mathematical or computational investigation | `research/h2-ratio-frontier` |
| `verify/` | Independent re-checks of existing results | `verify/m-k-second-solver` |
| `docs/` | Structure, indexes, write-ups | `docs/structure-cleanup` |
| `meta/` | Repository hygiene, privacy | `meta/privacy-redaction` |
| `ci/` | Automation and reproduction environments | `ci/lean-reproduction` |

## Rules
1. One question per branch; name it in `01_RESEARCH_QUESTIONS.md`.
2. A research branch adds, at minimum: one script in `03_CODE/`, one
   `06_EXPERIMENTS/EXPNNN_*/` folder (README plus `RAW_OUTPUT.txt`), a log entry
   with a Verification Checkpoint, and any claims in `09_LITERATURE/CLAIM_LEDGER.md`.
3. Experiment IDs are allocated in order and never reused. Take the next free
   ID from `06_EXPERIMENTS/INDEX.md`; if two branches collide, the later merge renumbers.
4. Never edit raw outputs from earlier experiments; supersede them.
5. Squash-merge, with the PR description stating proof status and novelty
   status in the repo's existing vocabulary (`PROVED`, `PROOF GAP — NOT PROVED`,
   `NOVELTY NOT ESTABLISHED`).
6. Log entries are appended to `00_MASTER_RESEARCH_LOG.md` at merge time, so
   parallel branches do not conflict on that file.
