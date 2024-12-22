#include <array>
#include <cstdint>
#include <execution>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

std::uint64_t next_secret_number(std::uint64_t n) {
    constexpr std::uint64_t m = 16777216;
    n = (n ^ (64*n)) % m;
    n = (n ^ (n/32)) % m;
    n = (n ^ (2048*n)) % m;
    return n;
}

int amount_bought_by_monkey(
    std::uint64_t n, const std::array<int, 4>& expected_changes
) {
    std::array<int, 4> changes;
    changes.fill(100);
    std::uint64_t current = n;
    int i = 0;
    for (; i < 2000 && changes != expected_changes; ++i) {
        std::uint64_t next = next_secret_number(current);
        for (int i = 0; i < 3; ++i) {
            changes.at(i) = changes.at(i + 1);
        }
        changes.back() = static_cast<int>(next%10) - static_cast<int>(current%10);
        current = next;
    }
    return i == 2000 ? 0 : current % 10;
}

int main() {
    std::vector<std::uint64_t> initial_prices;
    for (std::uint64_t n; std::cin >> n;) {
        initial_prices.push_back(n);
    }
    std::vector<std::pair<int, int>> ds;
    for (int i = -9; i <= 9; ++i) {
        for (int j = -9; j <= 9; ++j) {
            ds.emplace_back(i, j);
        }
    }
    int result = 0;
    for (int d1 = -9; d1 <= 9; ++d1) {
        std::cout << d1 << '\n';
        for (int d2 = -9; d2 <= 9; ++d2) {
            std::cout << d1 << ' ' << d2 << '\n';
            result = std::max(result, std::transform_reduce(
                std::execution::par,
                ds.begin(), ds.end(),
                0, [](int a, int b) { return std::max(a, b); },
                [&](const std::pair<int, int>& p) {
                    auto [d3, d4] = p;
                    int total_price = 0;
                    for (std::uint64_t p : initial_prices) {
                        total_price += amount_bought_by_monkey(p, {d1, d2, d3, d4});
                    }
                    return total_price;
                }
            ));
        }
    }
    std::cout << result << '\n';
}
