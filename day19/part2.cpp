
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> patterns;
    for (std::string s;;) {
        std::cin >> s;
        if (s.back() == ',') {
            s.pop_back();
            patterns.push_back(std::move(s));
        } else {
            patterns.push_back(std::move(s));
            break;
        }
    }
    std::int64_t result = 0;
    for (std::string s; std::cin >> s;) {
        std::vector<std::int64_t> dp(s.size()+1);
        dp.at(s.size()) = 1;
        for (int i = s.size()-1; i >= 0; --i) {
            for (const auto& p : patterns) {
                if (s.substr(i, p.size()) == p) {
                    dp.at(i) += dp.at(i + p.size());
                }
            }
        }
        result += dp.at(0);
    }
    std::cout << result << '\n';
}
