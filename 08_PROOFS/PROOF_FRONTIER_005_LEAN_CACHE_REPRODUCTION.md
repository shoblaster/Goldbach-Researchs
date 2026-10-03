# Proof frontier 005 — pinned Lean cache and build reproduction

**Status: REPRODUCTION BLOCKED BY LOCAL BUILD ARTIFACT/RESOURCE FAILURES; NO MATHEMATICAL CONCLUSION.**

## Frozen inputs

- External checkout: `12_ARCHIVE/EXTERNAL_SOURCE/goldbach-lean-main`
- Commit: `09b97db5764ade1246bfb77206baa1b124760958`
- Declared toolchain: `leanprover/lean4:v4.33.0-rc1`
- Installed executable: Lean `4.33.0-rc1`, Lake `5.0.0-src+62eed1d`

## Cache retrieval run

Command actually run from the frozen checkout:

```text
lake exe cache get
```

Observed output summary (a compact raw run log is preserved at
`12_ARCHIVE/EXTERNAL_SOURCE/LEAN_REPRO_RUN_LOG_2026-10-04.txt`):

- The cache phase announced `8679` files.
- It reached approximately `99%` and decompressed `8239` files.
- `393` decompression attempts failed; `10` downloads failed.
- Repeated errors included `Recv failure: Connection was reset`, `The system cannot find the path specified (os error 3)`, and `Decompression error: leantar exited with code 1`.
- The process became idle without completing and was terminated with Ctrl-C. Exit code: `1`.
- The partial cache remains on disk; it was not deleted or replaced.

This is an environment/cache retrieval result. It is not evidence for or against any mathematical theorem.

## Focused build run

After the partial cache run, the following focused build was started:

```text
lake build Goldbach.OnePlusOneNine
```

The first full run exited `1` with `error: build failed`; Lake listed 23 failed targets. Representative errors were failure to read `Lean/Elab/Tactic/BuiltinTactic.olean.private` and other `.olean.private` artifacts while dependency compilation was in progress. A direct check of the first named module later exited `0`, so this is not evidence that that file is permanently absent.

An incremental rerun of the same target also exited with `error: build failed` (the command wrapper printed `lake_exit=1`). It reported additional `.olean.private` read failures, including `Lean/Elab/DeclNameGen.olean.private`, `Init/Data/Range/Polymorphic/Lemmas.olean.private`, and a list of 39 failed targets. The facade run itself was then tested directly:

```text
lake env lean Goldbach/OnePlusOneNine.lean
```

It exited `1` because the dependency object `MathlibNt.SieveTheory.LiLiuGoldbachG11AuthorQuantitative.olean` had not been produced.

A third attempt with `lake -KmaxJobs=1 build Goldbach.OnePlusOneNine` did not serialize the build (progress still showed parallel jobs). It was interrupted after further `.olean.private` failures and a native `std::bad_alloc` (`Lean exited with code 3221226505`).

The isolated direct module command that did succeed was:

```text
lake env lean .lake/packages/mathlib/Mathlib/Data/Int/Log.lean
```

It exited `0` after the first build attempt. This shows that at least one previously reported read failure was transient or build-order related; it does not establish completion of the target.

A completed Lean build would establish only that the frozen source compiles in this environment; it would not independently audit the paper correspondence or prove binary Goldbach.

## Reproducibility boundary

The external formalization remains **SOURCE INSPECTED; FULL REPRODUCTION NOT ACHIEVED**. The earlier unchanged static-checker failure is separately documented in `PROOF_FRONTIER_004_WINDOWS_VERIFIER_FAILURE.md`; this file records the independent cache/toolchain obstacle and the failed focused-build attempts.

## Raw-data preservation

The frozen checkout, commit, toolchain declaration, downloaded installer, partial cache, compact raw run log, commands, observed counts, and process exit state are preserved. No upstream source was edited.
