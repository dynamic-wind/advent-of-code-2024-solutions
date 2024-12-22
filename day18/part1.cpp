

#include <array>
#include <exception>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int steps_to_exit(const std::vector<std::string>& grid, int n) {
    const std::array<std::pair<int, int>, 4> offsets = {{
        {1, 0}, {0, 1}, {-1, 0}, {0, -1},
    }};
    std::vector<std::pair<int, int>> current = {
        {0, 0},
    };
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n));
    visited.at(0).at(0) = true;
    for (int a = 0;; ++a) {
        std::vector<std::pair<int, int>> next;
        for (const auto& [i, j] : current) {
            for (const auto& [io, jo] : offsets) {
                int ni = i + io;
                int nj = j + jo;
                bool in_bounds = (0 <= ni && ni < n && 0 <= nj && nj < n);
                bool not_a_wall = (in_bounds && grid.at(ni).at(nj) != '#');
                if (not_a_wall && !visited.at(ni).at(nj)) {
                    if (ni == n-1 && nj == n-1) {
                        return (a+1);
                    }
                    visited.at(ni).at(nj) = true;
                    next.emplace_back(ni, nj);
                }
            }
        }
        current = std::move(next);
    }
    std::terminate();
}

int main() {
    const int n = 71;
    std::vector<std::string> grid(n, std::string(n, '.'));
    for (int i = 0; i < 1024; ++i) {
        int x, y; std::cin >> x; std::cin.ignore(1); std::cin >> y;
        grid.at(y).at(x) = '#';
    }
    std::cout << steps_to_exit(grid, n) << '\n';
}
