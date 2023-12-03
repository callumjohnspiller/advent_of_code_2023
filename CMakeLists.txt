cmake_minimum_required(VERSION 3.26)
project(aoc_2023)

# Add subdirectories for each day
add_subdirectory(Day1)

set(CMAKE_CXX_STANDARD 20)

add_executable(aoc_2023 main.cpp)

target_link_libraries(aoc_2023 day1)  # Link day-wise libraries
