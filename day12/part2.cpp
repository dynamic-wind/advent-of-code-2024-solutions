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

int count_sides(
    const std::vector<std::string>& garden,
    std::vector<std::vector<int>>& visited,
    int i, int j, int rows, int columns
) {
    auto in_region = [&](int ti, int tj) {
        return 0 <= ti && ti < rows && 0 <= tj && tj < columns 
            && garden.at(ti).at(tj) == garden.at(i).at(j);
    };
    visited.at(i).at(j) = 2;
    int result = 0;
    for (int d1 = 0; d1 < 4; ++d1) {
        int d2 = (d1+1) % 4;
        int ni = i + offsets.at(d1).first;
        int nj = j + offsets.at(d1).second;
        int si = i + offsets.at(d2).first;
        int sj = j + offsets.at(d2).second;
        int ci = ni + offsets.at(d2).first;
        int cj = nj + offsets.at(d2).second;
        if (!in_region(ni, nj) && !in_region(si, sj)) {
            ++result;
        } else if (in_region(ni, nj) && in_region(si, sj) && !in_region(ci, cj)) {
            ++result;
        }
    }
    for (auto [oi, oj] : offsets) {
        int ni = i + oi;
        int nj = j + oj;
        if (in_region(ni, nj) && visited.at(ni).at(nj) != 2) {
            result += count_sides(garden, visited, ni, nj, rows, columns);
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
                int sides = count_sides(garden, visited, i, j, rows, columns);
                result += area * sides;
            }
        }
    }
    std::cout << result << '\n';
}
