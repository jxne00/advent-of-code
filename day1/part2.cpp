#include "../utils/common.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

// replace all digit words with digits
void replaceDigitWords(std::string& str, const std::unordered_map<std::string, std::string>& mapping) {
    for (const auto& [word, digit] : mapping) {
        std::string::size_type i = 0;
        while ((i = str.find(word, i)) != std::string::npos) {
            // replace word with digit
            str.replace(i, word.length(), digit);
            i += digit.length();
        }
    }
}

int main(int argc, char* argv[]) {
    std::cout << "----- Day 1: Trebuchet?! (Part 2) -----" << std::endl;
    std::ifstream input(utils::get_input_path(argc, argv));
    std::string line;

    // maps digit words to its digit
    std::unordered_map<std::string, std::string> mapping = {
        {"one", "o1e"}, {"two", "t2o"}, {"three", "t3e"},
        {"four", "f4r"}, {"five", "f5e"}, {"six", "s6x"},
        {"seven", "s7n"}, {"eight", "e8t"}, {"nine", "n9e"}
    };

    int sum = 0;
    while (std::getline(input, line)) {
        std::cout << '\n' << line << std::endl;
        // convert all words to digits
        replaceDigitWords(line, mapping);

        // find first and last digit
        auto first_it = std::find_if(line.begin(), line.end(), ::isdigit);
        auto last_it = std::find_if(line.rbegin(), line.rend(), ::isdigit);

        // convert digits to 2 digit number then add to sum
        if (first_it != line.end() && last_it != line.rend()) {
            int first_digit = *first_it - '0';
            int last_digit = *last_it - '0';

            int calibration_val = (first_digit * 10) + last_digit;
            sum += calibration_val;

            std::cout << line << " -> " << calibration_val << std::endl;
        }
    }
    std::cout << "===========\nSum of calibration values: " << sum << std::endl;
    return 0;
}