#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <array>
#include <utility>

int main() {
    std::vector<std::string> word_search;
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;) {
        word_search.push_back(std::move(line));
    }
    const int rows = word_search.size();
    const int columns = word_search.at(0).size();
    auto in_bounds = [&](int i, int j) {
        return 0 <= i && i < rows && 0 <= j && j < columns;
    };
    static const std::array<std::pair<int, int>, 8> offsets = {{
        {-1, -1}, {-1,  0}, {-1,  1},
        { 0, -1},           { 0,  1},
        { 1, -1}, { 1,  0}, { 1,  1},
    }};
    const std::string_view xmas = "XMAS";
    int result = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            for (const auto& [di, dj] : offsets) {
                int ni = i;
                int nj = j;
                std::size_t k = 0;
                while (k < xmas.size() && in_bounds(ni, nj) && word_search.at(ni).at(nj) == xmas.at(k)) {
                    ni += di;
                    nj += dj;
                    ++k;
                }
                result += (k == xmas.size());
            }
        }
    }
    std::cout << result << '\n';
}
