// Exact fixed-window minimum M_k (EXP015/EXP019/EXP024) by branch and bound, no MILP/CP solver.
// Model: window [1, p_k^2]; forbid 1 class mod 2 and 2 classes mod each odd prime up to p_k; M_k is the minimum number of
// surviving positions. Primes are processed in increasing order; the last prime p_k is resolved exactly (the two classes
// holding the most survivors give the minimum over all pairs).
// Pruning: at a node with survivor mask m after the primes below p_i, every remaining prime p_j (j >= i) removes at most the
// sum of its two largest class counts within m, so no leaf below can have fewer than
//     pc(m) - sum_{j >= i} top2_j(m)
// survivors. The subtree is cut when this lower bound is strictly greater than the best value found so far. Equal values
// are not cut, so the number of leaves attaining the minimum is counted exactly like in mk_enum_cpp.cpp (EXP024).
// Build: g++ -std=c++17 -O3 -march=native -fopenmp mk_enum_bb.cpp -o mk_enum_bb
// Run:   ./mk_enum_bb K     (K = 3..9; prints the same summary lines as mk_enum_cpp.cpp, plus node counts)
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
typedef unsigned long long u64;
static const int NW = 22;                      // windows up to 1408 bits (k <= 12: 37^2 = 1369)
struct Mask { u64 w[NW]; };
int K, W, NWU;
vector<int> P;
vector<vector<Mask>> cls;                      // cls[i][r]: positions n with n % P[i] == r
static atomic<int> shared_best(1 << 30);
static inline int pc(const Mask& m) { int c = 0; for (int i = 0; i < NWU; i++) c += __builtin_popcountll(m.w[i]); return c; }
static inline Mask andnot(const Mask& a, const Mask& b) { Mask r; for (int i = 0; i < NWU; i++) r.w[i] = a.w[i] & ~b.w[i]; return r; }
static inline int cnt(const Mask& a, const Mask& b) { int c = 0; for (int i = 0; i < NWU; i++) c += __builtin_popcountll(a.w[i] & b.w[i]); return c; }
struct Best { int val = 1 << 30; long long hits = 0; vector<int> sel; unsigned long long nodes = 0, pruned = 0; };

int main(int argc, char** argv) {
    if (argc < 2) { fprintf(stderr, "usage: %s K\n", argv[0]); return 2; }
    K = atoi(argv[1]);
    int all[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    if (K < 2 || K > 12) { fprintf(stderr, "K must be 2..12\n"); return 2; }
    for (int i = 0; i < K; i++) P.push_back(all[i]);
    W = P.back() * P.back(); NWU = (W + 63) / 64;
    cls.assign(K, {});
    for (int i = 0; i < K; i++) {
        cls[i].assign(P[i], Mask());
        for (int r = 0; r < P[i]; r++) for (int j = 0; j < NW; j++) cls[i][r].w[j] = 0;
        for (int n = 1; n <= W; n++) cls[i][n % P[i]].w[(n - 1) >> 6] |= 1ULL << ((n - 1) & 63);
    }
    vector<vector<pair<int,int>>> ch(K - 1);
    for (int i = 0; i < K - 1; i++) {
        if (P[i] == 2) { for (int r = 0; r < 2; r++) ch[i].push_back({r, -1}); }
        else for (int a = 0; a < P[i]; a++) for (int b = a + 1; b < P[i]; b++) ch[i].push_back({a, b});
    }
    Mask full; for (int j = 0; j < NW; j++) full.w[j] = 0;
    for (int n = 1; n <= W; n++) full.w[(n - 1) >> 6] |= 1ULL << ((n - 1) & 63);
    int split = min(K - 1, 4);
    vector<vector<int>> tasks{{}};
    for (int i = 0; i < split; i++) {
        vector<vector<int>> nt;
        for (auto& t : tasks) for (int c = 0; c < (int)ch[i].size(); c++) { auto u = t; u.push_back(c); nt.push_back(u); }
        tasks.swap(nt);
    }
    long long total = 1; for (int i = 0; i < K - 1; i++) total *= ch[i].size();
    fprintf(stderr, "k=%d window=%d prefix_selections=%lld tasks=%zu threads=%d\n", K, W, total, tasks.size(), omp_get_max_threads());
    Best global;
    #pragma omp parallel
    {
        Best local;
        #pragma omp for schedule(dynamic, 1)
        for (int ti = 0; ti < (int)tasks.size(); ti++) {
            vector<int> pick(K - 1, 0);
            Mask cur = full;
            for (int i = 0; i < split; i++) {
                auto pr = ch[i][tasks[ti][i]]; pick[i] = tasks[ti][i];
                cur = andnot(cur, cls[i][pr.first]);
                if (pr.second >= 0) cur = andnot(cur, cls[i][pr.second]);
            }
            function<void(int, const Mask&)> rec = [&](int i, const Mask& m) {
                local.nodes++;
                int tot = pc(m);
                // lower bound on survivors in any leaf below this node (primes i..K-1 still to be chosen)
                int bound = tot;
                for (int j = i; j < K; j++) {
                    int c1 = 0, c2 = 0;
                    for (int r = 0; r < P[j]; r++) { int c = cnt(m, cls[j][r]); if (c > c1) { c2 = c1; c1 = c; } else if (c > c2) c2 = c; }
                    bound -= c1 + c2;
                }
                int best = min(local.val, shared_best.load(memory_order_relaxed));
                if (bound > best) { local.pruned++; return; }
                if (i == K - 1) {
                    int c1 = -1, c2 = -1, bi = -1, bj = -1;
                    for (int r = 0; r < P[K - 1]; r++) {
                        int c = cnt(m, cls[K - 1][r]);
                        if (c > c1) { c2 = c1; bj = bi; c1 = c; bi = r; } else if (c > c2) { c2 = c; bj = r; }
                    }
                    int val = tot - c1 - c2;
                    if (val < local.val) { local.val = val; local.hits = 1; local.sel.clear();
                        for (int t = 0; t < K - 1; t++) { auto pr = ch[t][pick[t]]; local.sel.push_back(pr.first); if (pr.second >= 0) local.sel.push_back(pr.second); }
                        local.sel.push_back(bi); local.sel.push_back(bj);
                        int cur_sb = shared_best.load(); while (val < cur_sb && !shared_best.compare_exchange_weak(cur_sb, val)) {}
                    } else if (val == local.val) local.hits++;
                    return;
                }
                for (int c = 0; c < (int)ch[i].size(); c++) {
                    pick[i] = c; auto pr = ch[i][c];
                    Mask nm = andnot(m, cls[i][pr.first]);
                    if (pr.second >= 0) nm = andnot(nm, cls[i][pr.second]);
                    rec(i + 1, nm);
                }
            };
            rec(split, cur);
        }
        #pragma omp critical
        { global.nodes += local.nodes; global.pruned += local.pruned;
          if (local.val < global.val) { global.val = local.val; global.hits = local.hits; global.sel = local.sel; }
          else if (local.val == global.val) global.hits += local.hits; }
    }
    vector<int> sel = global.sel; int pos = 0; vector<vector<int>> chosen(K);
    for (int i = 0; i < K; i++) { int c = (P[i] == 2) ? 1 : 2; for (int t = 0; t < c; t++) chosen[i].push_back(sel[pos++]); }
    int direct = 0; vector<int> surv;
    for (int n = 1; n <= W; n++) { bool ok = true; for (int i = 0; i < K && ok; i++) for (int r : chosen[i]) if (n % P[i] == r) ok = false; if (ok) { direct++; if (surv.size() < 12) surv.push_back(n); } }
    printf("k %d window %d exact_minimum %d witness_direct_survivors %d direct_match %s\n", K, W, global.val, direct, direct == global.val ? "True" : "False");
    printf("prefix_witnesses_attaining_minimum_with_a_best_last_pair %lld\n", global.hits);
    printf("selected "); for (int i = 0; i < K; i++) { printf("("); for (size_t t = 0; t < chosen[i].size(); t++) printf("%d%s", chosen[i][t], t + 1 < chosen[i].size() ? "," : ""); printf(") "); } printf("\n");
    printf("survivors "); for (int s : surv) printf("%d ", s); printf("\n");
    printf("nodes_visited %llu nodes_pruned %llu\n", global.nodes, global.pruned);
    return 0;
}
