#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    std::vector<int> left, right;
    for (int a, b; std::cin >> a >> b;) {
        left.push_back(a);
        right.push_back(b);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    int result = 0;
    for (std::size_t i = 0; i < left.size(); ++i) {
        result += std::abs(left.at(i) - right.at(i));
    }
    std::cout << result << '\n';
}
