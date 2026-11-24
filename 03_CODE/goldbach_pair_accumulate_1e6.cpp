// EXP026: independent count of G(n), n even in 4..1e6, by direct accumulation over prime pairs.
// For every prime pair p <= q with p + q <= N, increment count[p+q]. No FFT, no per-n trial division.
// Writes goldbach_counts_1e6.csv (n,unordered_representation_count) to the directory in argv[1].
// Build: g++ -std=c++17 -O2 -Wall -Wextra goldbach_pair_accumulate_1e6.cpp -o pair_accumulate
// Run (from repository root): ./pair_accumulate 06_EXPERIMENTS/EXP026_INDEPENDENT_CROSSCHECK_TO_1E6
#include <cstdio>
#include <cstdint>
#include <vector>
#include <string>
int main(int argc, char** argv) {
    if (argc < 2) { std::fprintf(stderr, "usage: %s outdir\n", argv[0]); return 2; }
    const uint32_t N = 1000000;
    std::vector<char> comp(N + 1, 0);
    comp[0] = comp[1] = 1;
    for (uint32_t i = 2; (uint64_t)i * i <= N; ++i)
        if (!comp[i]) for (uint32_t j = i * i; j <= N; j += i) comp[j] = 1;
    std::vector<uint32_t> pr;
    for (uint32_t i = 2; i <= N; ++i) if (!comp[i]) pr.push_back(i);
    std::vector<uint32_t> cnt(N + 1, 0);
    for (size_t a = 0; a < pr.size(); ++a)
        for (size_t b = a; b < pr.size(); ++b) {
            uint32_t s = pr[a] + pr[b];
            if (s > N) break;
            ++cnt[s];
        }
    std::string path = std::string(argv[1]) + "/goldbach_counts_1e6.csv";
    FILE* f = std::fopen(path.c_str(), "w");
    if (!f) { std::perror("open"); return 1; }
    std::fprintf(f, "n,unordered_representation_count\n");
    uint32_t mn = 0xffffffffu, mx = 0, zeros = 0;
    for (uint32_t n = 4; n <= N; n += 2) {
        std::fprintf(f, "%u,%u\n", n, cnt[n]);
        if (cnt[n] < mn) mn = cnt[n];
        if (cnt[n] > mx) mx = cnt[n];
        if (cnt[n] == 0) ++zeros;
    }
    std::fclose(f);
    std::printf("primes=%zu rows=%u zeros=%u min=%u max=%u\n", pr.size(), (N - 4) / 2 + 1, zeros, mn, mx);
    return 0;
}
