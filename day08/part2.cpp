#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

void generate_antinodes(
    std::vector<std::vector<bool>>& antinodes, const std::pair<int, int>& p, const std::pair<int, int>& q
) {
    const int rows = antinodes.size();
    const int columns = antinodes.at(0).size();
    int d = std::gcd(std::abs(p.first - q.first), std::abs(p.second - q.second));
    int ai = p.first;
    int aj = p.second;
    while (0 <= ai && ai < rows && 0 <= aj && aj < columns) {
        antinodes.at(ai).at(aj) = true;
        ai += (p.first - q.first) / d;
        aj += (p.second - q.second) / d;
    }
}

int main() {
    std::vector<std::string> map;
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;) {
        map.push_back(std::move(line));
    }
    const int rows = map.size();
    const int columns = map.at(0).size();
    std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (map.at(i).at(j) != '.') {
                antennas[map.at(i).at(j)].emplace_back(i, j);
            }
        }
    }
    std::vector<std::vector<bool>> antinodes(rows, std::vector<bool>(columns));
    for (const auto& [c, a] : antennas) {
        const int n = a.size();
        for (int i = 0; i < n-1; ++i) {
            const auto& p = a.at(i);
            for (int j = i+1; j < n; ++j) {
                const auto& q = a.at(j);
                generate_antinodes(antinodes, p, q);
                generate_antinodes(antinodes, q, p);
            }
        }
    }
    int result = 0;
    for (const auto& row : antinodes) {
        result += std::accumulate(row.begin(), row.end(), 0);
    }
    std::cout << result << '\n';
}
