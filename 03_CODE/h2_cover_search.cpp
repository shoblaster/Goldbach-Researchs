// Exact, solver-free feasibility search for the paired-Jacobsthal covering problem (CIT-029/031).
// Question for given k and length L: can positions 1..L all be covered when, for each prime
// p in {5,...,p_k}, exactly two nonzero residues r are chosen and position q is covered by p
// iff q%p == r (r != 0)?  (Same model as h2_frontier_verify.py.)
//
// Method: depth-first search that always branches on the LOWEST uncovered position q: some
// prime p with quota left must cover it, i.e. choose residue q%p for p. Prune with an exact
// upper bound on what the remaining quotas can still cover (sum over primes of the best t_p
// classes among currently uncovered positions). Every complete cover is reached by some path,
// so a finished search with no leaf is a proof of infeasibility.
// Build: g++ -std=c++17 -O3 -march=native h2_cover_search.cpp -o h2_cover_search
// Run:   ./h2_cover_search K L      -> prints FEASIBLE (+witness) or INFEASIBLE, node count
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
static const int NW = 4;                       // up to 256 positions
struct M { u64 w[NW]; };
static int K, L, NP, NWU;
static vector<int> P;
static vector<vector<M>> cls;                  // cls[i][r] (r=1..p-1): positions n in 1..L, n%p==r
static long long nodes = 0;
static int cnt[24];
static vector<int> chosen[24];
static vector<pair<int,int>> witness;

static inline int pcm(const M& a) { int c = 0; for (int i = 0; i < NWU; i++) c += __builtin_popcountll(a.w[i]); return c; }
static inline int pcand(const M& a, const M& b) { int c = 0; for (int i = 0; i < NWU; i++) c += __builtin_popcountll(a.w[i] & b.w[i]); return c; }
static inline int lowest_uncovered(const M& unc) {
    for (int i = 0; i < NWU; i++) if (unc.w[i]) return i * 64 + __builtin_ctzll(unc.w[i]) + 1;
    return -1;
}
static bool dfs(const M& unc) {
    nodes++;
    int total = pcm(unc);
    if (total == 0) { witness.clear(); for (int i = 0; i < NP; i++) for (int r : chosen[i]) witness.push_back({P[i], r}); return true; }
    // exact-gain upper bound for remaining quotas
    int bound = 0;
    for (int i = 0; i < NP; i++) {
        int t = 2 - cnt[i]; if (!t) continue;
        int b1 = 0, b2 = 0;
        for (int r = 1; r < P[i]; r++) {
            bool used = false; for (int u : chosen[i]) if (u == r) used = true;
            if (used) continue;
            int g = pcand(unc, cls[i][r]);
            if (g > b1) { b2 = b1; b1 = g; } else if (g > b2) b2 = g;
        }
        bound += (t == 2) ? b1 + b2 : b1;
    }
    if (bound < total) return false;
    int q = lowest_uncovered(unc);
    for (int i = 0; i < NP; i++) {
        if (cnt[i] >= 2) continue;
        int r = q % P[i]; if (r == 0) continue;
        M nu; for (int j = 0; j < NWU; j++) nu.w[j] = unc.w[j] & ~cls[i][r].w[j];
        cnt[i]++; chosen[i].push_back(r);
        bool ok = dfs(nu);
        cnt[i]--; chosen[i].pop_back();
        if (ok) return true;
    }
    return false;
}
int main(int argc, char** argv) {
    K = atoi(argv[1]); L = atoi(argv[2]);
    int all[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73};  // p_1..p_21
    if (K < 3 || K > 21) { fprintf(stderr, "K must be in 3..21\n"); return 2; }
    for (int i = 2; i < K; i++) P.push_back(all[i]);
    NP = P.size(); NWU = (L + 63) / 64;
    cls.resize(NP);
    for (int i = 0; i < NP; i++) {
        cls[i].assign(P[i], M());
        for (int r = 0; r < P[i]; r++) for (int j = 0; j < NW; j++) cls[i][r].w[j] = 0;
        for (int n = 1; n <= L; n++) if (n % P[i]) cls[i][n % P[i]].w[(n - 1) >> 6] |= 1ULL << ((n - 1) & 63);
    }
    M unc; for (int j = 0; j < NW; j++) unc.w[j] = 0;
    for (int n = 1; n <= L; n++) unc.w[(n - 1) >> 6] |= 1ULL << ((n - 1) & 63);
    bool ok = dfs(unc);
    // direct recheck of the witness from the definition
    bool direct = false;
    if (ok) {
        map<int, set<int>> ch; for (auto& pr : witness) ch[pr.first].insert(pr.second);
        direct = true;
        for (int q = 1; q <= L && direct; q++) { bool c = false; for (auto& kv : ch) if (q % kv.first && kv.second.count(q % kv.first)) c = true; direct = c; }
        for (int p : P) if (ch[p].size() > 2) direct = false;
    }
    printf("k %d L %d %s nodes %lld witness_direct_check %s\n", K, L, ok ? "FEASIBLE" : "INFEASIBLE", nodes, ok ? (direct ? "True" : "False") : "n/a");
    if (ok) { printf("witness"); for (auto& pr : witness) printf(" (%d:%d)", pr.first, pr.second); printf("\n"); }
    return 0;
}
