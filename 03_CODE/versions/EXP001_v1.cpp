#include <algorithm>
#include <chrono>
#include <cstdint>
#include <direct.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// EXP001 convention: an unordered representation {p, q} is counted once,
// p <= q, p = q is allowed, and 2 is included when applicable.

struct Result {
    int n;
    int count;
};

std::vector<bool> sieve(int limit) {
    std::vector<bool> prime(limit + 1, true);
    if (limit >= 0) prime[0] = false;
    if (limit >= 1) prime[1] = false;
    for (int p = 2; static_cast<int64_t>(p) * p <= limit; ++p) {
        if (prime[p]) {
            for (int64_t multiple = static_cast<int64_t>(p) * p; multiple <= limit; multiple += p)
                prime[static_cast<size_t>(multiple)] = false;
        }
    }
    return prime;
}

bool trial_is_prime(int n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (int d = 3; static_cast<int64_t>(d) * d <= n; d += 2)
        if (n % d == 0) return false;
    return true;
}

int independent_count(int n) {
    int count = 0;
    for (int p = 2; p <= n / 2; ++p)
        if (trial_is_prime(p) && trial_is_prime(n - p)) ++count;
    return count;
}

std::vector<Result> compute(int start, int end, const std::vector<bool>& prime,
                            const std::vector<int>& primes, std::ofstream& pairs) {
    std::vector<Result> results;
    for (int n = start; n <= end; n += 2) {
        int count = 0;
        for (int p : primes) {
            if (p > n / 2) break;
            const int q = n - p;
            if (prime[q]) {
                ++count;
                pairs << n << ',' << p << ',' << q << "\n";
            }
        }
        results.push_back({n, count});
    }
    return results;
}

void require(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error("Validation failure: " + message);
}

int main(int argc, char* argv[]) {
    const int start = argc > 1 ? std::stoi(argv[1]) : 4;
    const int end = argc > 2 ? std::stoi(argv[2]) : 1000;
    const std::string output = argc > 3 ? argv[3] : "../04_RAW_DATA/EXP001";
    if (start < 4 || start % 2 || end < start || end % 2)
        throw std::invalid_argument("Use an even range with 4 <= start <= end.");

    const auto began = std::chrono::steady_clock::now();
    const auto prime = sieve(end);
    std::vector<int> primes;
    for (int p = 2; p <= end; ++p) if (prime[p]) primes.push_back(p);

    // Fixed cases make the counting convention executable and explicit.
    require(independent_count(4) == 1, "G(4) must be 1 (2+2)");
    require(independent_count(10) == 2, "G(10) must be 2 (3+7, 5+5)");
    require(independent_count(28) == 2, "G(28) must be 2 (5+23, 11+17)");

    // The baseline targets the available MinGW environment, which lacks <filesystem>.
    // The experiment directory is created during repository setup; _mkdir is harmless if it exists.
    _mkdir(output.c_str());
    std::ofstream pairs(output + "/goldbach_pairs.csv");
    pairs << "n,p,q\n";
    const auto results = compute(start, end, prime, primes, pairs);
    pairs.close();

    // Independent trial-division recomputation for every value in this small baseline range.
    for (const auto& result : results)
        require(result.count == independent_count(result.n), "independent count mismatch at n=" + std::to_string(result.n));

    std::ofstream counts(output + "/goldbach_counts.csv");
    counts << "n,unordered_representation_count\n";
    int min_count = results.front().count, max_count = results.front().count;
    int zero_count = 0;
    for (const auto& result : results) {
        counts << result.n << ',' << result.count << "\n";
        min_count = std::min(min_count, result.count);
        max_count = std::max(max_count, result.count);
        if (result.count == 0) ++zero_count;
    }
    counts.close();

    const auto elapsed = std::chrono::duration<double>(std::chrono::steady_clock::now() - began).count();
    std::ofstream metadata(output + "/metadata.txt");
    metadata << "experiment_id=EXP001\n"
             << "program=goldbach_baseline.cpp\n"
             << "counting_convention=unordered pairs p<=q; p=q allowed; 2 included\n"
             << "range_start=" << start << "\nrange_end=" << end << "\n"
             << "numbers_tested=" << results.size() << "\n"
             << "min_G=" << min_count << "\nmax_G=" << max_count << "\nzero_G=" << zero_count << "\n"
             << "validation=fixed cases plus independent trial-division check for every n\n"
             << "elapsed_seconds=" << elapsed << "\n";

    std::cout << "EXP001 complete: " << results.size() << " even integers checked; "
              << "G min=" << min_count << ", max=" << max_count << ", zeros=" << zero_count
              << ", elapsed=" << elapsed << " seconds\n";
}
