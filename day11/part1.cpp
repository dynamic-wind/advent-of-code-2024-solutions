#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

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

std::vector<std::int64_t> line_after_blinking(const std::vector<std::int64_t>& line) {
    std::vector<std::int64_t> result;
    for (std::int64_t e : line) {
        if (e == 0) {
            result.push_back(1);
        } else {
            std::int64_t d = number_of_digits(e);
            if (d%2 == 0) {
                auto [left, right] = split_digits(e, d/2);
                result.push_back(left);
                result.push_back(right);
            } else {
                result.push_back(2024*e);
            }
        }
    }
    return result;
}

int main() {
    std::vector<std::int64_t> line;
    for (std::int64_t e; std::cin >> e;) {
        line.push_back(e);
    }
    for (std::int64_t i = 0; i < 25; ++i) {
        line = line_after_blinking(line);
    }
    std::cout << line.size() << '\n';
}
