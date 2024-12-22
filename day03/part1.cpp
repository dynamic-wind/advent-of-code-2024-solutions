#include <iostream>
#include <string>
#include <regex>

int main() {
    const std::regex mul_regex("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");
    int result = 0;
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;) {
        std::sregex_iterator matches_begin(
            line.begin(), line.end(), mul_regex
        );
        std::sregex_iterator matches_end;
        for (auto it = matches_begin; it != matches_end; ++it) {
            result += std::stoi((*it)[1]) * std::stoi((*it)[2]);
        }
    }
    std::cout << result << '\n';
}
