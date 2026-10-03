# Proof frontier 002 — audit of the public Lean-formalization report

**Status at audit time: PARTIALLY VERIFIED / SOURCE-REPORTED; not an independently verified proof certificate. Later build attempts are recorded in Proof Frontier 005.**

## Scope of this audit

On 2026-10-03 I inspected the public report at:

<https://subfish-zhou.github.io/goldbach-lean/report/index.html>

The report discusses a Lean formalization of Li–Liu's 2026 preprint, *Theorem
(1+1.9) on the Goldbach Conjecture* (<https://arxiv.org/abs/2606.05224>). This
file records exactly what the report supports and what it does not support.

## What the report says

The report presents a public theorem interface of the form “there exists a
threshold `K` such that every even `N >= K` has witnesses `p`, `r`, and `q`,”
with the inequality `r^10 <= q^9` (equivalently, `r <= q^(9/10)` for positive
quantities). It describes this as the Lean-facing form of the source
paper's `(1+1.9)` statement.

The report also explicitly records two boundaries that are material to an
audit:

1. An implemented “corrected tenth fibre” differs from the fibre printed in
   the paper; equality with the paper's printed fibre is identified as a
   separate question.
2. The report does not claim that the paper's complete global Buchstab-majorant
   argument has been audited line by line. It describes formalized interfaces
   and components, not a project-independent certification that every printed
   proof transformation is correct.

## Verification classification

- **Verified:** the web report exists and makes the formalization/interface
  statements summarized above.
- **Not verified:** that the Lean source used by the report is complete,
  reproducible from this repository, or mathematically equivalent in every
  detail to the printed Li–Liu paper.
- **Not verified:** the correctness of Li–Liu's `(1+1.9)` theorem itself.

During this audit, attempts to open the report's linked GitHub/source pages
were unavailable in the browsing environment. At that stage no build, replay,
or checksum of the formalization was performed here. Later local attempts are
recorded in Proof Frontier 005. Accordingly, this report is evidence
of a serious formalization effort, not a completed proof certificate for this
project.

## Mathematical meaning

Even if the formalization were later independently reproduced and checked, the
reported proposition still permits a prime factor `r > 1`; it is therefore an
almost-prime statement and does not imply the binary equation `N = p + q`.
The Strong Goldbach proof gap remains open in this repository.

## Required next verification

Obtain the exact Lean source and build instructions, reproduce the build in a
clean environment, compare the formalized contracts with the arXiv version,
and separately inspect the corrected-fibre discrepancy before treating the
result as independently verified.
