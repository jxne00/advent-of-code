#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream input("input.txt");
    std::string line;

    int calibration_sum = 0;
    int line_count = 1;
    while (std::getline(input, line)) {
        int first_digit = -1;
        int last_digit = -1;

        // find the first digit occurence
        for (int i = 0; i < line.size(); i++) {
            if (isdigit(line[i])) {
                first_digit = line[i] - '0';
                break;
            }
        }

        // find the last digit occurence
        for (int i = line.size() - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                last_digit = line[i] - '0';
                break;
            }
        }

        // add calibration value to sum
        if (first_digit != -1 && last_digit != -1) {
            int calibration_val = (first_digit * 10) + last_digit;
            calibration_sum += calibration_val;

            std::cout << line_count++ << ") " << calibration_val << std::endl;
        }
    }
    std::cout << "\nFinal sum: " << calibration_sum << std::endl;
    return 0;
}
