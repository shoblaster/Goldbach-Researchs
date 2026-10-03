# Proof frontier 003 — source and reproducibility audit

**Historical status at creation: SOURCE INSPECTED; REPRODUCTION NOT RUN. Later frozen-checkout and partial-build attempts are recorded in Proof Frontiers 004–006; current status is FULL REPRODUCTION NOT ACHIEVED.**

## Sources inspected

On 2026-10-03 the following public project files were inspected directly:

- Repository README: <https://github.com/subfish-zhou/goldbach-lean/blob/main/README.md>
- Public theorem facade: <https://raw.githubusercontent.com/subfish-zhou/goldbach-lean/main/Goldbach/OnePlusOneNine.lean>
- Verification guide: <https://github.com/subfish-zhou/goldbach-lean/blob/main/docs/VERIFICATION.md>
- Theorem interpretation: <https://github.com/subfish-zhou/goldbach-lean/blob/main/docs/THEOREMS.md>
- Toolchain declaration: <https://github.com/subfish-zhou/goldbach-lean/blob/main/lean-toolchain>

## Facts established by direct source inspection

1. The public Lean facade states an eventual theorem with witnesses `p`, `r`,
   and `q`, `p` and `q` prime, `r = 1` or prime, `N = p + r*q`, and
   `r^10 <= q^9`. The source also exposes count and coefficient-bound
   declarations.
2. The repository documents a five-part verification protocol: a warning-free
   source build; static source/import checks; literal theorem-type and axiom
   probes; separate module replay; and isolated reconstruction from an
   extracted source archive.
3. The documented allowed logical axioms are Lean's standard
   `propext`, `Classical.choice`, and `Quot.sound`. The verification script
   shown in the repository checks for additional axiom reports and prohibited
   source tokens.
4. The pinned toolchain file inspected on GitHub names
   `leanprover/lean4:v4.33.0-rc1`.

These are facts about the published source and its stated checks. They are not
yet independent results of this repository.

## What was not established at the time of this audit

- No checkout of the external repository was created here; a frozen checkout
  was created later and is recorded in Proof Frontier 004.
- No Lean, Lake, or `elan` executable was available in the local environment
  when checked, so no build, axiom probe, module replay, or isolated
  reconstruction was run at that stage. Later partial build attempts are
  recorded in Proof Frontier 005.
- No CI log or immutable commit digest was independently captured. The main
  branch may change, and the report/website/API artifacts may refer to
  different revisions.
- The source-level theorem statement was not yet compared line-by-line with
  every definition and proof transformation in the Li–Liu paper.
- The corrected-tenth-fibre discrepancy identified in the public report was
  not resolved by this inspection.

## Mathematical interpretation

The source statement is still an almost-prime theorem: `r` may be a prime
larger than `1`. It therefore does not imply `N = p + q` for every sufficiently
large even `N`, and it does not prove Strong Goldbach.

The new evidence upgrades the status from “only a web report was visible” to
“the project publishes inspectable source and a reproducibility protocol.” It
does **not** upgrade the status to independently verified in this repository.

## Required next step

Acquire an immutable commit/source archive, install the pinned Lean toolchain,
run the documented checks in a clean directory, preserve all stdout/stderr and
hashes, then compare the formalized contracts and corrected fibre against the
paper. Until that is done, retain **PARTIALLY VERIFIED / SOURCE-REPORTED**.
