#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// EXP006 analysis: consume the frozen, n-then-p sorted EXP005 pair file.
// The first row seen for each n is therefore its smallest p under EXP005's
// unordered convention. The analyzer does not alter raw data.
int main(int argc, char* argv[]) {
    const std::string input = argc > 1 ? argv[1] : "../04_RAW_DATA/EXP005/goldbach_pairs.csv";
    const std::string output = argc > 2 ? argv[2] : "../05_PROCESSED_DATA/EXP006/minimal_prime_by_n.csv";
    std::ifstream in(input);
    if (!in) throw std::runtime_error("Cannot open pair file: " + input);
    std::string line;
    std::getline(in, line);
    std::ofstream out(output);
    if (!out) throw std::runtime_error("Cannot open analysis output: " + output);
    out << "n,minimal_p,complement_q\n";
    int current_n = -1, current_min_p = -1, current_q = -1;
    int rows = 0, represented = 0;
    int max_min_p = -1, max_n = -1, max_q = -1;
    while (std::getline(in, line)) {
        std::istringstream row(line);
        std::string a, b, c;
        if (!std::getline(row, a, ',') || !std::getline(row, b, ',') || !std::getline(row, c))
            throw std::runtime_error("Malformed pair row.");
        const int n = std::stoi(a), p = std::stoi(b), q = std::stoi(c);
        ++rows;
        if (n != current_n) {
            if (current_n >= 0) {
                out << current_n << ',' << current_min_p << ',' << current_q << "\n";
                ++represented;
                if (current_min_p > max_min_p) {
                    max_min_p = current_min_p;
                    max_n = current_n;
                    max_q = current_q;
                }
            }
            current_n = n;
            current_min_p = p;
            current_q = q;
        }
    }
    if (current_n >= 0) {
        out << current_n << ',' << current_min_p << ',' << current_q << "\n";
        ++represented;
        if (current_min_p > max_min_p) {
            max_min_p = current_min_p;
            max_n = current_n;
            max_q = current_q;
        }
    }
    std::cout << "pair_rows=" << rows << ", represented_n=" << represented
              << ", max_minimal_p=" << max_min_p << ", witness_n=" << max_n
              << ", witness_q=" << max_q << "\n";
}
