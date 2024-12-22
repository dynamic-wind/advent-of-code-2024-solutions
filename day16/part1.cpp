#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <array>

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
    int d;
    vertex(int i, int j, int d) :  
        i(i), j(j), d(d) 
    {}
};

struct dijkstra_state {
    vertex v;
    int cost;

    dijkstra_state(vertex v, int cost) :
        v(v), cost(cost)
    {}

    bool operator<(const dijkstra_state& o) const {
        return cost > o.cost;
    }
};

int dijkstra(
    const std::vector<std::string>& grid, int rows, int columns,
    int si, int sj, int ei, int ej
) {
    std::priority_queue<dijkstra_state> pq;
    std::vector<std::vector<std::array<int, 4>>> d(
        rows, std::vector<std::array<int, 4>>(columns, {{-1, -1, -1, -1}})
    );
    pq.emplace(vertex(si, sj, 1), 0);
    while (pq.size() > 0) {
        auto [v, cost] = pq.top();
        auto [i, j, o] = v;
        pq.pop();
        if (i == ei && j == ej) {
            return cost;
        }
        if (d.at(i).at(j).at(o) == -1) {
            d.at(i).at(j).at(o) = cost;
            int ni = i + offsets.at(o).first;
            int nj = j + offsets.at(o).second;
            if (grid.at(ni).at(nj) != '#') {
                pq.emplace(vertex(ni, nj, o), cost + 1);
            }
            pq.emplace(vertex(i, j, (o+1) % 4), cost + 1000);
            pq.emplace(vertex(i, j, (o+3) % 4), cost + 1000);
        }
    }
    std::terminate();
}

int main() {
    std::vector<std::string> grid;
    for (std::string line; getline(std::cin, line), line.size() > 0;) {
        grid.push_back(std::move(line));
    }
    const int rows = grid.size();
    const int columns = grid.at(0).size();
    auto [si, sj] = find_in_grid(grid, rows, columns, 'S');
    auto [ei, ej] = find_in_grid(grid, rows, columns, 'E');
    std::cout << dijkstra(grid, rows, columns, si, sj, ei, ej) << '\n';
}
