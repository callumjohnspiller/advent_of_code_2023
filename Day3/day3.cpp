//
// Created by Callum Spiller on 2023-12-05.
//

#include "day3.h"
#include "array"
#include "set"
#include "fstream"
#include "iostream"

static const int dimension = 140;


std::vector<char> get_adjacent_values(
        std::array<std::array<char, dimension>, dimension> matrix,
        size_t x,
        size_t y,
        size_t len) {

    std::vector<char> output;

    // Offsets for the 8 surrounding cells
    int dx[] = {-1, -1, -1,  1, 1, 1, 0,  0};
    int dy[] = {-1,  0 , 1, -1, 0, 1, 1, -1};

    // for every coordinate of the number:
    for (size_t i = 0; i < len; ++i) {
        // loop through surrounding elements:
        size_t newX = x - i;
        for (int j = 0; j < 8; ++j) {
            size_t loopX = newX + dx[j];
            if (loopX < dimension) {
                if ((y + dy[j] >= 0 && (y + dy[j]) < dimension)) {
                    output.push_back(matrix[y+dy[j]][loopX]);
                }
            }
        }
    }
    return output;
}


int day3::day_3() {
    std::ifstream input("../Day3/input.txt");
    std::string line;
    if (!input) {
        std::cerr << "Failed to open file." << std::endl;
        return -1; // Return an error code
    }

//     build 2d array from text file

    std::array<std::array<char, dimension>, dimension> matrix = {};

    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            input >> matrix[i][j];
        }
    }
    input.close();

//    Declare required variables

    int count = 0;
    std::string num_buffer;

//    iterate over matrix:
    size_t i = 0;
    for (std::array<char, dimension> row : matrix) {
        size_t j = 0;
        for (char c : row) {
            std::vector<char> adjacent;
            // if number, add to buffer, check not endl, if so, get values
            if (isdigit(c)) {
                num_buffer.push_back(c);
                if (j == dimension-1) {
                    adjacent = get_adjacent_values(matrix, j, i, num_buffer.length());
                } else {
                    j++;
                    continue;
                }
            } else { //if not number, check if number in buffer
                if (num_buffer.length() > 0) { // if so, collect and get adjacent values from previous index
                    adjacent = get_adjacent_values(matrix, j - 1, i, num_buffer.length());
                } else {
                    j++;
                    continue;
                }
            }

            for(char d : adjacent) {
                if (!isdigit(d) && d != '.') {
                    count += stoi(num_buffer);
                    break;
                }
            }
            num_buffer.clear();
            j++;
        }
        i++;
    }
    return count;
}

int day3::day_3b() {
    return 0;
}
