// Independent exact computation of the fixed-window minimum M_k (EXP015/EXP019)
// WITHOUT any MILP/CP solver: enumerate every choice of forbidden residues for
// primes p_1..p_{k-1} (1 class mod 2, 2 classes mod each odd prime), keep the
// bit-mask of surviving positions in [1, p_k^2], and for the LAST prime p_k pick
// the best two classes exactly (the two classes with the most survivors).
// Choosing the two largest classes is exactly the minimum over all pairs of
// classes mod p_k, so the search covers every selection of the full model.
// Build: g++ -std=c++17 -O3 -march=native -fopenmp mk_enum_cpp.cpp -o mk_enum
// Run:   ./mk_enum K     (K = 3..8 intended; k=9 is not attempted here)
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
typedef unsigned long long u64;
static const int NW = 9;                       // supports windows up to 576 bits
struct Mask { u64 w[NW]; };

int K, W, NWU;
vector<int> P;
vector<vector<Mask>> cls;                      // cls[i][r]: positions n with n%P[i]==r

static inline int pc(const Mask& m) { int c = 0; for (int i = 0; i < NWU; i++) c += __builtin_popcountll(m.w[i]); return c; }
static inline Mask andnot(const Mask& a, const Mask& b) { Mask r; for (int i = 0; i < NWU; i++) r.w[i] = a.w[i] & ~b.w[i]; return r; }
static inline Mask orm(const Mask& a, const Mask& b) { Mask r; for (int i = 0; i < NWU; i++) r.w[i] = a.w[i] | b.w[i]; return r; }

struct Best { int val = 1 << 30; long long hits = 0; vector<int> sel; };   // sel: residues, 2 per prime (1 for p=2)

int main(int argc, char** argv) {
    K = atoi(argv[1]);
    int all[] = {2,3,5,7,11,13,17,19,23,29};
    for (int i = 0; i < K; i++) P.push_back(all[i]);
    W = P.back() * P.back(); NWU = (W + 63) / 64;
    cls.assign(K, {});
    for (int i = 0; i < K; i++) {
        cls[i].assign(P[i], Mask());
        for (int r = 0; r < P[i]; r++) for (int j = 0; j < NW; j++) cls[i][r].w[j] = 0;
        for (int n = 1; n <= W; n++) cls[i][n % P[i]].w[(n - 1) >> 6] |= 1ULL << ((n - 1) & 63);
    }
    // choices per prime (indices 0..K-2), as (r1,r2) with r2=-1 for p=2
    vector<vector<pair<int,int>>> ch(K - 1);
    for (int i = 0; i < K - 1; i++) {
        if (P[i] == 2) { for (int r = 0; r < 2; r++) ch[i].push_back({r, -1}); }
        else for (int a = 0; a < P[i]; a++) for (int b = a + 1; b < P[i]; b++) ch[i].push_back({a, b});
    }
    Mask full; for (int j = 0; j < NW; j++) full.w[j] = 0;
    for (int n = 1; n <= W; n++) full.w[(n - 1) >> 6] |= 1ULL << ((n - 1) & 63);

    // build prefix tasks through the first min(K-1,4) primes for parallelism
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
            vector<Mask> S(K); vector<int> pick(K - 1, 0);
            Mask cur = full;
            for (int i = 0; i < split; i++) {
                auto pr = ch[i][tasks[ti][i]]; pick[i] = tasks[ti][i];
                cur = andnot(cur, cls[i][pr.first]);
                if (pr.second >= 0) cur = andnot(cur, cls[i][pr.second]);
                S[i] = cur;
            }
            // iterative DFS over remaining primes split..K-2
            function<void(int, const Mask&)> rec = [&](int i, const Mask& m) {
                if (i == K - 1) {
                    int q = P[K - 1], tot = pc(m), c1 = -1, c2 = -1, bi = -1, bj = -1;
                    for (int r = 0; r < q; r++) {
                        int c = 0; for (int j = 0; j < NWU; j++) c += __builtin_popcountll(m.w[j] & cls[K - 1][r].w[j]);
                        if (c > c1) { c2 = c1; bj = bi; c1 = c; bi = r; } else if (c > c2) { c2 = c; bj = r; }
                    }
                    int val = tot - c1 - c2;
                    if (val < local.val) { local.val = val; local.hits = 1; local.sel.clear();
                        for (int t = 0; t < K - 1; t++) { auto pr = ch[t][pick[t]]; local.sel.push_back(pr.first); if (pr.second >= 0) local.sel.push_back(pr.second); }
                        local.sel.push_back(bi); local.sel.push_back(bj); }
                    else if (val == local.val) local.hits++;
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
        { if (local.val < global.val) { global.val = local.val; global.hits = local.hits; global.sel = local.sel; }
          else if (local.val == global.val) global.hits += local.hits; }
    }
    // direct recomputation of the witness from the definition
    vector<int> sel = global.sel; int pos = 0; vector<vector<int>> chosen(K);
    for (int i = 0; i < K; i++) { int cnt = (P[i] == 2) ? 1 : 2; for (int t = 0; t < cnt; t++) chosen[i].push_back(sel[pos++]); }
    int direct = 0; vector<int> surv;
    for (int n = 1; n <= W; n++) { bool ok = true; for (int i = 0; i < K && ok; i++) for (int r : chosen[i]) if (n % P[i] == r) ok = false; if (ok) { direct++; if (surv.size() < 12) surv.push_back(n); } }
    printf("k %d window %d exact_minimum %d witness_direct_survivors %d direct_match %s\n", K, W, global.val, direct, direct == global.val ? "True" : "False");
    printf("prefix_witnesses_attaining_minimum_with_a_best_last_pair %lld\n", global.hits);
    printf("selected "); for (int i = 0; i < K; i++) { printf("("); for (size_t t = 0; t < chosen[i].size(); t++) printf("%d%s", chosen[i][t], t + 1 < chosen[i].size() ? "," : ""); printf(") "); } printf("\n");
    printf("survivors "); for (int s : surv) printf("%d ", s); printf("\n");
    return 0;
}
