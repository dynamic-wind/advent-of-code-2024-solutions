#include <array>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::pair<int, int> find_start(const std::vector<std::string>& map) {
    const int rows = map.size();
    const int columns = map.at(0).size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (map.at(i).at(j) == '^') {
                return {i, j};
            }
        }
    }
    throw "Invalid input";
}

bool map_has_loop(const std::vector<std::string>& map, int i, int j) {
    const int rows = map.size();
    const int columns = map.at(0).size();
    static const std::array<std::pair<int, int>, 4> offsets = {{
        {-1, 0}, {0, 1}, {1, 0}, {0, -1},
    }};
    std::vector<std::vector<std::array<bool, 4>>> visited(
        rows, std::vector<std::array<bool, 4>>(columns)
    );
    int direction = 0;
    while (0 <= i && i < rows && 0 <= j && j < columns) {
        if (visited.at(i).at(j).at(direction)) {
            return true;
        }
        visited.at(i).at(j).at(direction) = true;
        auto [oi, oj] = offsets.at(direction);
        int ni = i + oi;
        int nj = j + oj;
        if (0 <= ni && ni < rows && 0 <= nj && nj < columns && map.at(ni).at(nj) == '#') {
            direction = (direction + 1) % 4;
        } else {
            i = ni;
            j = nj;
        }
    }
    return false;
}

int main() {
    std::vector<std::string> map;
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;) {
        map.push_back(std::move(line));
    }
    const auto [si, sj] = find_start(map);
    const int rows = map.size();
    const int columns = map.at(0).size();
    int result = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (map.at(i).at(j) == '.') {
                map.at(i).at(j) = '#';
                result += map_has_loop(map, si, sj);
                map.at(i).at(j) = '.';
            }
        }
    }
    std::cout << result << '\n';
}
