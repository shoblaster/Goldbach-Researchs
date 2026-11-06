# Roadmap

Status: Strong Goldbach is open. This repository is an auditable research checkpoint, not a claim of a proof. This roadmap lists realistic next steps, ordered by value for the effort.

## Near term (days)
1. Merge the open pull request and turn on GitHub Pages (Settings, Pages, source "GitHub Actions").
2. Add a LICENSE, a CITATION.cff, a repository description and topics.
3. Deposit a tagged release on Zenodo to get a DOI so the dataset and logs can be cited.
4. Add a short top-level README section pointing to `06_EXPERIMENTS/INDEX.md`, the claim ledger and this roadmap.

## Computation (weeks)
1. Scale the counts-only pipeline above 10^6 (a segmented sieve, counts stored, pairs not stored). Validate each range against EXP024 before any interpretation.
2. Independently cross-check the Lean `(1+1.9)` formalization build in a Unix or CI environment. Record logs and hashes. The Windows run failed on cache and path issues.
3. Test whether the Li-Liu composite-witness count can be bounded numerically on small ranges, as an illustration only.

## Literature and proof (months)
1. Read the full Li-Liu preprint and track whether independent experts confirm it. It proves a `(1+1.9)` statement, which still allows an almost-prime factor and does not give binary Goldbach.
2. Keep the proof-gap register current. Add a new entry only when the missing implication is stated exactly.
3. Pick a restricted problem that is actually tractable and genuinely open, such as an exceptional-set refinement or an effective version of a known bound, and search its exact wording before computing.

## Writing
1. Turn `11_PAPER/TECHNICAL_NOTE_DRAFT.md` into a short methods note on auditable computation for a conjecture (validation, invalid-run handling, claim ledger). That is a defensible contribution on its own.
2. Submit only a note that makes no claim beyond what the ledger supports.

## Not worth pursuing
- Counts, the comet plot, least summand statistics, and pair gap statistics. All have prior art or follow from standard heuristics (see CLAIM_LEDGER and the log).
- Elementary sieve proofs. Proof attempts 001 and 005 show the obstruction.
