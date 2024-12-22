#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<int, int>> run_length_encode_input(const std::string& input) {
    std::vector<std::pair<int, int>> result;
    for (std::size_t i = 0; i < input.size(); ++i) {
        if (i%2 == 0) {
            result.emplace_back(input.at(i)-'0', i/2);
        } else {
            result.emplace_back(input.at(i)-'0', -1);
        }
    }
    return result;
}

void compact_hard_drive(std::vector<std::pair<int, int>>& hard_drive) {
    
    for (int file_position = hard_drive.size()-1; file_position >= 0; --file_position) {
        if (hard_drive.at(file_position).second != -1) {
            for (int free_position = 0;
                 free_position < file_position;
                 ++free_position)
            {
                if (hard_drive.at(free_position).second == -1) {
                    int free_size = hard_drive.at(free_position).first;
                    int file_size = hard_drive.at(file_position).first;
                    if (file_size <= free_size) {
                        hard_drive.at(free_position).first = free_size - file_size;
                        int file_id = hard_drive.at(file_position).second;
                        hard_drive.at(file_position).second = -1;
                        hard_drive.insert(
                            hard_drive.begin() + free_position,
                            {file_size, file_id}
                        );
                        break;
                    }
                }
            }
        }
    }
}

std::int64_t compute_filesystem_checksum(
    const std::vector<std::pair<int, int>>& hard_drive
) {
    std::int64_t result = 0;
    std::int64_t block_position = 0;
    for (std::size_t i = 0; i < hard_drive.size(); ++i) {
        if (hard_drive.at(i).second == -1) {
            block_position += hard_drive.at(i).first;
        } else {
            for (int j = 0; j < hard_drive.at(i).first; ++j) {
                result += block_position*hard_drive.at(i).second;
                ++block_position;
            }
        }
    }
    return result;
}

int main() {
    std::string input; std::cin >> input;
    auto hard_drive = run_length_encode_input(input);
    compact_hard_drive(hard_drive);
    auto checksum = compute_filesystem_checksum(hard_drive);
    std::cout << checksum << '\n';
}
