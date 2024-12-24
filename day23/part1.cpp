#include <cstddef>
#include <iostream>
#include <vector>

int main() {
    constexpr std::size_t n_letters = 'z' - 'a' + 1;
    constexpr std::size_t n_computers = n_letters * n_letters;
    std::vector<bool> connected(n_computers * n_computers);
    for (char l1, l2, r1, r2;
         std::cin >> l1 >> l2 &&
         std::cin.ignore(1) &&
         std::cin >> r1 >> r2;
    ) {
        const std::size_t l = (l1-'a')*n_letters + (l2-'a');
        const std::size_t r = (r1-'a')*n_letters + (r2-'a');
        connected.at(l*n_computers + r) = true;
        connected.at(r*n_computers + l) = true;
    }
    std::size_t result = 0;
    for (std::size_t i = 0; i < n_computers-2; ++i) {
        for (std::size_t j = i+1; j < n_computers-1; ++j) {
            if (connected.at(i*n_computers + j)) {
                for (std::size_t k = j+1; k < n_computers; ++k) {
                    if (connected.at(i*n_computers + k) &&
                        connected.at(j*n_computers + k)
                    ) {
                        result += (i/n_letters + 'a' == 't'
                                || j/n_letters + 'a' == 't'
                                || k/n_letters + 'a' == 't');
                    }
                }
            }
        }
    }
    std::cout << result << '\n';
}
