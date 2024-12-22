#include <algorithm>
#include <array>
#include <climits>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

using namespace std::literals;

const std::array<std::array<char, 3>, 4> numeric_keypad_layout {{
    {'7', '8', '9'},
    {'4', '5', '6'},
    {'1', '2', '3'},
    {  0, '0', 'A'},
}};

const std::array<std::pair<int, int>, 4> offsets = {{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1},
}};

std::string_view move_directional_keypad(char from, char to) {
    switch (from) {
        case 'v': switch (to) {
            case 'v': return "A"sv;
            case '>': return ">A"sv;
            case '^': return "^A"sv;
            case '<': return "<A"sv;
            case 'A': return "^>A"sv;
        } break;
        case '>': switch (to) {
            case 'v': return "<A"sv;
            case '>': return "A"sv;
            case '^': return "<^A"sv;
            case '<': return "<<A"sv;
            case 'A': return "^A"sv;
        } break;
        case '^': switch (to) {
            case 'v': return "vA"sv;
            case '>': return "v>A"sv;
            case '^': return "A"sv;
            case '<': return "v<A"sv;
            case 'A': return ">A"sv;
        } break;
        case '<': switch (to) {
            case 'v': return ">A"sv;
            case '>': return ">>A"sv;
            case '^': return ">^A"sv;
            case '<': return "A"sv;
            case 'A': return ">>^A"sv;
        } break;
        case 'A': switch (to) {
            case 'v': return "<vA"sv;
            case '>': return "vA"sv;
            case '^': return "<A"sv;
            case '<': return "v<<A"sv;
            case 'A': return "A"sv;
        } break;
    }
    std::terminate();
}

std::int64_t button_to_index(char c) {
    switch (c) {
        case 'v': return 0;
        case '>': return 1;
        case '^': return 2;
        case '<': return 3;
        case 'A': return 4;
    }
    std::terminate();
}

std::vector<std::string> numeric_keypad_sequences(const std::string& door_code) {
    const int n = door_code.size();
    std::vector<std::string> result;
    std::vector<std::tuple<int, int, int, std::string>> current = {
        {3, 2, 0, ""}
    };
    while (result.size() == 0 && current.size() > 0) {
        std::vector<std::tuple<int, int, int, std::string>> next;
        for (const auto& [i, j, output_length, buttons_pressed] : current) {
            char button = numeric_keypad_layout.at(i).at(j);
            if (button == door_code.at(output_length)) {
                if (output_length+1 == n) {
                    result.push_back(buttons_pressed + 'A');
                } else {
                    next.emplace_back(i, j, output_length+1, buttons_pressed + 'A');
                }
            } else {
                for (int o = 0; o < 4; ++o) {
                    int ni = i + offsets.at(o).first;
                    int nj = j + offsets.at(o).second;
                    bool in_bounds = (0 <= ni && ni < 4 && 0 <= nj && nj < 3);
                    if (in_bounds && numeric_keypad_layout.at(ni).at(nj) != '\0') {
                        next.emplace_back(ni, nj, output_length, buttons_pressed + "v>^<A"sv.at(o));
                    }
                }
            }
        }
        current = std::move(next);
    }
    return result;
}

int main() {
    std::array<std::array<std::int64_t, 5>, 5> current;
    for (auto& row : current) {
        row.fill(1);
    }
    std::array<std::array<std::int64_t, 5>, 5> previous;
    for (std::int64_t t = 0; t < 2; ++t) {
        previous = current;
        for (auto& row : current) {
            row.fill(0);
        }
        const std::string_view buttons = "v>^<A"sv;
        for (std::int64_t i = 0; i < 5; ++i) {
            char bi = buttons.at(i);
            for (std::int64_t j = 0; j < 5; ++j) {
                char bj = buttons.at(j);
                char previous_button = 'A';
                for (char button : move_directional_keypad(bi, bj)) {
                    current.at(i).at(j) += previous
                        .at(button_to_index(previous_button))
                        .at(button_to_index(button));
                    previous_button = button;
                }
            }
        }
    }
    std::int64_t result = 0;
    for (std::string door_code; std::cin >> door_code;) {
        std::int64_t shortest_length = INT64_MAX;
        for (const auto& button_sequence : numeric_keypad_sequences(door_code)) {
            char previous_button = 'A';
            std::int64_t length = 0;
            for (char button : button_sequence) {
                length += current
                    .at(button_to_index(previous_button))
                    .at(button_to_index(button));
                previous_button = button;
            }
            shortest_length = std::min(shortest_length, length);
        }
        result += shortest_length * std::stoi(door_code.substr(0, door_code.size()-1));
    }
    std::cout << result << '\n';
}
