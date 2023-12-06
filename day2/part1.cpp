#include "../utils/common.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// stores count of each color
struct ColorCount {
    int red = 0;
    int green = 0;
    int blue = 0;
};

// returns a vector of ColorCount for each set
std::vector<ColorCount> getCounts(const std::string& line) {
    std::vector<ColorCount> counts;
    std::istringstream ss(line.substr(line.find(':') + 1));
    std::string set;

    // count colors for each set
    while (getline(ss, set, ';')) {
        ColorCount count{};
        std::istringstream set_ss(set);
        std::string color;
        int val;

        while (set_ss >> val >> color) {
            // remove comma
            if (color.back() == ',') color.pop_back();

            // add the count to respective color
            if (color == "red") count.red += val;
            else if (color == "green") count.green += val;
            else if (color == "blue") count.blue += val;
        }
        counts.push_back(count);
    }
    return counts;
}

int main(int argc, char* argv[]) {
    std::cout << "----- Day 2: Cube Conundrum (Part 1) -----\n" << std::endl;

    std::ifstream input(utils::get_input_path(argc, argv));
    std::string line;
    int game_id = 1;
    int sum_id = 0;

    while (getline(input, line)) {
        std::cout << line << "\n";
        bool valid = true;

        // loop through each set to check if valid
        for (const auto& count : getCounts(line)) {
            if (count.red > 12 || count.green > 13 || count.blue > 14) {
                std::cout << "Red: " << count.red << ", Green: " << count.green << ", Blue: " << count.blue << '\n';
                valid = false;
                break;
            }
            std::cout << "Red: " << count.red << ", Green: " << count.green << ", Blue: " << count.blue << " (OK)\n";
        }

        // add id to sum if all sets valid
        if (valid) sum_id += game_id;

        game_id++;
        std::cout << '\n';
    }

    std::cout << "===============\nSum of valid game IDs: " << sum_id << '\n';

    return 0;
}
