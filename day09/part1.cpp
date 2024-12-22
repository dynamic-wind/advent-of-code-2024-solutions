#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> expand_input(const std::string& input) {
    std::vector<int> result;
    int id = 0;
    for (std::size_t i = 0; i < input.size(); ++i) {
        if (i%2 == 0) {
            for (int j = 0; j < input.at(i)-'0'; ++j) {
                result.push_back(id);
            }
            ++id;
        } else {
            for (int j = 0; j < input.at(i)-'0'; ++j) {
                result.push_back(-1);
            }
        }
    }
    return result;
}

void compact_hard_drive(std::vector<int>& hard_drive) {
    int free_position = 0;
    int file_position = hard_drive.size()-1;
    while (free_position < file_position) {
        if (hard_drive.at(free_position) != -1) {
            ++free_position;
        } else if (hard_drive.at(file_position) == -1) {
            --file_position;
        } else {
            hard_drive.at(free_position) = hard_drive.at(file_position);
            hard_drive.at(file_position) = -1;
        }
    }
}

std::int64_t compute_filesystem_checksum(const std::vector<int>& hard_drive) {
    std::int64_t result = 0;
    for (std::size_t i = 1; i < hard_drive.size(); ++i) {
        if (hard_drive.at(i) != -1) {
            result += i*hard_drive.at(i);
        }
    }
    return result;
}

int main() {
    std::string input; std::cin >> input;
    auto hard_drive = expand_input(input);
    compact_hard_drive(hard_drive);
    auto checksum = compute_filesystem_checksum(hard_drive);
    std::cout << checksum << '\n';
}
