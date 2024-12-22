#include <array>
#include <exception>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

constexpr std::array<std::pair<int, int>, 4> offsets = {{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1},
}};

std::vector<std::vector<int>> bfs(
    const std::vector<std::string>& grid,
    int rows, int columns, 
    int si, int sj
) {
    std::vector<std::vector<int>> distances(
        rows, std::vector<int>(columns, -1)
    );
    distances.at(si).at(sj) = 0;
    std::vector<std::pair<int, int>> current = {
        {si, sj},
    };
    for (int distance = 1; current.size() > 0; ++distance) {
        std::vector<std::pair<int, int>> next;
        for (const auto& [i, j] : current) {
            for (const auto& [io, jo] : offsets) {
                int ni = i + io;
                int nj = j + jo;
                bool in_bounds = (0 <= ni && ni < rows && 0 <= nj && nj < columns);
                bool not_a_wall = (in_bounds && grid.at(ni).at(nj) != '#');
                if (not_a_wall && distances.at(ni).at(nj) == -1) {
                    distances.at(ni).at(nj) = distance;
                    next.emplace_back(ni, nj);
                }
            }
        }
        current = std::move(next);
    }
    return distances;
}

std::pair<int, int> find_position(
    const std::vector<std::string>& grid,
    int rows, int columns, char c
) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (grid.at(i).at(j) == c) {
                return {i, j};
            }
        }
    }
    std::terminate();
}

int main() {
    std::vector<std::string> grid;
    for (std::string line; getline(std::cin, line) && line.size() > 0;) {
        grid.push_back(std::move(line));
    }
    const int rows = grid.size();
    const int columns = grid.at(0).size();
    const auto [si, sj] = find_position(grid, rows, columns, 'S');
    const auto [ei, ej] = find_position(grid, rows, columns, 'E');
    const auto distances_from_start = bfs(grid, rows, columns, si, sj);
    const auto distances_from_end = bfs(grid, rows, columns, ei, ej);
    int result = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (grid.at(i).at(j) != '#') {
                for (const auto& [io, jo] : offsets) {
                    int ni = i + 2*io;
                    int nj = j + 2*jo;
                    bool in_bounds = (0 <= ni && ni < rows && 0 <= nj && nj < columns);
                    if (in_bounds && grid.at(ni).at(nj) != '#') {
                        int t = distances_from_start.at(i).at(j) + 2 + distances_from_end.at(ni).at(nj);
                        result += (distances_from_start.at(ei).at(ej) - t >= 100);
                    }
                }
            }
        }
    }
    std::cout << result << '\n';
}
