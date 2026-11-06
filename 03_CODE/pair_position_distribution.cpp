// EXP025: where in (0, n/2] do the smaller primes of Goldbach pairs sit?
// For 25000 pseudo-randomly chosen even n in [500000, 1000000] (mt19937, seed 1; a fixed step would bias the
// small-prime divisibility of n and was rejected after it inflated the ratio by about 25%), count observed pairs p <= q (p + q = n) in 50 bins of x = p/n
// (x in (0, 0.5]) and compare with the heuristic weight sum over odd p of 1/(ln p * ln(n-p)).
// Writes bins.csv to argv[1]. Build: g++ -std=c++17 -O2 -Wall -Wextra pair_position_distribution.cpp -o ppd
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <random>
int main(int argc, char** argv) {
    if (argc < 2) return 2;
    const int N = 1000000, LO = 500000, NS = 25000, B = 50;
    std::vector<char> comp(N + 1, 0); comp[0] = comp[1] = 1;
    for (int i = 2; (long long)i * i <= N; ++i) if (!comp[i]) for (int j = i * i; j <= N; j += i) comp[j] = 1;
    std::vector<double> lg(N + 1, 0.0);
    for (int i = 2; i <= N; ++i) lg[i] = std::log((double)i);
    std::vector<double> obs(B, 0.0), pred(B, 0.0);
    long long nn = 0;
    std::mt19937 rng(1);
    std::uniform_int_distribution<int> dist(LO / 2, N / 2);
    for (int it = 0; it < NS; ++it) {
        int n = 2 * dist(rng);
        ++nn;
        for (int p = 3; p <= n / 2; p += 2) {
            int b = (int)((double)p / n * 2.0 * B); if (b >= B) b = B - 1;
            pred[b] += 1.0 / (lg[p] * lg[n - p]);
            if (!comp[p] && !comp[n - p]) obs[b] += 1.0;
        }
    }
    std::string path = std::string(argv[1]) + "/bins.csv";
    FILE* f = std::fopen(path.c_str(), "w");
    std::fprintf(f, "bin_lo_x,bin_hi_x,observed,heuristic_weight,ratio\n");
    for (int b = 0; b < B; ++b)
        std::fprintf(f, "%.3f,%.3f,%.0f,%.3f,%.5f\n", 0.5 * b / B, 0.5 * (b + 1) / B, obs[b], pred[b], obs[b] / pred[b]);
    std::fclose(f);
    std::printf("n values=%lld bins=%d\n", nn, B);
    return 0;
}
