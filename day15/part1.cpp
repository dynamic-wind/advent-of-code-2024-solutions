#include <array>
#include <exception>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::pair<int, int> find_robot(
    const std::vector<std::string>& grid, int rows, int columns
) {
    for (int i = 1; i < rows-1; ++i) {
        for (int j = 1; j < columns-1; ++j) {
            if (grid.at(i).at(j) == '@') {
                return {i, j};
            }
        }
    }
    std::terminate();
}

void run_robot(
    std::vector<std::string>& grid, int rows, int columns
) {
    static const std::array<std::pair<int, int>, 4> offsets = {{
        {1, 0}, {0, 1}, {-1, 0}, {0, -1},
    }};
    auto [bi, bj] = find_robot(grid, rows, columns);
    for (char d; std::cin >> d;) {
        int o;
        switch (d) {
            case 'v': o = 0; break;
            case '>': o = 1; break;
            case '^': o = 2; break;
            case '<': o = 3; break;
            default: std::terminate();
        }
        for (int k = 1;; ++k) {
            int ni = bi + k*offsets.at(o).first;
            int nj = bj + k*offsets.at(o).second;
            if (grid.at(ni).at(nj) == '#') {
                break;
            } else if (grid.at(ni).at(nj) == '.') {
                for (int l = k; l > 0; --l) {
                    int ci = bi + l*offsets.at(o).first;
                    int cj = bj + l*offsets.at(o).second;
                    int pi = bi + (l-1)*offsets.at(o).first;
                    int pj = bj + (l-1)*offsets.at(o).second;
                    grid.at(ci).at(cj) = grid.at(pi).at(pj);
                }
                grid.at(bi).at(bj) = '.';
                bi += offsets.at(o).first;
                bj += offsets.at(o).second;
                break;
            }
        }
    }
}

int main() {
    std::vector<std::string> grid;
    for (std::string line; getline(std::cin, line) && line.size() > 0;) {
        grid.push_back(std::move(line));
    }
    const int rows = grid.size();
    const int columns = grid.at(0).size();
    run_robot(grid, rows, columns);
    int result = 0;
    for (int i = 1; i < rows-1; ++i) {
        for (int j = 1; j < columns-1; ++j) {
            if (grid.at(i).at(j) == 'O') {
                result += 100*i + j;
            }
        }
    }
    std::cout << result << '\n';
}
