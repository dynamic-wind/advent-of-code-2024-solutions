#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

int main() {
    std::vector<int> left;
    std::unordered_map<int, int> right_counts;
    for (int a, b; std::cin >> a >> b;) {
        left.push_back(a);
        ++right_counts[b];
    }
    int result = 0;
    for (int e : left) {
        result += e * right_counts[e];
    }
    std::cout << result << '\n';
}
