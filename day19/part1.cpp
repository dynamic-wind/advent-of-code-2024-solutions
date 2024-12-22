#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> patterns;
    for (std::string p;;) {
        std::cin >> p;
        if (p.back() == ',') {
            p.pop_back();
            patterns.push_back(std::move(p));
        } else {
            patterns.push_back(std::move(p));
            break;
        }
    }
    int result = 0;
    for (std::string s; std::cin >> s;) {
        std::vector<bool> dp(s.size()+1);
        dp.at(s.size()) = true;
        for (int i = s.size()-1; i >= 0; --i) {
            for (const auto& p : patterns) {
                if (s.substr(i, p.size()) == p) {
                    dp.at(i) = dp.at(i) || dp.at(i + p.size());
                }
            }
        }
        result += dp.at(0);
    }
    std::cout << result << '\n';
}
