#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <utility>

std::int64_t number_of_digits(std::int64_t n) {
    std::int64_t result = 0;
    for (std::int64_t k = n; k > 0; k /= 10) {
        ++result;
    }
    return result;
}

std::pair<std::int64_t, std::int64_t> split_digits(std::int64_t n, std::int64_t d) {
    std::int64_t power_of_ten = 1;
    std::int64_t left = n;
    std::int64_t right = 0;
    for (std::int64_t i = 0; i < d; ++i) {
        right += (left%10)*power_of_ten;
        left /= 10;
        power_of_ten *= 10;
    }
    return {left, right};
}

std::int64_t count_stones_after_blinking(
    std::unordered_map<std::int64_t, std::int64_t>& cache,
    std::int64_t n, std::int64_t k
) {
    if (k == 0) {
        return 1;
    }
    auto it = cache.find(76*n + k);
    if (it != cache.end()) {
        return it->second;
    }
    std::int64_t result = 0;
    if (n == 0) {
        result = count_stones_after_blinking(cache, 1, k-1);
    } else {
        std::int64_t d = number_of_digits(n);
        if (d%2 == 0) {
            auto [left, right] = split_digits(n, d/2);
            result = count_stones_after_blinking(cache, left, k-1)
                   + count_stones_after_blinking(cache, right, k-1);
        } else {
            result = count_stones_after_blinking(cache, 2024*n, k-1);
        }
    }
    cache.emplace(76*n + k, result);
    return result;
}

int main() {
    std::int64_t result = 0;
    std::unordered_map<std::int64_t, std::int64_t> cache;
    for (std::int64_t e; std::cin >> e;) {
        result += count_stones_after_blinking(cache, e, 75);
    }
    std::cout << result << '\n';
}
