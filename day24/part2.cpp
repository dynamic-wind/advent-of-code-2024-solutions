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

void evaluate_output(
    std::string wire,
    const std::unordered_map<std::string, connection>& connections,
    std::unordered_map<std::string, bool>& values
) {
    auto it = values.find(wire);
    if (it != values.end()) {
        std::cout << wire;
    } else {
        const auto& [left, op, right] = connections.at(wire);
        std::cout << '('; evaluate_output(left, connections, values);
        switch (op) {
            case boolean_operation::AND: {
                std::cout << '&';
            } break;
            case boolean_operation::XOR: {
                std::cout << '^';
            } break;
            case boolean_operation::OR: {
                std::cout << '|';
            } break;
            default: std::terminate();
        }
        evaluate_output(right, connections, values); std::cout << ')';
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
    for (int i = 0;; ++i) {
        std::ostringstream z;
        z << 'z' << std::setfill('0') << std::setw(2) << i;
        auto it = connections.find(z.str());
        if (it == connections.end()) {
            break;
        } else {
            std::cout << z.str() << ": ";
            evaluate_output(it->first, connections, values);
            std::cout << '\n';
        }
    }
    std::cout << "I did this one by hand using the output above\n";
    std::cout << "You just have to ensure each z__ looks like (...)^(x__^y__)\n";
}
