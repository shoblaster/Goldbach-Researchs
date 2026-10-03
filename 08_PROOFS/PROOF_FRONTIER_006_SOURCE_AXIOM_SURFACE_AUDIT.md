# Proof frontier 006 — source/axiom surface audit

**Status: LEXICAL SOURCE AUDIT PASSED IN MEMORY; KERNEL AXIOM REPORT UNVERIFIED.**

## Scope and method

The frozen checkout at commit `09b97db5764ade1246bfb77206baa1b124760958` was inspected using the repository's own `scripts/check.py`. No source file was edited. The checker was loaded in memory with the Windows path-separator normalization diagnostic already documented in Proof Frontier 004:

```python
str(path.relative_to(ROOT).with_suffix("")) \
    .replace("\\", ".").replace("/", ".")
```

The resulting static scan reported:

```text
source_modules=2514
reachable_modules=1745
default_library_glob_modules=2514
default_build_modules=2514
issues=[]
```

The scanner masks comments and (by default) strings before looking for the prohibited tokens `sorry`, `admit`, `axiom`, `native_decide`, `unsafe`, and `debug.skipKernelTC`. Therefore the in-memory result is evidence that this lexical release-surface scan found no such prohibited token and no missing-local-module/coverage issue after separator normalization.

## What this does and does not establish

- The public facade source was directly inspected. `Goldbach/OnePlusOneNine.lean` wraps imported theorem constants; it does not contain a new proof body.
- `Goldbach/OnePlusOneNineChecks.lean` contains `#print axioms` commands for the four public declarations, but those reports require Lean elaboration.
- `scripts/check.py` accepts only `propext`, `Classical.choice`, and `Quot.sound` as standard axioms.
- The kernel axiom reports were **not obtained** because the focused build/facade elaboration was not completed. This audit therefore does not claim that the theorem proofs use only those axioms.
- No semantic theorem correctness, paper equivalence, or Strong Goldbach result follows from a lexical scan.

## Reproducibility boundary

Status remains **SOURCE INSPECTED; FULL REPRODUCTION NOT ACHIEVED**. The source scan is a useful negative audit result, but it is not a proof certificate.

## Raw-data preservation

The frozen checkout, commit, source hashes, exact scanner expression, and observed summary are preserved. The underlying source files remain unmodified.
