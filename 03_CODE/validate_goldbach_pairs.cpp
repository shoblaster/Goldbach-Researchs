#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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
    const std::string pairs_path = argc > 1 ? argv[1] : "../04_RAW_DATA/EXP005/goldbach_pairs.csv";
    const std::string counts_path = argc > 2 ? argv[2] : "../04_RAW_DATA/EXP005/goldbach_counts.csv";
    std::ifstream counts_file(counts_path);
    if (!counts_file) throw std::runtime_error("Cannot open count file.");
    std::string line;
    std::getline(counts_file, line);
    std::vector<int> expected;
    int maximum = 0;
    while (std::getline(counts_file, line)) {
        const size_t comma = line.find(',');
        if (comma == std::string::npos) throw std::runtime_error("Malformed count row.");
        const int n = std::stoi(line.substr(0, comma));
        const int count = std::stoi(line.substr(comma + 1));
        if (n < 4 || n % 2 || count < 0) throw std::runtime_error("Invalid count row.");
        if (static_cast<int>(expected.size()) <= n) expected.resize(n + 1, -1);
        expected[n] = count;
        maximum = n;
    }
    const auto prime = make_prime_table(maximum);
    std::vector<int> observed(maximum + 1, 0);
    std::ifstream pairs_file(pairs_path);
    if (!pairs_file) throw std::runtime_error("Cannot open pair file.");
    std::getline(pairs_file, line);
    int64_t rows = 0, malformed = 0;
    while (std::getline(pairs_file, line)) {
        std::istringstream row(line);
        std::string a, b, c;
        if (!std::getline(row, a, ',') || !std::getline(row, b, ',') || !std::getline(row, c)) {
            ++malformed;
            continue;
        }
        const int n = std::stoi(a), p = std::stoi(b), q = std::stoi(c);
        if (n < 4 || n > maximum || n % 2 || p > q || p + q != n || !prime[p] || !prime[q])
            ++malformed;
        else
            ++observed[n];
        ++rows;
    }
    int count_mismatches = 0;
    for (int n = 4; n <= maximum; n += 2)
        if (expected[n] != observed[n]) ++count_mismatches;
    std::cout << "Validated pair rows=" << rows << ", malformed=" << malformed
              << ", count_mismatches=" << count_mismatches << "\n";
    return (malformed == 0 && count_mismatches == 0) ? 0 : 1;
}
