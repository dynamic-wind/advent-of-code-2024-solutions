#include <ios>
#include <iostream>
#include <limits>
#include <optional>

int mod(int a, int b) {
    int r = a % b;
    return r >= 0 ? r : r + b;
}

struct robot {
    int px; int py;
    int vx; int vy;
};

std::optional<robot> read_robot() {
    constexpr auto ignore_max = std::numeric_limits<std::streamsize>::max();
    robot result;
    std::cin.ignore(ignore_max, '='); std::cin >> result.px;
    std::cin.ignore(ignore_max, ','); std::cin >> result.py;
    std::cin.ignore(ignore_max, '='); std::cin >> result.vx;
    std::cin.ignore(ignore_max, ','); std::cin >> result.vy;
    if (std::cin.fail()) {
        return std::nullopt;
    } else {
        return result;
    }
}

int main() {
    int upper_left = 0;
    int upper_right = 0;
    int lower_left = 0;
    int lower_right = 0;
    for (std::optional<robot> opt; opt = read_robot(), opt.has_value();) {
        const auto& robot = opt.value();
        int fx = mod(robot.px + 100*robot.vx, 101);
        int fy = mod(robot.py + 100*robot.vy, 103);
        if (fx <= 49) {
            if (fy <= 50) {
                ++upper_left;
            } else if (52 <= fy) {
                ++lower_left;
            }
        } else if (51 <= fx) {
            if (fy <= 50) {
                ++upper_right;
            } else if (52 <= fy) {
                ++lower_right;
            }
        }
    }
    std::cout << (upper_left*upper_right*lower_left*lower_right) << '\n';
}
