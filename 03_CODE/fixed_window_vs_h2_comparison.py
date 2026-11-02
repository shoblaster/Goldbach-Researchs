"""Compare EXP015 fixed-window minima with the source h_2 guarantee.

This is a derived, deterministic comparison. It reads the raw outputs of
EXP015 and EXP017, then applies the elementary bound

    M_k >= floor(p_k^2 / h_2(k)),

where h_2(k) guarantees a survivor in every block of h_2(k) consecutive
indices. The proof and scope are recorded in
08_PROOFS/PROOF_FRONTIER_017_OBJECTIVE_COMPARISON.md.
"""

from __future__ import annotations

import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
EXP015 = ROOT / "06_EXPERIMENTS/EXP015_BARCA_SIEVE2_K8_MILP_EXACT/RAW_OUTPUT.txt"
EXP017 = ROOT / "06_EXPERIMENTS/EXP017_PAIRED_JACOBSTHAL_ILP_CROSSCHECK/RAW_OUTPUT.txt"
EXP019 = ROOT / "06_EXPERIMENTS/EXP019_BARCA_SIEVE2_K9_MILP_EXACT/RAW_OUTPUT.txt"


def read_exp015(path: Path) -> dict[int, int]:
    text = path.read_text(encoding="utf-8")
    rows = re.findall(r"^k (\d+) limit \d+ exact_minimum (\d+)$", text, re.MULTILINE)
    if not rows:
        raise RuntimeError(f"no EXP015 minima found in {path}")
    return {int(k): int(m) for k, m in rows}


def read_exp017(path: Path) -> dict[int, tuple[int, int]]:
    text = path.read_text(encoding="utf-8")
    rows = re.findall(
        r"^k (\d+) p_k (\d+) omega2 \d+ reconstructed_h2 (\d+)$",
        text,
        re.MULTILINE,
    )
    if not rows:
        raise RuntimeError(f"no EXP017 h2 rows found in {path}")
    return {int(k): (int(p), int(h)) for k, p, h in rows}


def read_exp019(path: Path) -> dict[int, int]:
    text = path.read_text(encoding="utf-8")
    rows = re.findall(r"^k (\d+) limit \d+ exact_minimum (\d+)$", text, re.MULTILINE)
    if not rows:
        raise RuntimeError(f"no EXP019 minimum found in {path}")
    return {int(k): int(m) for k, m in rows}


def main() -> None:
    minima = read_exp015(EXP015)
    minima.update(read_exp019(EXP019))
    h2_rows = read_exp017(EXP017)
    primes = {1: 2, 2: 3, 3: 5, 4: 7, 5: 11, 6: 13, 7: 17, 8: 19, 9: 23}
    # EXP017 starts at k=3; k=1,2 are transcribed from the inspected source
    # table (arXiv:1706.03668, lines 66--75).
    source_h2_prefix = {1: 2, 2: 6, 9: 366}

    print("k,p_k,L=p_k^2,M_k,h2(k),floor(L/h2),M_k/floor(L/h2)")
    for k in sorted(minima):
        p, h = h2_rows.get(k, (primes[k], source_h2_prefix.get(k)))
        if h is None:
            raise RuntimeError(f"no h2 value available for k={k}")
        if p != primes[k]:
            raise AssertionError(f"unexpected prime at k={k}: {p}")
        length = p * p
        lower_bound = length // h
        minimum = minima[k]
        if minimum < lower_bound:
            raise AssertionError(
                f"finite bound violated at k={k}: M_k={minimum} < {lower_bound}"
            )
        ratio = minimum / lower_bound
        print(f"{k},{p},{length},{minimum},{h},{lower_bound},{ratio:.6g}")


if __name__ == "__main__":
    main()
