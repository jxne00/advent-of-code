#include "../utils/common.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    std::cout << "----- Day 1: Trebuchet?! (Part 1) -----\n" << std::endl;

    std::ifstream input(utils::get_input_path(argc, argv));
    std::string line;

    int calibration_sum = 0;
    while (std::getline(input, line)) {
        // find first and last digit
        auto first_it = std::find_if(line.begin(), line.end(), ::isdigit);
        auto last_it = std::find_if(line.rbegin(), line.rend(), ::isdigit);

        // convert digits to int then add to sum
        if (first_it != line.end() && last_it != line.rend()) {
            int first_digit = *first_it - '0';
            int last_digit = *last_it - '0';

            int calibration_val = (first_digit * 10) + last_digit;
            calibration_sum += calibration_val;

            std::cout << line << " -> " << calibration_val << std::endl;
        }
    }
    std::cout << "---------------\nFinal sum: " << calibration_sum << std::endl;
    return 0;
}