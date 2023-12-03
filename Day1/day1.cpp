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
