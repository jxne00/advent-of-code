// UNSOLVED
#include "../utils/common.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "----- Day 5: If You Give A Seed A Fertilizer (Part 1) -----\n"
              << std::endl;

    std::ifstream input(utils::get_input_path(argc, argv));
    std::string line;

    while (std::getline(input, line)) {
        std::cout << line << std::endl;
    }

    std::cout << "---------------\nResult: "
              << "here" << std::endl;
    return 0;
}