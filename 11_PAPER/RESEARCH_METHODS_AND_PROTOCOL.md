# Research methods and verification protocol

**Status:** prospective protocol for new work; earlier experiments were not preregistered.  
**Scope:** finite computational audit of the residue-selection model discussed in the Barca Sieve II source, not a claimed proof of Strong Goldbach.

## 1. Research question and stopping rule

The primary question is whether the stated finite residue-selection model has a rigorously computable extremal structure that clarifies (or falsifies) the density-transfer step in the proposed argument. A computation may establish only the finite instance and the exact convention implemented. It cannot by itself establish Strong Goldbach, an asymptotic bound, or novelty.

Work is considered substantively useful when it produces at least one of:

1. an exact finite optimum with an independently checkable formulation and raw output;
2. a source-verified proof gap or correction to an existing argument;
3. a reproducible counterexample to a stated finite claim; or
4. a literature-verified connection that changes the interpretation of the model.

If a proposed computation cannot meet one of these standards, it is reported as exploratory or stopped rather than promoted to a result.

## 2. Definitions and claim classes

Every result is labeled as one of the following:

- **THEOREM/PROOF:** a complete mathematical derivation whose hypotheses and quantifiers are explicit;
- **EXACT COMPUTATION:** exhaustive or exact optimization for a finite, stated instance, with code and raw output;
- **CROSS-CHECK:** an independent implementation or independently derived identity reproducing an exact result;
- **HEURISTIC:** randomized, approximate, or incomplete search; useful for witnesses only;
- **UNVERIFIED:** a statement not yet checked against the source or a rerunnable computation;
- **PROOF GAP — NOT PROVED:** a missing implication or unjustified quantifier transition;
- **NOVELTY NOT ESTABLISHED:** no priority claim is made unless the relevant literature has been searched and verified.

The words “proof,” “disproof,” “new,” “first,” and “solves Goldbach” are prohibited in summaries unless the corresponding evidence is recorded in the claim ledger and citation-verification file.

## 3. Computational procedure

For each experiment, the repository records:

1. the exact mathematical convention and finite search domain;
2. source code, interpreter/compiler, command, seed, and relevant options;
3. the experiment identifier and an immutable raw-output file;
4. independent invariants or a second implementation where feasible;
5. the result, limitations, and next verification required.

Exact searches must enumerate the stated domain or use a mathematically equivalent exact formulation. Optimization shortcuts must be justified in a proof note and checked against smaller cases by direct enumeration. Heuristics must never be used as lower bounds or as evidence of an exact minimum.

## 4. Error-control protocol

Before accepting a result, check at least two of: direct recomputation, an independent language/algorithm, exact rational arithmetic, small-instance exhaustive comparison, invariant identities, or a manually inspectable witness. If an error is discovered, preserve the original output, record the correction, rerun from the corrected source, and update the master log. Existing examples include the EXP013 probability-product correction and the EXP012 transcription correction; neither is silently erased from the audit trail.

## 5. Literature and citation protocol

External claims are checked against the actual cited source, not a search-result snippet. The URL, access date, exact claim supported, and limits of inspection are recorded in `09_LITERATURE/CITATION_VERIFICATION.md`. Related work is not treated as equivalent without reading enough of the source to establish equivalence. A failed or incomplete search is recorded as such, and global novelty is never inferred from absence of a search hit.

The handoff document's Sections 20–22 control this protocol. At every meaningful stage, update:

- `09_LITERATURE/CITATION_VERIFICATION.md` for source checks;
- `09_LITERATURE/CLAIM_LEDGER.md` for significant factual or mathematical claims;
- `00_MASTER_RESEARCH_LOG.md` for a Verification Checkpoint.

## 6. Reproducibility and publication rule

Raw data are never overwritten by a corrected run without documenting the correction. Generated binaries and machine-specific artifacts are excluded unless they are needed to reproduce a result. A paper or preprint is appropriate only for a clearly scoped technical note whose claims are all finite, cited, and reproducible; the repository must state explicitly that Strong Goldbach remains open and that no novelty claim has been established.

This protocol is a research-control document, not a mathematical result. Its adoption does not increase the evidentiary status of earlier experiments; it governs subsequent work.
