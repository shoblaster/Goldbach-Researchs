# Proof frontier 004 — Windows reproducibility check failure

**Status: REPRODUCIBILITY FAILURE IN PROJECT CHECKER; NOT A MATHEMATICAL COUNTEREXAMPLE.**

## Frozen external checkout

The public repository was cloned into:

`12_ARCHIVE/EXTERNAL_SOURCE/goldbach-lean-main`

The checkout is frozen at commit:

`09b97db5764ade1246bfb77206baa1b124760958`

Recorded SHA-256 hashes:

- `scripts/check.py`: `BF381C6676357D490C00E972C0D6FD125ED83E247B35FD1E1F78DECF09B65015`
- `Goldbach/OnePlusOneNine.lean`: `FCD30B5C85984BDE811293EF38B17A79AD74AD3F6F982609D89FD6B015854560`
- `docs/VERIFICATION.md`: `3A9E1ADA6DF848A26AFFA96D0125075D6934331824E61D6CB3BA940BC0795414`

## Run A — unmodified checker

Command actually run from the checkout root:

```text
python -u scripts/check.py --static-only
```

Observed result:

- Exit code: `1`.
- JSON summary began with `source_modules: 2514`, `reachable_modules: 3`,
  `default_library_glob_modules: 3`, and `default_build_modules: 3`.
- The issue list contained `4478` entries, including missing-local-module messages whose left-hand module
  names used Windows backslashes, for example
  `AnalyticNumberTheory\\LargeSieve\\BombieriDavenport`, while imports use
  dotted names such as `AnalyticNumberTheory.LargeSieve.Multiplicative`.
- The script ended with `CHECK FAILED: release source checks failed`.

The relevant source line is line 181 of `scripts/check.py` in this frozen
checkout:

```python
module = str(path.relative_to(ROOT).with_suffix("")).replace("/", ".")
```

On Windows, `str(Path(...))` uses `\\`, so replacing only `/` leaves module
keys with backslashes and makes ordinary local imports appear missing.

## Run B — in-memory diagnostic only

No external source file was modified. The checker was loaded in memory with
only this expression changed:

```python
module = str(path.relative_to(ROOT).with_suffix("")).replace("\\", ".").replace("/", ".")
```

Observed result:

- Exit code: `0`.
- `source_modules: 2514`.
- `reachable_modules: 1745`.
- `default_library_glob_modules: 2514`.
- `default_build_modules: 2514`.
- `issues: []`.

This diagnostic isolates the failure to Windows path normalization in the
static checker. It does **not** run Lean, prove any theorem, or establish that
the external project passes its full verification protocol.

## Interpretation

The published verification protocol cannot be reproduced unchanged on this
Windows environment at the frozen revision. The failure is a tooling/portability
issue and does not by itself indicate a false mathematical theorem. At the time
of this checker audit the source formalization was **SOURCE INSPECTED;
REPRODUCTION NOT RUN**. Later partial toolchain/build attempts are recorded in
Proof Frontier 005; the current status remains **FULL REPRODUCTION NOT ACHIEVED**.

## Raw-data preservation

The frozen source checkout, commit identifier, source hashes, exact commands,
exit codes, and machine-readable summaries above are preserved. No generated
Lean artifacts or source modifications were mixed into the checkout.
