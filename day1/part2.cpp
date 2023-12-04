#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>

std::string replaceDigitWords(std::string input) {
    std::unordered_map<std::string, std::string> word_digit_map = {
        {"one", "1"}, {"two", "2"}, {"three", "3"},
        {"four", "4"}, {"five", "5"}, {"six", "6"},
        {"seven", "7"}, {"eight", "8"}, {"nine", "9"}
    };

    bool toRight = true;
    while (true) {
        size_t position = std::string::npos;
        std::string numberForm;
        size_t wordLength = 0;

        for (const auto& pair : word_digit_map) {
            // search for next word
            size_t foundPos = toRight ? input.find(pair.first) : input.rfind(pair.first);

            if (foundPos != std::string::npos && (position == std::string::npos ||
                (toRight && foundPos < position) || (!toRight && foundPos > position))) {
                position = foundPos;
                numberForm = pair.second;
                wordLength = pair.first.length();
            }
        }

        // replace word with its number form if found
        if (position != std::string::npos) {
            input.replace(position, wordLength, numberForm);
        }
        else break; // search end

        // toggle search direction
        toRight = !toRight;
    }

    return input;
}

int main() {
    std::ifstream input("input.txt");
    std::string line;

    int calibration_sum = 0;
    int line_count = 1;
    while (std::getline(input, line)) {
        // convert all words to digits
        std::string digits_line = replaceDigitWords(line);
        std::cout << line_count++ << ". " << line << " (" << digits_line << ")" << std::endl;

        int first_digit = -1;
        int last_digit = -1;

        // find the first digit occurence
        for (int i = 0; i < digits_line.size(); i++) {
            if (isdigit(digits_line[i])) {
                first_digit = digits_line[i] - '0';
                break;
            }
        }

        // find the last digit occurence
        for (int i = digits_line.size() - 1; i >= 0; i--) {
            if (isdigit(digits_line[i])) {
                last_digit = digits_line[i] - '0';
                break;
            }
        }

        // add calibration value to sum
        if (first_digit != -1 && last_digit != -1) {
            int calibration_val = (first_digit * 10) + last_digit;
            calibration_sum += calibration_val;

            std::cout << " ->  " << calibration_val << std::endl;
            std::cout << std::endl;
        }
    }
    std::cout << "===========\nFinal sum: " << calibration_sum << std::endl;
    return 0;
}