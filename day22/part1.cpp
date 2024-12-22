#include <cstdint>
#include <iostream>

std::uint64_t next_secret_number(std::uint64_t n) {
    constexpr std::uint64_t m = 16777216;
    n = (n ^ (64*n)) % m;
    n = (n ^ (n/32)) % m;
    n = (n ^ (2048*n)) % m;
    return n;
}

int main() {
    std::uint64_t result = 0;
    for (int n; std::cin >> n;) {
        for (int i = 0; i < 2000; ++i) {
            n = next_secret_number(n);
        }
        result += n;
    }
    std::cout << result << '\n';
}
