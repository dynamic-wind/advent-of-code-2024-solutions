#include <array>
#include <cstdint>
#include <exception>
#include <ios>
#include <iostream>
#include <limits>
#include <vector>

std::vector<std::int64_t> run_program(
    const std::array<std::int64_t, 3>& initial_registers,
    const std::vector<std::int64_t>& program
) {
    std::vector<std::int64_t> result;
    std::array<std::int64_t, 3> registers = initial_registers;
    auto combo_op = [&](std::int64_t k) {
        if (0 <= k && k <= 3) {
            return k;
        } else if (4 <= k && k <= 6) {
            return registers.at(k-4);
        } else {
            std::terminate();
        }
    };
    const std::int64_t int64_t_bits = 8*sizeof(std::int64_t);
    int ip = 0;
    const std::int64_t n = program.size();
    while (ip+1 < n) {
        const std::int64_t op = program.at(ip+1);
        switch (program.at(ip)) {
            case 0: {
                registers.at(0) >>= std::min(combo_op(op), int64_t_bits-1);
            } break;
            case 1: {
                registers.at(1) ^= op;
            } break;
            case 2: {
                registers.at(1) = combo_op(op)%8;
            } break;
            case 3: {
                if (registers.at(0) != 0) {
                    ip = op - 2;
                }
            } break;
            case 4: {
                registers.at(1) ^= registers.at(2);
            } break;
            case 5: {
                result.push_back(combo_op(op) % 8);
            } break;
            case 6: {
                registers.at(1) = registers.at(0) >> std::min(combo_op(op), int64_t_bits-1);
            } break;
            case 7: {
                registers.at(2) = registers.at(0) >> std::min(combo_op(op), int64_t_bits-1);
            } break;
            default: std::terminate();
        }
        ip += 2;
    }
    return result;
}

std::int64_t find_quine(
    const std::array<int64_t, 3>& initial_registers,
    const std::vector<std::int64_t>& program,
    std::int64_t a0, std::int64_t l
) {
    if (l == -1) {
        return a0;
    }
    std::int64_t result = INT64_MAX;
    for (std::int64_t k = 0; k < 8; ++k) {
        std::int64_t a = a0 | (k<<(3*l));
        auto registers = initial_registers;
        registers.at(0) = a;
        auto output = run_program(registers, program);
        if (output.size() == program.size() && output.at(l) == program.at(l)) {
            result = std::min(result, find_quine(initial_registers, program, a, l-1));
        }
    }
    return result;
}

int main() {
    constexpr auto ignore_max = std::numeric_limits<std::streamsize>::max();
    std::array<std::int64_t, 3> registers = {};
    std::cin.ignore(ignore_max, ':'); std::cin >> registers.at(0);
    std::cin.ignore(ignore_max, ':'); std::cin >> registers.at(1);
    std::cin.ignore(ignore_max, ':'); std::cin >> registers.at(2);
    std::cin.ignore(ignore_max, ':');
    std::vector<std::int64_t> program;
    for (std::int64_t k; std::cin >> k; std::cin.ignore(1)) {
        program.push_back(k);
    }
    std::cout << find_quine(registers, program, 0, program.size()-1) << '\n';
}
