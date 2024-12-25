#include <cstdint>
#include <exception>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>

enum class boolean_operation {
    AND, XOR, OR,
};

struct connection {
    std::string left_operand;
    boolean_operation operation;
    std::string right_operand;
    connection(
        std::string left_operand,
        boolean_operation operation,
        std::string right_operand
    ) : 
        left_operand(left_operand),
        operation(operation),
        right_operand(right_operand)
    {}
};

bool evaluate_output(
    std::string wire,
    const std::unordered_map<std::string, connection>& connections,
    std::unordered_map<std::string, bool>& values
) {
    auto it = values.find(wire);
    if (it != values.end()) {
        return it->second;
    } else {
        const auto& [left, op, right] = connections.at(wire);
        bool left_value = evaluate_output(left, connections, values);
        bool right_value = evaluate_output(right, connections, values);
        bool value;
        switch (op) {
            case boolean_operation::AND: {
                value = left_value && right_value;
            } break;
            case boolean_operation::XOR: {
                value = left_value != right_value;
            } break;
            case boolean_operation::OR: {
                value = left_value || right_value;
            } break;
            default: std::terminate();
        }
        values.emplace(wire, value);
        return value;
    }
}

int main() {
    constexpr auto ignore_max = std::numeric_limits<std::streamsize>::max();
    std::unordered_map<std::string, bool> values;
    std::unordered_map<std::string, connection> connections;
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;) {
        std::string wire = line.substr(0, 3);
        bool value = line.back() == '1';
        values.emplace(wire, value);
    }
    for (std::string left, operand_name, right, wire;
         std::cin >> left >> operand_name >> right &&
         std::cin.ignore(ignore_max, '>') &&
         std::cin >> wire;
    ) {
        boolean_operation operation;
        if (operand_name == "AND") {
            operation = boolean_operation::AND;
        } else if (operand_name == "XOR") {
            operation = boolean_operation::XOR;
        } else if (operand_name == "OR") {
            operation = boolean_operation::OR;
        }
        connections.emplace(wire, connection(left, operation, right));
    }
    std::uint64_t result = 0;
    for (int i = 0;; ++i) {
        std::ostringstream z;
        z << 'z' << std::setfill('0') << std::setw(2) << i;
        auto it = connections.find(z.str());
        if (it == connections.end()) {
            break;
        } else {
            bool value = evaluate_output(it->first, connections, values);
            result |= static_cast<std::uint64_t>(value) << i;
        }
    }
    std::cout << result << '\n';
}
