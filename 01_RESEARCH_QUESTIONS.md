# Research questions

Status labels follow `11_PAPER/RESEARCH_METHODS_AND_PROTOCOL.md`. No question
below claims a proof, and none claims novelty. Each question names the branch
where work on it happens (see `BRANCHING.md`).

## Closed stages

| Stage | Question | Outcome |
|---|---|---|
| EXP001–EXP006 | Can a correctness-first program generate and independently validate unordered Goldbach counts? | Yes, validated for 4–100000 (EXP005). |
| EXP007–EXP019 | What is the exact fixed-window minimum `M_k` of the two-class-per-prime residue model? | Exact for k = 1…9 (MILP, HiGHS); close prior art (Ziller–Morack, Hildebrand). |
| EXP020–EXP022 | Which fixed-N and primorial structures are elementary, and which are prime-level? | Elementary correspondences proved; prime-level Goldbach untouched. |

## Active questions

### RQ1 — Does `h2(k) < p_k^2` hold for all k, and how does `h2(k)/p_k^2` behave?
Why it matters: per the Ziller–Morack source, a bound on the paired-Jacobsthal
function `h2` is tied to a tightened Goldbach statement, so this is the one
finite quantity in the repo that sits on the literature frontier.
Branch: `research/h2-ratio-frontier`. Status: in progress.

### RQ2 — Why can standard sieves not reach the window boundary `p = sqrt(x)`?
Open item from CIT-036 (Pollack). Needs a primary-source statement of the
sifting limit for a dimension-2 sieve and the parity barrier.
Branch: `research/sieve-dimension-barrier`. Status: answered at literature level in
`08_PROOFS/PROOF_FRONTIER_023_SIEVE_DIMENSION_BARRIER.md`; primary-text confirmations still listed there.

### RQ3 — Are the `M_k` values solver-independent, and what are `M_10…M_12`?
Current k = 8, 9 results rest on one HiGHS run.
Branch: `verify/m-k-second-solver`. Status: queued.

### RQ4 — Does the Li–Liu `(1+1.9)` Lean formalization build on Linux?
The Windows reproduction failed on path handling and cache errors, which is
infrastructural.
Branch: `ci/lean-reproduction`. Status: queued.

## Standing constraints
- Finite computation is never presented as a proof of Strong Goldbach.
- Every new claim needs a source check (`09_LITERATURE/`) before it enters the log.
- Raw data is never overwritten; reruns get a new experiment ID.

## RQ1 follow-up (2026-11-12): search-algorithm lead
The unpaired Jacobsthal literature (CIT-045) reaches n=54 using greedy-ordered, bound-pruned permutation search. A paired analogue
(choose the class *pair* covering most uncovered positions first; re-derive the bounds for two classes) is untested and is the most
concrete route beyond k=11 (EXP032: ~1.4e10 nodes; extrapolated ~1e12 for k=12). Status: idea only, no experiment yet.
