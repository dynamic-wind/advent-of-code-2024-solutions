#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> read_schematic() {
    std::vector<std::string> result;
    for (std::string line; getline(std::cin, line) && line.size() > 0;) {
        result.push_back(std::move(line));
    }
    return result;
}

struct schematic {
    bool is_a_lock;
    std::vector<int> heights;
};

schematic parse_schematic(const std::vector<std::string>& lines) {
    const int rows = lines.size();
    const int columns = lines.at(0).size();
    schematic result;
    if (lines.at(0).at(0) == '#') {
        result.is_a_lock = true;
        for (int j = 0; j < columns; ++j) {
            int i = 0;
            while (lines.at(i).at(j) == '#') {
                ++i;
            }
            result.heights.push_back(i-1);
        }
    } else {
        result.is_a_lock = false;
        for (int j = 0; j < columns; ++j) {
            int i = 0;
            while (lines.at(rows-1-i).at(j) == '#') {
                ++i;
            }
            result.heights.push_back(i-1);
        }
    }
    return result;
}

int main() {
    std::vector<std::vector<int>> locks, keys;
    for (std::vector<std::string> lines; lines = read_schematic(), lines.size() > 0;) {
        auto s = parse_schematic(lines);
        if (s.is_a_lock) {
            locks.push_back(std::move(s.heights));
        } else {
            keys.push_back(std::move(s.heights));
        }
    }
    int result = 0;
    for (const auto& lock : locks) {
        for (const auto& key : keys) {
            bool b = true;
            for (int j = 0; j < 5; ++j) {
                if (lock.at(j) + key.at(j) > 5) {
                    b = false;
                    break;
                }
            }
            result += b;
        }
    }
    std::cout << result << '\n';
}
