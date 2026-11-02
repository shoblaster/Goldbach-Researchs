// Independent C++17 distribution audit for the k=6 Sieve II model.
// This intentionally does not import or mirror the Python implementation.

#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

using Mask = std::array<std::uint64_t, 3>; // 192 bits; only first 169 used

struct Choice {
    int a;
    int b;
};

std::vector<Choice> make_choices(int p, bool single) {
    std::vector<Choice> out;
    if (single) {
        for (int a = 0; a < p; ++a) out.push_back({a, -1});
    } else {
        for (int a = 0; a < p; ++a)
            for (int b = a + 1; b < p; ++b)
                out.push_back({a, b});
    }
    return out;
}

Mask make_mask(int p, Choice c) {
    Mask mask{0, 0, 0};
    for (int n = 1; n <= 169; ++n) {
        int r = n % p;
        bool allowed = (r != c.a) && (c.b < 0 || r != c.b);
        if (allowed) mask[(n - 1) / 64] |= std::uint64_t{1} << ((n - 1) % 64);
    }
    return mask;
}

Mask intersect(Mask x, const Mask& y) {
    for (int i = 0; i < 3; ++i) x[i] &= y[i];
    return x;
}

int popcount(const Mask& mask) {
    return __builtin_popcountll(mask[0]) + __builtin_popcountll(mask[1])
         + __builtin_popcountll(mask[2]);
}

int main() {
    const std::array<int, 6> primes{2, 3, 5, 7, 11, 13};
    std::array<std::vector<Choice>, 6> choices;
    std::array<std::vector<Mask>, 6> masks;
    for (int j = 0; j < 6; ++j) {
        choices[j] = make_choices(primes[j], j == 0);
        for (const auto& c : choices[j]) masks[j].push_back(make_mask(primes[j], c));
    }

    std::array<std::uint64_t, 170> histogram{};
    std::uint64_t total = 0;
    std::uint64_t sum = 0;
    int minimum = 170;
    int maximum = 0;

    auto visit = [&](auto&& self, int depth, Mask current) -> void {
        if (depth == 6) {
            int count = popcount(current);
            ++histogram[count];
            ++total;
            sum += static_cast<std::uint64_t>(count);
            if (count < minimum) minimum = count;
            if (count > maximum) maximum = count;
            return;
        }
        for (const Mask& next : masks[depth]) self(self, depth + 1, intersect(current, next));
    };

    Mask all{~std::uint64_t{0}, ~std::uint64_t{0}, ~std::uint64_t{0}};
    visit(visit, 0, all);

    std::cout << "tested_choices " << total << "\n";
    std::cout << "minimum " << minimum << " maximum " << maximum << "\n";
    std::cout << "sum_counts " << sum << "\n";
    std::cout << "histogram=";
    bool first = true;
    for (int c = 0; c <= maximum; ++c) {
        if (histogram[c] == 0) continue;
        if (!first) std::cout << ',';
        first = false;
        std::cout << c << ':' << histogram[c];
    }
    std::cout << "\n";
}
