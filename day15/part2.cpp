#include <array>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

static const std::array<std::pair<int, int>, 4> offsets = {{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1},
}};

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

bool can_move(std::vector<std::string>& grid, int i, int j, int o) {
    int ni = i + offsets.at(o).first;
    int nj = j + offsets.at(o).second;
    if (grid.at(ni).at(nj) == '#') {
        return false;
    } else if (grid.at(ni).at(nj) == '.') {
        return true;
    } else if (o == 1 || o == 3) {
        return can_move(grid, ni, nj, o);
    } else if (grid.at(i).at(j) == ']' && grid.at(ni).at(nj) == ']') {
        return true;
    } else {
        return can_move(grid, ni, nj - (grid.at(ni).at(nj) == ']'), o)
            && can_move(grid, ni, nj + (grid.at(ni).at(nj) == '['), o);
    }
}

void do_move(std::vector<std::string>& grid, int i, int j, int o) {
    int ni = i + offsets.at(o).first;
    int nj = j + offsets.at(o).second;
    if (grid.at(ni).at(nj) == '.') {
        grid.at(ni).at(nj) = grid.at(i).at(j);
        grid.at(i).at(j) = '.';
    } else if (o == 1 || o == 3) {
        do_move(grid, ni, nj, o);
        grid.at(ni).at(nj) = grid.at(i).at(j);
        grid.at(i).at(j) = '.';
    } else {
        int l = nj - (grid.at(ni).at(nj) == ']');
        int r = nj + (grid.at(ni).at(nj) == '[');
        do_move(grid, ni, l, o);
        do_move(grid, ni, r, o);
        grid.at(ni).at(nj) = grid.at(i).at(j);
        grid.at(i).at(j) = '.';
    }
}

void run_robot(
    std::vector<std::string>& grid, int rows, int columns
) {
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
        if (can_move(grid, bi, bj, o)) {
            do_move(grid, bi, bj, o);
            bi += offsets.at(o).first;
            bj += offsets.at(o).second;
        }
    }
}

int main() {
    std::vector<std::string> grid;
    for (std::string line; getline(std::cin, line) && line.size() > 0;) {
        std::string expanded_line;
        for (char c : line) {
            switch (c) {
                case '.': expanded_line += ".."; break;
                case 'O': expanded_line += "[]"; break;
                case '#': expanded_line += "##"; break;
                case '@': expanded_line += "@."; break;
                default: std::terminate();
            }
        }
        grid.push_back(std::move(expanded_line));
    }
    const int rows = grid.size();
    const int columns = grid.at(0).size();
    run_robot(grid, rows, columns);
    int result = 0;
    for (int i = 1; i < rows-1; ++i) {
        for (int j = 2; j < columns-2; ++j) {
            if (grid.at(i).at(j) == '[') {
                result += 100*i + j;
            }
        }
    }
    std::cout << result << '\n';
}
