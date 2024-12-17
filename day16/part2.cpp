#include <iostream>
#include <array>
#include <string>
#include <queue>
#include <utility>

const std::array<std::pair<int, int>, 4> offsets = {{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1},
}};

std::pair<int, int> find_in_grid(
    const std::vector<std::string>& grid, int rows, int columns, char c
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

struct vertex {
    int i;
    int j;
    int o;

    vertex(int i, int j, int o) :
        i(i), j(j), o(o)
    {}
};

struct dijkstra_state {
    vertex v;
    vertex p;
    int cost;

    dijkstra_state(vertex v, vertex p, int cost) :
        v(v), p(p), cost(cost)
    {}

    bool operator<(const dijkstra_state& n) const {
        return cost > n.cost;
    }
};

std::vector<std::vector<std::array<std::vector<vertex>, 4>>> dijkstra(
    const std::vector<std::string>& grid, int rows, int columns, int si, int sj
) {
    std::priority_queue<dijkstra_state> pq;
    std::vector<std::vector<std::array<int, 4>>> d(
        rows, std::vector<std::array<int, 4>>(columns, {{-1, -1, -1, -1}})
    );
    d.at(si).at(sj).at(1) = 0;
    std::vector<std::vector<std::array<std::vector<vertex>, 4>>> parents(
        rows, std::vector<std::array<std::vector<vertex>, 4>>(columns, {{{}, {}, {}, {}}})
    );
    pq.emplace(vertex(si, sj, 1), vertex(-1, -1, -1), 0);
    while (pq.size() > 0) {
        auto [v, p, cost] = pq.top();
        auto [i, j, o] = v;
        auto [pi, pj, po] = p;
        pq.pop();
        if (d.at(i).at(j).at(o) == -1 || d.at(i).at(j).at(o) == cost) {
            d.at(i).at(j).at(o) = cost;
            if (pi != -1) {
                parents.at(i).at(j).at(o).emplace_back(vertex(pi, pj, po));
            }
            int ni = i + offsets.at(o).first;
            int nj = j + offsets.at(o).second;
            if (grid.at(ni).at(nj) != '#') {
                pq.emplace(vertex(ni, nj, o), vertex(i, j, o), cost + 1);
            }
            pq.emplace(vertex(i, j, (o+1)%4), vertex(i, j, o), cost + 1000);
            pq.emplace(vertex(i, j, (o+3)%4), vertex(i, j, o), cost + 1000);
        }
    }
    return parents;
}

void dfs(
    std::vector<std::vector<std::array<bool, 4>>>& v,
    const std::vector<std::vector<std::array<std::vector<vertex>, 4>>>& p,
    int i, int j, int o
) {
    if (!v.at(i).at(j).at(o)) {
        v.at(i).at(j).at(o) = true;
        for (auto& n : p.at(i).at(j).at(o)) {
            dfs(v, p, n.i, n.j, n.o);
        }
    }
}

int main() {
    std::vector<std::string> grid;
    for (std::string line; getline(std::cin, line), line.size() > 0;) {
        grid.push_back(std::move(line));
    }
    int rows = grid.size();
    int columns = grid.at(0).size();
    auto [si, sj] = find_in_grid(grid, rows, columns, 'S');
    auto [ei, ej] = find_in_grid(grid, rows, columns, 'E');
    auto p = dijkstra(grid, rows, columns, si, sj);
    std::vector<std::vector<std::array<bool, 4>>> v(rows, std::vector<std::array<bool, 4>>(columns, {false, false, false, false}));
    dfs(v, p, ei, ej, 0);
    dfs(v, p, ei, ej, 1);
    dfs(v, p, ei, ej, 2);
    dfs(v, p, ei, ej, 3);
    int result = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            bool b = false;
            for (int o = 0; o < 4; ++o) {
                b |= v.at(i).at(j).at(o);
            }
            result += b;
        }
    }
    std::cout << result << '\n';
}
