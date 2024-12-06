#include <iostream>
#include <string>
#include <unordered_set>
#include <sstream>
#include <vector>

struct OrderingRule {
    int before;
    int after;
    OrderingRule(int before, int after) : before(before), after(after) {}

    bool operator==(const OrderingRule& other) const {
        return std::pair(before, after) == std::pair(other.before, other.after);
    }
};

template <>
struct std::hash<OrderingRule> {
    size_t operator()(const OrderingRule& ordering_rule) const {
        return (ordering_rule.before<<16) + ordering_rule.after;
    }
};

std::vector<int> parse_updates(const std::string& string) {
    std::istringstream stream(string);
    std::vector<int> result;
    for (int update; stream >> update; stream.ignore(1)) {
        result.push_back(update);
    }
    return result;
}

bool updates_are_ordered(
    const std::vector<int>& updates, const std::unordered_set<OrderingRule>& ordering_rules
) {
    for (std::size_t i = 0; i < updates.size()-1; ++i) {
        for (std::size_t j = i+1; j < updates.size(); ++j) {
            if (ordering_rules.count(OrderingRule(updates.at(i), updates.at(j))) == 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::unordered_set<OrderingRule> ordering_rules;
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;) {
        auto bar = line.find('|');
        int before = std::stoi(line.substr(0, bar));
        int after = std::stoi(line.substr(bar+1));
        ordering_rules.emplace(before, after);
    }
    int result = 0;
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;) {
        auto updates = parse_updates(line);
        if (updates_are_ordered(updates, ordering_rules)) {
            result += updates.at((updates.size()-1) / 2);
        }
    }
    std::cout << result << '\n';
}
