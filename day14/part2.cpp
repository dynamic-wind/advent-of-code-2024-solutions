#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <optional>
#include <vector>

constexpr auto ignore_max = std::numeric_limits<std::streamsize>::max();

int mod(int a, int b) {
    int r = a % b;
    return r >= 0 ? r : r + b;
}

struct robot {
    int px; int py;
    int vx; int vy;
};

std::optional<robot> read_robot(std::istream& is) {
    robot result;
    is.ignore(ignore_max, '='); is >> result.px;
    is.ignore(ignore_max, ','); is >> result.py;
    is.ignore(ignore_max, '='); is >> result.vx;
    is.ignore(ignore_max, ','); is >> result.vy;
    if (is.fail()) {
        return std::nullopt;
    } else {
        return result;
    }
}

void show_map(const std::vector<std::vector<int>>& map) {
    for (int i = 0; i < 101; ++i) {
        std::cout << "==";
    }
    std::cout << '\n';
    for (int i = 0; i < 103; ++i) {
        for (int j = 0; j < 101; ++j) {
            if (map.at(i).at(j) > 0) {
                std::cout << "  ";
            } else {
                std::cout << "# ";
            }
        }
        std::cout << '\n';
    }
    for (int i = 0; i < 101; ++i) {
        std::cout << "==";
    }
    std::cout << '\n';
}

void update_robots(std::vector<robot>& robots, std::vector<std::vector<int>>& map) {
    for (auto& r : robots) {
        --map.at(r.py).at(r.px);
        r.px = mod(r.px + r.vx, 101);
        r.py = mod(r.py + r.vy, 103);
        ++map.at(r.py).at(r.px);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <INPUT_FILE>\n";
        return 0;
    }
    std::vector<std::vector<int>> map(103, std::vector<int>(101));
    std::vector<robot> robots;
    std::ifstream in(argv[1]);
    for (std::optional<robot> opt; opt = read_robot(in), opt.has_value();) {
        const auto& robot = opt.value();
        robots.push_back(robot);
        ++map.at(robot.py).at(robot.px);
    }
    std::cout << "Just make you terminal's text small and hold enter for a while ;)\n";
    std::cin.ignore(ignore_max, '\n');
    for (int k = 0;; ++k) {
        std::cout << '\n' << k << '\n';
        show_map(map);
        update_robots(robots, map);
        std::cout.flush();
        std::cin.ignore(ignore_max, '\n');
    }
}
