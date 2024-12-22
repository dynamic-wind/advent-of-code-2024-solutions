#include <algorithm>
#include <climits>
#include <cstdint>
#include <ios>
#include <iostream>
#include <limits>
#include <optional>

struct machine_configuration {
    std::int64_t ax, ay;
    std::int64_t bx, by;
    std::int64_t px, py;
};

std::optional<machine_configuration> read_machine_configuration() {
    machine_configuration result;
    constexpr auto ignore_max = std::numeric_limits<std::streamsize>::max();
    std::cin.ignore(ignore_max, '+'); std::cin >> result.ax;
    std::cin.ignore(ignore_max, '+'); std::cin >> result.ay;
    std::cin.ignore(ignore_max, '+'); std::cin >> result.bx;
    std::cin.ignore(ignore_max, '+'); std::cin >> result.by;
    std::cin.ignore(ignore_max, '='); std::cin >> result.px;
    std::cin.ignore(ignore_max, '='); std::cin >> result.py;

    result.px += INT64_C(10'000'000'000'000);
    result.py += INT64_C(10'000'000'000'000);

    if (std::cin.fail()) {
        return std::nullopt;
    } else {
        return result;
    }
}

int main() {
    std::int64_t result = 0;
    for (std::optional<machine_configuration> opt;
         opt = read_machine_configuration(), opt.has_value();)
    {
        const auto& [ax, ay, bx, by, px, py] = opt.value();
        std::int64_t det = ax*by - bx*ay;
        if (det == 0) {
            std::int64_t s;
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
            std::int64_t t;
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
            std::int64_t a = INT64_MAX;
            if (s >= 0) {
                a = std::min(a, 3*s);
            }
            if (t >= 0) {
                a = std::min(a, t);
            }
            if (a != INT64_MAX) {
                result += a;
            }
        } else {
            std::int64_t s = px*by - bx*py;
            std::int64_t t = ax*py - px*ay;
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
