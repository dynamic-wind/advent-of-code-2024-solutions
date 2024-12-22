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

int main() {
    std::vector<std::string> map;
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;) {
        map.push_back(std::move(line));
    }
    const int rows = map.size();
    const int columns = map.at(0).size();
    static const std::array<std::pair<int, int>, 4> offsets = {{
        {-1, 0}, {0, 1}, {1, 0}, {0, -1},
    }};
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(columns));
    int result = 0;
    int direction = 0;
    auto [i, j] = find_start(map);
    while (0 <= i && i < rows && 0 <= j && j < columns) {
        if (!visited.at(i).at(j)) {
            ++result;
            visited.at(i).at(j) = true;
        }
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
    std::cout << result << '\n';
}
