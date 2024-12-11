#include <array>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

const std::array<std::pair<int, int>, 4> offsets = {{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1},
}};

int evaluate_trailhead_score(
    const std::vector<std::string>& map,
    std::vector<std::vector<int>>& cache,
    int i, int j, int rows, int columns
) {
    if (cache.at(i).at(j) != -1) {
        return cache.at(i).at(j);
    }
    if (map.at(i).at(j) == '9') {
        return 1;
    }
    int result = 0;
    for (const auto& [oi, oj] : offsets) {
        int ni = i + oi;
        int nj = j + oj;
        if (0 <= ni && ni < rows && 0 <= nj && nj < columns &&
            map.at(ni).at(nj) == map.at(i).at(j) + 1)
        {
            result += evaluate_trailhead_score(map, cache, ni, nj, rows, columns);
        }
    }
    cache.at(i).at(j) = result;
    return result;
}

int main() {
    std::vector<std::string> map;
    for (std::string line; std::getline(std::cin, line);) {
        map.push_back(std::move(line));
    }
    const int rows = map.size();
    const int columns = map.at(0).size();
    std::vector<std::vector<int>> cache(rows, std::vector<int>(columns, -1));
    int result = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (map.at(i).at(j) == '0') {
                result += evaluate_trailhead_score(map, cache, i, j, rows, columns);
            }
        }
    }
    std::cout << result << '\n';
}
