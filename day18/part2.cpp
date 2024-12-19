#include <array>
#include <iostream>
#include <utility>
#include <vector>

struct disjoint_set {
    std::vector<int> ds;

    disjoint_set(int n) : ds(n, -1) {}

    int find(int i) {
        if (ds.at(i) < 0) {
            return i;
        } else {
            int ri = find(ds.at(i));
            ds.at(i) = ri;
            return ri;
        }
    }

    bool join(int i, int j) {
        int ri = find(i);
        int rj = find(j);
        if (ri == rj) {
            return false;
        } else {
            if (-ds.at(ri) > -ds.at(rj)) {
                ds.at(ri) += ds.at(rj);
                ds.at(rj) = ri;
            } else {
                ds.at(rj) += ds.at(ri);
                ds.at(ri) = rj;
            }
            return true;
        }
    }

    int size_of_set(int i)  {
        return -ds.at(find(i));
    }
};

int steps_until_exit_is_blocked(
    const std::vector<std::pair<int, int>>& falling_bytes, int n
) {
    std::vector<std::string> grid(n, std::string(n, '.'));
    for (const auto& [i, j] : falling_bytes) {
        grid.at(i).at(j) = '#';
    }
    disjoint_set ds(n*n);
    const std::array<std::pair<int, int>, 4> offsets = {{
        {1, 0}, {0, 1}, {-1, 0}, {0, -1},
    }};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid.at(i).at(j) == '.')  {
                for (const auto& [io, jo] : offsets) {
                    int ni = i + io;
                    int nj = j + jo;
                    bool in_bounds = (0 <= ni && ni < n && 0 <= nj && nj < n);
                    if (in_bounds && grid.at(ni).at(nj) == '.') {
                        ds.join(i*n + j, ni*n + nj);
                    }
                }
            }
        }
    }
    int steps = falling_bytes.size()-1 ;
    for (; ds.find(0*n + 0) != ds.find(70*n + 70); --steps) {
        const auto& [i, j] = falling_bytes.at(steps);
        grid.at(i).at(j) = '.';
        for (const auto& [io, jo] : offsets) {
            int ni = i + io;
            int nj = j + jo;
            bool in_bounds = (0 <= ni && ni < n && 0 <= nj && nj < n);
            if (in_bounds && grid.at(ni).at(nj) == '.') {
                ds.join(i*n + j, ni*n + nj);
            }
        }
    }
    return steps + 1;
}

int main() {
    const int n = 71;
    std::vector<std::pair<int, int>> falling_bytes;
    for (int y, x; std::cin >> x, std::cin.ignore(1), std::cin >> y;) {
        falling_bytes.emplace_back(y, x);
    }
    const int steps = steps_until_exit_is_blocked(falling_bytes, n);
    const auto& [y, x] = falling_bytes.at(steps);
    std::cout << x << ',' << y << '\n';
}
