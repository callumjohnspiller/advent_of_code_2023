//
// Created by Callum Spiller on 2023-12-03.
//
#include <fstream>
#include <map>
#include "iostream"
#include "string"
#include "day2.h"

std::string remove_spaces(std::string str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

bool valid_turn(const std::string &cubes, const std::string &color, int max) {
    int num = stoi(cubes.substr(0, cubes.find(color)));
    if (num > max) {
        return false;
    } else {
        return true;
    }
}

int day2::day_2() {
    // Open file + declare variables
    std::ifstream input("../Day2/input.txt");
    std::string line;
    int count = 0;
    int game_number = 1;
    std::string turn_delimiter = ";";
    std::string cubes_delimiter = ",";
    std::map<std::string, int> colors;
    colors["red"] = 12;
    colors["green"] = 13;
    colors["blue"] = 14;

    if (!input) {
        std::cerr << "Failed to open file." << std::endl;
        return -1; // Return an error code
    }

    while (std::getline(input, line)) {
        // Game is valid at start
        bool valid = true;
        // remove unnecessary characters from string
        std::string stripped = line.substr(line.find(':') + 2, -1);
        stripped = remove_spaces(stripped);
        // add helper delim
        stripped += turn_delimiter;
        // Build vector to track each time cubes are pulled from bag
        std::vector<std::string> turns;
        while ((stripped.find(turn_delimiter)) != std::string::npos) {
            turns.push_back(stripped.substr(0, stripped.find(turn_delimiter)));
            stripped.erase(0, stripped.find(turn_delimiter) + (turn_delimiter.length()));
        }

        for (auto &turn: turns) {
            //Early termination if game is invalidated
            if (!valid) break;
            // add helper delim
            turn += cubes_delimiter;
            // Iterate over the cubes drawn in each turn
            while ((turn.find(cubes_delimiter)) != std::string::npos) {
                std::string cubes = turn.substr(0, turn.find(cubes_delimiter));
                for (const auto& pair : colors) {
                    if (cubes.find(pair.first) != std::string::npos) {
                        if (!valid_turn(cubes, pair.first, pair.second)) {
                            valid = false;
                            break;
                        }
                    }
                }
                turn.erase(0, turn.find(cubes_delimiter) + 1);
            }
        }
        if (valid) count += game_number;
        ++game_number;
    }
    return count;
}

int day2::day_2b() {
    // Open file + declare variables
    std::ifstream input("../Day2/input.txt");
    std::string line;
    int count = 0;
    int game_number = 1;
    std::string turn_delimiter = ";";
    std::string cubes_delimiter = ",";
    std::map<std::string, int> min_colors;

    if (!input) {
        std::cerr << "Failed to open file." << std::endl;
        return -1; // Return an error code
    }

    while (std::getline(input, line)) {
        // remove unnecessary characters from string
        std::string stripped = line.substr(line.find(':') + 2, -1);
        stripped = remove_spaces(stripped);
        // add helper delim
        stripped += turn_delimiter;
        // Build vector to track each time cubes are pulled from bag
        std::vector<std::string> turns;
        while ((stripped.find(turn_delimiter)) != std::string::npos) {
            turns.push_back(stripped.substr(0, stripped.find(turn_delimiter)));
            stripped.erase(0, stripped.find(turn_delimiter) + (turn_delimiter.length()));
        }

        min_colors["red"] = 0;
        min_colors["green"] = 0;
        min_colors["blue"] = 0;

        for (auto &turn: turns) {
            // add helper delim
            turn += cubes_delimiter;
            // Iterate over the cubes drawn in each turn
            while ((turn.find(cubes_delimiter)) != std::string::npos) {
                std::string cubes = turn.substr(0, turn.find(cubes_delimiter));
                for (const auto &pair: min_colors) {
                    if (cubes.find(pair.first) != std::string::npos) {
                        int num = stoi(cubes.substr(0, cubes.find(pair.first)));
                        if (num > pair.second) {
                            min_colors[pair.first] = num;
                        }
                    }
                }
                turn.erase(0, turn.find(cubes_delimiter) + 1);
            }
        }
        int powers = min_colors["red"] * min_colors["blue"] * min_colors["green"];
        count += powers;

        ++game_number;
    }
    return count;
}
