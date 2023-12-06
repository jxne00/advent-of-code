#include "../utils/common.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    std::cout << "----- Day 6: Wait For It (Part 1) -----\n" << std::endl;

    std::ifstream input(utils::get_input_path(argc, argv));
    std::string line;

    while (std::getline(input, line)) {
        std::cout << line << std::endl;
    }

    std::cout << "---------------\nResult: " << "here" << std::endl;
    return 0;
}