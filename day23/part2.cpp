#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

constexpr std::size_t n_letters = 'z' - 'a' + 1;
constexpr std::size_t n_computers = n_letters * n_letters;

std::string computer_name(std::size_t a) {
    return std::string(1, a/n_letters + 'a') 
         + std::string(1, a%n_letters + 'a');
}

void solve(
    std::vector<std::vector<std::size_t>>& solutions,
    std::vector<std::size_t>& connected_so_far, 
    const std::vector<bool>& are_connected,
    std::size_t start, std::size_t n
) {
    if (connected_so_far.size() == n) {
        solutions.push_back(connected_so_far);
    } else {
        for (std::size_t i = start; i < n_computers; ++i) {
            bool all_connected = std::all_of(
                connected_so_far.begin(), connected_so_far.end(), 
                [&](std::size_t j) {
                    return are_connected.at(i*n_computers + j);
                }
            );
            if (all_connected) {
                connected_so_far.push_back(i);
                solve(solutions, connected_so_far, are_connected, i + 1, n);
                connected_so_far.pop_back();
            }
        }
    }
}

int main() {
    std::vector<bool> are_connected(n_computers * n_computers);
    for (char l1, l2, r1, r2;
         std::cin >> l1 >> l2 && std::cin.ignore(1) && std::cin >> r1 >> r2;
    ) {
        const std::size_t l = (l1-'a')*n_letters + (l2-'a');
        const std::size_t r = (r1-'a')*n_letters + (r2-'a');
        are_connected.at(l*n_computers + r) = true;
        are_connected.at(r*n_computers + l) = true;
    }
    for (int i = 3;; ++i) {
        std::vector<std::vector<std::size_t>> solutions;
        std::vector<std::size_t> connected_so_far;
        solve(solutions, connected_so_far, are_connected, 0, i);
        if (solutions.size() == 1) {
            for (std::size_t j = 0; j < solutions.at(0).size(); ++j) {
                if (j > 0) {
                    std::cout << ',';
                }
                std::cout << computer_name(solutions.at(0).at(j));
            }
            std::cout << '\n';
            break;
        }
    }
}
