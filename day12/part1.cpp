#include <array>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

const std::array<std::pair<int, int>, 4> offsets = {{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1},
}};

int area_fill(
    const std::vector<std::string>& garden,
    std::vector<std::vector<int>>& visited,
    int i, int j, int rows, int columns
) {
    visited.at(i).at(j) = 1;
    int result = 1;
    for (auto [oi, oj] : offsets) {
        int ni = i + oi;
        int nj = j + oj;
        bool in_bounds = 0 <= ni && ni < rows && 0 <= nj && nj < columns;
        bool in_region = in_bounds && garden.at(ni).at(nj) == garden.at(i).at(j);
        if (in_region && visited.at(ni).at(nj) == 0) {
            result += area_fill(garden, visited, ni, nj, rows, columns);
        }
    }
    return result;
}

int perimeter_fill(
    const std::vector<std::string>& garden,
    std::vector<std::vector<int>>& visited,
    int i, int j, int rows, int columns
) {
    visited.at(i).at(j) = 2;
    int result = 0;
    for (auto [oi, oj] : offsets) {
        int ni = i + oi;
        int nj = j + oj;
        bool in_bounds = (0 <= ni && ni < rows && 0 <= nj && nj < columns);
        if (!in_bounds || garden.at(ni).at(nj) != garden.at(i).at(j)) {
            ++result;
        } else if (visited.at(ni).at(nj) != 2) {
            result += perimeter_fill(garden, visited, ni, nj, rows, columns);
        }
    }
    return result;
}

int main() {
    std::vector<std::string> garden;
    for (std::string line; getline(std::cin, line) && line.size() > 0;) {
        garden.push_back(std::move(line));
    }
    const int rows = garden.size();
    const int columns = garden.at(0).size();
    std::vector<std::vector<int>> visited(rows, std::vector<int>(columns));
    int result = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (visited.at(i).at(j) == 0) {
                int area = area_fill(garden, visited, i, j, rows, columns);
                int perimeter = perimeter_fill(garden, visited, i, j, rows, columns);
                result += area * perimeter;
            }
        }
    }
    std::cout << result << '\n';
}
