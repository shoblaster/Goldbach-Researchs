// Parallel version of h2_cover_search.cpp (same model, same branching on the lowest uncovered position,
// same exact remaining-coverage bound), split into independent subtrees at depth SPLIT and run with OpenMP.
// The set of visited nodes is the same as in the sequential search, so for INFEASIBLE instances the total node
// count must equal the sequential count exactly; this is the validation used in EXP031.
// Build: g++ -std=c++17 -O3 -march=native -fopenmp h2_cover_search_par.cpp -o h2_cover_search_par
// Run:   ./h2_cover_search_par K L
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
typedef unsigned long long u64;
static const int NW = 4;
struct M { u64 w[NW]; };
static int K, L, NP, NWU;
static vector<int> P;
static vector<vector<M>> cls;
static const int SPLIT = 2;

struct St {
    int cnt[16]; vector<int> chosen[16]; long long nodes = 0;
    bool found = false; vector<pair<int,int>> witness;
};
static inline int pcm(const M& a) { int c = 0; for (int i = 0; i < NWU; i++) c += __builtin_popcountll(a.w[i]); return c; }
static inline int pcand(const M& a, const M& b) { int c = 0; for (int i = 0; i < NWU; i++) c += __builtin_popcountll(a.w[i] & b.w[i]); return c; }
static inline int lowest_uncovered(const M& u) { for (int i = 0; i < NWU; i++) if (u.w[i]) return i * 64 + __builtin_ctzll(u.w[i]) + 1; return -1; }

// returns true if a complete cover was found below this node
static bool dfs(St& s, const M& unc, int depth, vector<M>* frontier, vector<St>* fstates) {
    s.nodes++;
    int total = pcm(unc);
    if (total == 0) { s.witness.clear(); for (int i = 0; i < NP; i++) for (int r : s.chosen[i]) s.witness.push_back({P[i], r}); s.found = true; return true; }
    int bound = 0;
    for (int i = 0; i < NP; i++) {
        int t = 2 - s.cnt[i]; if (!t) continue;
        int b1 = 0, b2 = 0;
        for (int r = 1; r < P[i]; r++) {
            bool used = false; for (int u : s.chosen[i]) if (u == r) used = true;
            if (used) continue;
            int g = pcand(unc, cls[i][r]);
            if (g > b1) { b2 = b1; b1 = g; } else if (g > b2) b2 = g;
        }
        bound += (t == 2) ? b1 + b2 : b1;
    }
    if (bound < total) return false;
    if (frontier && depth == SPLIT) { frontier->push_back(unc); fstates->push_back(s); return false; }
    int q = lowest_uncovered(unc);
    for (int i = 0; i < NP; i++) {
        if (s.cnt[i] >= 2) continue;
        int r = q % P[i]; if (r == 0) continue;
        M nu; for (int j = 0; j < NWU; j++) nu.w[j] = unc.w[j] & ~cls[i][r].w[j];
        s.cnt[i]++; s.chosen[i].push_back(r);
        bool ok = dfs(s, nu, depth + 1, frontier, fstates);
        s.cnt[i]--; s.chosen[i].pop_back();
        if (ok) return true;
    }
    return false;
}
int main(int argc, char** argv) {
    K = atoi(argv[1]); L = atoi(argv[2]);
    int all[] = {2,3,5,7,11,13,17,19,23,29,31,37,41};
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

    St root; memset(root.cnt, 0, sizeof root.cnt);
    vector<M> frontier; vector<St> fstates;
    bool ok = dfs(root, unc, 0, &frontier, &fstates);   // nodes above the split level are counted here
    long long total = root.nodes;
    vector<pair<int,int>> wit = root.witness;
    int ntasks = frontier.size();
    fprintf(stderr, "k=%d L=%d prefix_nodes=%lld tasks=%d threads=%d\n", K, L, root.nodes, ntasks, omp_get_max_threads());
    volatile bool stop = ok;
    #pragma omp parallel for schedule(dynamic, 1) reduction(+:total)
    for (int t = 0; t < ntasks; t++) {
        if (stop) continue;
        St s = fstates[t]; s.nodes = 0;
        // frontier nodes were already counted (and bound-checked) in the prefix; re-expand their children only
        s.nodes = -1;                                   // compensate: dfs() counts the node itself again
        bool f = dfs(s, frontier[t], SPLIT + 1, nullptr, nullptr);
        total += s.nodes;
        if (f) {
            #pragma omp critical
            { if (!stop) { stop = true; wit = s.witness; ok = true; } }
        }
    }
    bool direct = false;
    if (ok) {
        map<int, set<int>> ch; for (auto& pr : wit) ch[pr.first].insert(pr.second);
        direct = true;
        for (int q = 1; q <= L && direct; q++) { bool c = false; for (auto& kv : ch) if (q % kv.first && kv.second.count(q % kv.first)) c = true; direct = c; }
    }
    printf("k %d L %d %s nodes %lld witness_direct_check %s\n", K, L, ok ? "FEASIBLE" : "INFEASIBLE", total, ok ? (direct ? "True" : "False") : "n/a");
    return 0;
}
