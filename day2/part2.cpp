#include "../utils/common.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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
    int power_sum = 0;

    while (getline(input, line)) {
        std::cout << line << "\n";

        // get the counts for each set
        std::vector<ColorCount> counts = getCounts(line);

        // find the min cubes (max count) for each color
        ColorCount min_cubes{};
        for (const auto& count : counts) {
            min_cubes.red = std::max(min_cubes.red, count.red);
            min_cubes.green = std::max(min_cubes.green, count.green);
            min_cubes.blue = std::max(min_cubes.blue, count.blue);
        }

        // get power of set
        int power = min_cubes.red * min_cubes.green * min_cubes.blue;
        power_sum += power;

        std::cout << "-> Power: " << power << '\n' << std::endl;
    }

    std::cout << "===============\nSum of powers: " << power_sum << '\n';

    return 0;
}
