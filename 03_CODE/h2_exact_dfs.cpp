// Exact decision procedure for the paired-Jacobsthal covering problem (no solver library).
// For a given k and length L: can positions 1..L all be covered when, for each prime p in {5,...,p_k},
// at most two nonzero residues r are chosen and q is covered if q % p == r (r != 0)?
// (Choosing fewer than two residues never helps, so "at most two" equals "exactly two".)
// Search: take the smallest uncovered position q; some prime p with q % p != 0 and a free slot must choose
// r = q % p. Branch over these primes. Prune when the best possible coverage by the remaining free slots
// (for each prime, the largest uncovered residue-class counts) cannot cover the uncovered positions.
// h2(k) = 6 * omega2(k) + 6, omega2(k) = largest feasible L.
// Build: g++ -std=c++17 -O2 -Wall -Wextra h2_exact_dfs.cpp -o h2_exact_dfs
// Usage: ./h2_exact_dfs K L [K L ...]    prints FEASIBLE with a witness (re-checked) or INFEASIBLE with node count.
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstdint>
typedef unsigned __int128 u128;
static const int PR[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73};
static int L, np;
static std::vector<int> P;
static std::vector<std::vector<u128>> cls;       // cls[i][r] = positions q in 1..L with q % P[i] == r
static int slots[32]; static std::vector<int> chosen[32];
static u128 FULL; static unsigned long long nodes;
static inline int pc(u128 x) { return __builtin_popcountll((uint64_t)x) + __builtin_popcountll((uint64_t)(x >> 64)); }
static bool bound_ok(u128 unc) {
    int need = pc(unc), cap = 0;
    for (int i = 0; i < np; ++i) {
        if (!slots[i]) continue;
        int best1 = 0, best2 = 0;
        for (int r = 1; r < P[i]; ++r) { int c = pc(cls[i][r] & unc); if (c > best1) { best2 = best1; best1 = c; } else if (c > best2) best2 = c; }
        cap += best1 + (slots[i] >= 2 ? best2 : 0);
    }
    return cap >= need;
}
static bool dfs(u128 cov) {
    ++nodes;
    u128 unc = FULL & ~cov;
    if (!unc) return true;
    if (!bound_ok(unc)) return false;
    int q = 0; while (!((unc >> q) & 1)) ++q;        // smallest uncovered position (bit q = position q)
    for (int i = 0; i < np; ++i) {
        if (!slots[i] || q % P[i] == 0) continue;
        int r = q % P[i];
        --slots[i]; chosen[i].push_back(r);
        if (dfs(cov | cls[i][r])) return true;
        chosen[i].pop_back(); ++slots[i];
    }
    return false;
}
int main(int argc, char** argv) {
    if (argc < 3 || (argc - 1) % 2) { std::fprintf(stderr, "usage: %s K L [K L ...]\n", argv[0]); return 2; }
    for (int a = 1; a + 1 < argc; a += 2) {
        int k = std::atoi(argv[a]); L = std::atoi(argv[a + 1]);
        P.assign(PR + 2, PR + k); np = (int)P.size();
        cls.assign(np, {}); FULL = 0;
        for (int q = 1; q <= L; ++q) FULL |= (u128)1 << q;
        for (int i = 0; i < np; ++i) {
            cls[i].assign(P[i], 0);
            for (int q = 1; q <= L; ++q) cls[i][q % P[i]] |= (u128)1 << q;
            slots[i] = 2; chosen[i].clear();
        }
        nodes = 0;
        bool ok = dfs(0);
        if (ok) {   // re-check the witness directly
            bool good = true;
            for (int q = 1; q <= L && good; ++q) {
                bool c = false;
                for (int i = 0; i < np; ++i) if (q % P[i]) for (int r : chosen[i]) if (r == q % P[i]) c = true;
                good = c;
            }
            std::printf("k=%d L=%d FEASIBLE witness_check=%s nodes=%llu witness:", k, L, good ? "True" : "False", nodes);
            for (int i = 0; i < np; ++i) { std::printf(" %d:{", P[i]); for (int r : chosen[i]) std::printf("%d,", r); std::printf("}"); }
            std::printf("\n");
        } else std::printf("k=%d L=%d INFEASIBLE nodes=%llu\n", k, L, nodes);
        std::fflush(stdout);
    }
    return 0;
}
