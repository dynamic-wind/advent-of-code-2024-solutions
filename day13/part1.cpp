#include <algorithm>
#include <climits>
#include <ios>
#include <iostream>
#include <limits>
#include <optional>

struct machine_configuration {
    int ax; int ay;
    int bx; int by;
    int px; int py;
};

std::optional<machine_configuration> read_machine_configuration() {
    machine_configuration result;
    constexpr auto ignore_max = std::numeric_limits<std::streamsize>::max();
    std::cin.ignore(ignore_max, '+');
    std::cin >> result.ax;
    std::cin.ignore(ignore_max, '+');
    std::cin >> result.ay;
    std::cin.ignore(ignore_max, '+');
    std::cin >> result.bx;
    std::cin.ignore(ignore_max, '+');
    std::cin >> result.by;
    std::cin.ignore(ignore_max, '=');
    std::cin >> result.px;
    std::cin.ignore(ignore_max, '=');
    std::cin >> result.py;

    if (std::cin.fail()) {
        return std::nullopt;
    } else {
        return result;
    }
}

int main() {
    int result = 0;
    for (std::optional<machine_configuration> opt;
         opt = read_machine_configuration(), opt.has_value();)
    {
        const auto& [ax, ay, bx, by, px, py] = opt.value();
        int det = ax*by - bx*ay;
        if (det == 0) {
            int s;
            if (px*ay == py*ax) {
                if (ax != 0 && px%ax == 0) {
                    s = px/ax;
                } else if (ay != 0 && py%ay == 0) {
                    s = py/ay;
                } else {
                    s = 0;
                }
            } else {
                s = -1;
            }
            int t;
            if (px*by == py*bx) {
                if (bx != 0 && px%bx == 0) {
                    t = px/bx;
                } else if (by != 0 && py%by == 0) {
                    t = py/by;
                } else {
                    t = 0;
                }
            } else {
                t = -1;
            }
            int a = INT_MAX;
            if (s >= 0) {
                a = std::min(a, 3*s);
            }
            if (t >= 0) {
                a = std::min(a, t);
            }
            if (a != INT_MAX) {
                result += a;
            }
        } else {
            int s = px*by - bx*py;
            int t = ax*py - px*ay;
            if (s%det == 0 && t%det == 0) {
                s /= det;
                t /= det;
                if (s >= 0 && t >= 0) {
                    result += 3*s + t;
                }
            }
        }
    }
    std::cout << result << '\n';
}
