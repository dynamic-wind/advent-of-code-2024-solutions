#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <optional>
#include <raylib.h>
#include <vector>

int mod(int a, int b) {
    int r = a % b;
    return r >= 0 ? r : r + b;
}

struct robot {
    int px; int py;
    int vx; int vy;
};

std::optional<robot> read_robot(std::istream& is) {
    constexpr auto ignore_max = std::numeric_limits<std::streamsize>::max();
    robot result;
    is.ignore(ignore_max, '='); is >> result.px;
    is.ignore(ignore_max, ','); is >> result.py;
    is.ignore(ignore_max, '='); is >> result.vx;
    is.ignore(ignore_max, ','); is >> result.vy;
    if (is.fail()) {
        return std::nullopt;
    } else {
        return result;
    }
}


void update_robots(std::vector<robot>& robots, std::vector<std::vector<int>>& map, int times) {
    for (auto& robot : robots) {
        --map.at(robot.py).at(robot.px);
        robot.px = mod(robot.px + times*robot.vx, 101);
        robot.py = mod(robot.py + times*robot.vy, 103);
        ++map.at(robot.py).at(robot.px);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <INPUT_FILE>\n";
        return 0;
    }
    std::vector<std::vector<int>> map(103, std::vector<int>(101));
    std::vector<robot> robots;
    std::ifstream in(argv[1]);
    for (std::optional<robot> opt; opt = read_robot(in), opt.has_value();) {
        const auto& robot = opt.value();
        robots.push_back(robot);
        ++map.at(robot.py).at(robot.px);
    }

    SetTargetFPS(30);
    InitWindow(6*101, 6*103, "day14 - part 2");

    std::cout << "\n";
    std::cout << "Controls: \n";
    std::cout << "- Space Bar: toggle auto update\n";
    std::cout << "- Left Arrow: undo robot movement\n";
    std::cout << "- Right Arrow: do robot movement\n";
    std::cout.flush();

    int iterations = 0;
    bool update = false;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            update ^= 1;
        }
        if (!update && IsKeyPressed(KEY_LEFT)) {
            update_robots(robots, map, -1);
            --iterations;
            std::cout << iterations << '\n';
        }
        if (!update && IsKeyPressed(KEY_RIGHT)) {
            update_robots(robots, map, 1);
            ++iterations;
            std::cout << iterations << '\n';
        }
        if (update) {
            update_robots(robots, map, 1);
            ++iterations;
            std::cout << iterations << '\n';
        }

        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < 103; ++i) {
            for (int j = 0; j < 101; ++j) {
                if (map.at(i).at(j) > 0) {
                    DrawRectangle(6*j, 6*i, 6, 6, WHITE);
                }
            }
        }
        EndDrawing();
    }
    
    CloseWindow();
}
