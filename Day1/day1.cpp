// day1.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "day1.h"

int day1::day_1() {
    std::ifstream input("../Day1/input.txt");
    int count = 0;
    std::string line;

    if (!input) {
        std::cerr << "Failed to open file." << std::endl;
        return -1; // Return an error code
    }

    while (std::getline(input, line)) {
        std::string number;

        // Find the first digit from the front
        auto frontDigit = std::find_if(line.begin(), line.end(), ::isdigit);
        if (frontDigit != line.end()) {
            number.push_back(*frontDigit);
        }

        // Find the first digit from the back
        auto backDigit = std::find_if(line.rbegin(), line.rend(), ::isdigit);
        if (backDigit != line.rend()) {
            number.push_back(*backDigit);
        }

        if (!number.empty()) {
            count += std::stoi(number);
        }
    }

    return count;
}

char find_number(std::string line, std::unordered_map<std::string, char> const& string_numbers, bool rev=false) {
    if (rev) {std::reverse(line.begin(), line.end());}
    std::string buffer = "";
    char number = '\0';
    for (char c : line) {
        if (isnumber(c)) {
            number = c;
            break;
        }
        if (rev) {
            buffer.insert(0, 1, c);
        } else {
            buffer.push_back(c);
        }

        if (buffer.length() > 2) {
            for (const auto& string : string_numbers) {
                if (buffer.find(string.first) != std::string::npos) {
                    number = string.second;
                    break;
                }
            }
            if (number != '\0') break;
        }
    }
    return number;
}

int day1::day_1b() {
    std::ifstream input("../Day1/input.txt");
    int count = 0;
    std::string line;

    if (!input) {
        std::cerr << "Failed to open file." << std::endl;
        return -1; // Return an error code
    }

    std::unordered_map<std::string, char> string_numbers;
    string_numbers["one"] = '1';
    string_numbers["two"] = '2';
    string_numbers["three"] = '3';
    string_numbers["four"] = '4';
    string_numbers["five"] = '5';
    string_numbers["six"] = '6';
    string_numbers["seven"] = '7';
    string_numbers["eight"] = '8';
    string_numbers["nine"] = '9';

    while (std::getline(input, line)) {
        std::string number;
        number += find_number(line, string_numbers);
        number += find_number(line, string_numbers, true);

        if (!number.empty()) {
            count += std::stoi(number);
        }
    }

    return count;
}
