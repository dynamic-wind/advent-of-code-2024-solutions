#include <iostream>
#include <string>
#include <regex>

int main() {
    const std::regex mul_regex(
        "(mul\\(([0-9]{1,3}),([0-9]{1,3})\\))|"
        "(do\\(\\))|"
        "(don't\\(\\))"
    );
    bool do_mul = true;
    int result = 0;
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;) {
        std::sregex_iterator matches_begin(
            line.begin(), line.end(), mul_regex
        );
        std::sregex_iterator matches_end;
        for (auto it = matches_begin; it != matches_end; ++it) {
            if (it->str() == "do()") {
                do_mul = true;
            } else if (it->str() == "don't()") {
                do_mul = false;
            } else if (do_mul) {
                result += std::stoi((*it)[2]) * std::stoi((*it)[3]);
            }
        }
    }
    std::cout << result << '\n';
}
