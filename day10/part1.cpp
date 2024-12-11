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
    std::vector<std::vector<bool>>& visited,
    int i, int j, int rows, int columns
) {
    if (visited.at(i).at(j)) {
        return 0;
    }
    visited.at(i).at(j) = true;
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
            result += evaluate_trailhead_score(map, visited, ni, nj, rows, columns);
        }
    }
    return result;
}

void unset_visited_positions(
    std::vector<std::vector<bool>>& visited,
    int i, int j, int rows, int columns
) {
    if (visited.at(i).at(j)) {
        visited.at(i).at(j) = false;
        for (const auto& [oi, oj] : offsets) {
            int ni = i + oi;
            int nj = j + oj;
            if (0 <= ni && ni < rows && 0 <= nj && nj < columns) {
                unset_visited_positions(visited, ni, nj, rows, columns);
            }
        }
    }
}

int main() {
    std::vector<std::string> map;
    for (std::string line; std::getline(std::cin, line);) {
        map.push_back(std::move(line));
    }
    const int rows = map.size();
    const int columns = map.at(0).size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(columns));
    int result = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (map.at(i).at(j) == '0') {
                result += evaluate_trailhead_score(map, visited, i, j, rows, columns);
                unset_visited_positions(visited, i, j, rows, columns);
            }
        }
    }
    std::cout << result << '\n';
}
