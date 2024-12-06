#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
    std::vector<std::string> word_search;
    for (std::string line; std::getline(std::cin, line);) {
        word_search.push_back(std::move(line));
    }
    const int rows = word_search.size();
    const int columns = word_search.at(0).size();
    int result = 0;
    for (int i = 1; i < rows-1; ++i) {
        for (int j = 1; j < columns-1; ++j) {
            result += (word_search.at(i).at(j) == 'A'
                    && ((word_search.at(i-1).at(j-1) == 'M'
                      && word_search.at(i+1).at(j+1) == 'S')
                     || (word_search.at(i-1).at(j-1) == 'S'
                      && word_search.at(i+1).at(j+1) == 'M'))
                    && ((word_search.at(i-1).at(j+1) == 'M'
                      && word_search.at(i+1).at(j-1) == 'S')
                     || (word_search.at(i-1).at(j+1) == 'S'
                      && word_search.at(i+1).at(j-1) == 'M')));

        }
    }
    std::cout << result << '\n';
}
