#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Independent EXP003 validator.  It does not reuse the baseline program's
// functions or pair file: it reads the saved count CSV, builds a byte sieve,
// and recomputes each count using the complementary-prime test.

std::vector<unsigned char> make_prime_table(int limit) {
    std::vector<unsigned char> prime(limit + 1, 1);
    prime[0] = prime[1] = 0;
    for (int p = 2; static_cast<int64_t>(p) * p <= limit; ++p)
        if (prime[p])
            for (int64_t k = static_cast<int64_t>(p) * p; k <= limit; k += p)
                prime[static_cast<size_t>(k)] = 0;
    return prime;
}

int main(int argc, char* argv[]) {
    const std::string input = argc > 1 ? argv[1] : "../04_RAW_DATA/EXP003/goldbach_counts.csv";
    std::ifstream file(input);
    if (!file) throw std::runtime_error("Cannot open count file: " + input);
    std::string line;
    std::getline(file, line);
    std::vector<std::pair<int, int>> saved;
    int maximum = 0;
    while (std::getline(file, line)) {
        std::istringstream row(line);
        std::string left, right;
        if (!std::getline(row, left, ',') || !std::getline(row, right))
            throw std::runtime_error("Malformed CSV row: " + line);
        const int n = std::stoi(left), claimed = std::stoi(right);
        if (n < 4 || n % 2 || claimed < 0) throw std::runtime_error("Invalid row: " + line);
        saved.push_back({n, claimed});
        if (n > maximum) maximum = n;
    }
    if (saved.empty()) throw std::runtime_error("No data rows found.");

    const auto prime = make_prime_table(maximum);
    int mismatches = 0;
    for (const auto& entry : saved) {
        const int n = entry.first;
        const int claimed = entry.second;
        int recomputed = 0;
        // This loop is deliberately over all possible p, not the baseline's prime list.
        for (int p = 2; p <= n / 2; ++p)
            if (prime[p] && prime[n - p]) ++recomputed;
        if (recomputed != claimed) {
            ++mismatches;
            std::cerr << "Mismatch at n=" << n << ": saved=" << claimed
                      << ", recomputed=" << recomputed << "\n";
        }
    }
    std::cout << "Validated rows=" << saved.size() << ", mismatches=" << mismatches << "\n";
    return mismatches == 0 ? 0 : 1;
}
