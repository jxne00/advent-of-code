#include "../utils/common.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

// map digit words to its digit
std::unordered_map<std::string, std::string> word_digit_map = {
    {"one", "1"}, {"two", "2"}, {"three", "3"},
    {"four", "4"}, {"five", "5"}, {"six", "6"},
    {"seven", "7"}, {"eight", "8"}, {"nine", "9"}
};

// replace all digit words with digits
std::string replaceDigitWords(std::string input) {
    for (auto& [word, digit] : word_digit_map) {
        std::string::size_type pos = 0;
        while ((pos = input.find(word, pos)) != std::string::npos) {
            // replace word with digit
            input.replace(pos, word.length(), digit);
            pos += digit.length();
        }
    }
    return input;
}

int main(int argc, char* argv[]) {
    std::cout << "----- Day 1: Trebuchet?! (Part 2) -----" << std::endl;
    std::ifstream input(utils::get_input_path(argc, argv));
    std::string line;

    int calibration_sum = 0;
    while (std::getline(input, line)) {
        std::cout << '\n' << line << std::endl;
        // convert all words to digits
        std::string digits_line = replaceDigitWords(line);

        // find first and last digit
        auto first_it = std::find_if(digits_line.begin(), digits_line.end(), ::isdigit);
        auto last_it = std::find_if(digits_line.rbegin(), digits_line.rend(), ::isdigit);

        // convert digits to int then add to sum
        if (first_it != digits_line.end() && last_it != digits_line.rend()) {
            int first_digit = *first_it - '0';
            int last_digit = *last_it - '0';

            int calibration_val = (first_digit * 10) + last_digit;
            calibration_sum += calibration_val;

            std::cout << digits_line << " -> " << calibration_val << std::endl;
        }
    }
    std::cout << "===========\nFinal sum: " << calibration_sum << std::endl;
    return 0;
}