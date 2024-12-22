#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

std::vector<std::int64_t> parse_equation(const std::string& line) {
    std::istringstream iss(line);
    std::vector<std::int64_t> result;
    for (std::int64_t k; iss >> k; iss.ignore(1)) {
        result.push_back(k);
    }
    return result;
}

bool possible_equation(const std::vector<std::int64_t>& equation) {
    const std::int64_t target = equation.at(0);
    std::vector<std::int64_t> current = {equation.at(1)};
    for (std::size_t i = 2; i < equation.size(); ++i) {
        const std::int64_t k = equation.at(i);
        std::vector<std::int64_t> next;
        for (std::int64_t e : current) {
            const std::array<std::int64_t, 2> values = {{
                e + k,
                e * k,
            }};
            for (std::int64_t v : values) {
                if (v <= target) {
                    next.push_back(v);
                }
            }
        }
        current = std::move(next);
    }
    return std::find(current.begin(), current.end(), target) != current.end();
}

int main() {
    std::int64_t result = 0;
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;) {
        auto equation = parse_equation(line);
        if (possible_equation(equation)) {
            result += equation.at(0);
        }
    }
    std::cout << result << '\n';
}
