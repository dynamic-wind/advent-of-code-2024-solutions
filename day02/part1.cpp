#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

bool is_safe_report(const std::vector<int>& report) {
    bool increasing = true;
    bool decreasing = true;
    bool values_in_range = true;
    for (std::size_t i = 1; i < report.size(); ++i) {
        increasing &= (report.at(i) > report.at(i-1));
        decreasing &= (report.at(i) < report.at(i-1));
        int difference = std::abs(report.at(i) - report.at(i-1));
        values_in_range &= (1 <= difference && difference <= 3);
    }
    return (increasing || decreasing) && values_in_range;
}

int main() {
    int result = 0;
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;) {
        std::istringstream iss(line);
        std::vector<int> report;
        for (int value; iss >> value;) {
            report.push_back(value);
        }
        result += is_safe_report(report);
    }
    std::cout << result << '\n';
}
