//
// Created by Callum Spiller on 2023-12-05.
//

#include "day3.h"
#include "array"
#include "fstream"
#include "iostream"

static const int dimension = 140;


std::vector<char> get_adjacent_values(
        std::array<std::array<char, dimension>, dimension> matrix,
        size_t x,
        size_t y,
        size_t len) {

    std::vector<char> output;

    // Offsets for the 8 surrounding cells in a clockwise circle
    int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};

    // for every coordinate of the number:
    for (size_t i = 0; i < len; ++i) {
        // loop through surrounding elements:
        size_t newX = x - i;
        for (int j = 0; j < 8; ++j) {
            size_t loopX = newX + dx[j];
            if (loopX < dimension) {
                if ((y + dy[j] >= 0 && (y + dy[j]) < dimension)) {
                    output.push_back(matrix[y+dy[j]][loopX]);
                    continue;
                }
            }
            output.push_back('.');
        }
    }
    return output;
}

std::array<std::array<char, dimension>, dimension> setup() {
    std::ifstream input("../Day3/input.txt");
    std::string line;
    if (!input) {
        std::cerr << "Failed to open file." << std::endl;
    }

//     build 2d array from text file

    std::array<std::array<char, dimension>, dimension> matrix = {};

    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            input >> matrix[i][j];
        }
    }
    input.close();
    return matrix;
}


int day3::day_3() {

    std::array<std::array<char, dimension>, dimension> matrix = setup();

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

std::string get_full_number(std::array<std::array<char, dimension>, dimension> matrix, size_t x, size_t y) {
    size_t start_x = x;
    size_t end_x = x;
    std::string output;
    for (; isdigit(matrix[y][start_x]); --start_x) {
    }
    for (; isdigit(matrix[y][end_x]); ++end_x) {
    }
    for (size_t i = start_x+1; i<=end_x-1; ++i) {
        output.push_back(matrix[y][i]);
    }
    return output;
}

int day3::day_3b() {
    std::array<std::array<char, dimension>, dimension> matrix = setup();

//    Declare required variables

    int count = 0;

//    iterate over matrix, find gears

    size_t i = 0;
    for (std::array<char, dimension> row : matrix) {
        size_t j = 0;
        for (char c : row) {
            if (c == '*') {
                std::vector<char> adjacent = get_adjacent_values(matrix, j, i, 1);
                char prev = '\0';
                size_t k = 0;
                std::vector<std::string> found_numbers;
                for (char d : adjacent) {
                    if (isdigit(d) && (!isdigit(prev) || (k == 3 || k == 7))) {
                        switch (k) {
                            case 0:
                                found_numbers.push_back(get_full_number(matrix, j-1, i-1));
                                break;
                            case 1:
                                found_numbers.push_back(get_full_number(matrix, j, i-1));
                                break;
                            case 2:
                                found_numbers.push_back(get_full_number(matrix, j+1, i-1));
                                break;
                            case 3:
                                found_numbers.push_back(get_full_number(matrix, j+1, i));
                                break;
                            case 4:
                                found_numbers.push_back(get_full_number(matrix, j+1, i+1));
                                break;
                            case 5:
                                found_numbers.push_back(get_full_number(matrix, j, i+1));
                                break;
                            case 6:
                                found_numbers.push_back(get_full_number(matrix, j-1, i+1));
                                break;
                            case 7:
                                found_numbers.push_back(get_full_number(matrix, j-1, i));
                                break;
                            default:
                                std::cout << "Error in found number index" << std::endl;
                        }
                    }
                    k++;
                    prev = d;
                }
                if (found_numbers.size() == 2) {
                    int torque = 1;
                    for (std::string number : found_numbers) {
                        torque *= stoi(number);
                    }
                    count += torque;
                }

            }
            j++;
        }
        i++;
    }
    return count;
}
