// UNSOLVED
#include "../utils/common.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// to store position of part numbers
struct PartNumber {
    size_t x;
    size_t y;
};

// checks if position is adjacent to a symbol
bool isPartNumber(const std::vector<std::string> &schematic, int x, int y) {
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; ++i) {
        size_t adj_x = x + dx[i];
        size_t adj_y = y + dy[i];

        if (adj_y >= 0 && adj_y < schematic.size() && adj_x >= 0 &&
            adj_x < schematic[adj_y].size()) {
            char adj_val = schematic[adj_y][adj_x];
            if (!std::isdigit(adj_val) && adj_val != '.') {
                return true;
            }
        }
    }
    return false;
}

int getGearRatio(const std::vector<std::string> &schematic, int x, int y,
                 const std::vector<PartNumber> &part_numbers) {
    // only * can be gear
    if (schematic[y][x] != '*') {
        return false;
    }

    // positions of adjacent places
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int count = 0;
    int val1 = 0, ratio = 0;

    for (int i = 0; i < 8; ++i) {
        size_t adj_x = x + dx[i];
        size_t adj_y = y + dy[i];

        // check how many part numbers there are
        for (size_t j = 0; j < part_numbers.size(); ++j) {
            if (adj_x == part_numbers[j].x && adj_y == part_numbers[j].y) {
                // get values of part numbers
                if (count == 0) {
                    val1 = schematic[adj_y][adj_x] - '0';
                } else if (count == 1) {
                    int val2 = schematic[adj_y][adj_x] - '0';
                    ratio = val1 * val2;
                }
                ++count;
            }
        }
    }

    // calculate gear ratio
    if (count == 2) {
        return ratio;
    } else {
        return -1;
    }
}

int main(int argc, char *argv[]) {
    std::cout << "----- Day 3: Gear Ratios (Part 2) -----\n\n";
    std::ifstream input(utils::get_input_path(argc, argv));

    std::string line;
    std::vector<std::string> schematic;
    std::vector<PartNumber> part_numbers;

    // add each line in txt file to schematic
    while (std::getline(input, line)) {
        schematic.push_back(line);
    }

    // get position of all part numbers in schematic
    for (size_t y = 0; y < schematic.size(); y++) {
        for (size_t x = 0; x < schematic[y].size(); x++) {
            bool is_part = false;
            // get the position of all part numbers
            if (std::isdigit(schematic[y][x])) {
                int number = 0;
                while (x < schematic[y].size() &&
                       std::isdigit(schematic[y][x])) {
                    number = number * 10 + (schematic[y][x] - '0');
                    if (!is_part) { // once true keep it as true
                        is_part = isPartNumber(schematic, x, y);
                        if (is_part) {
                            // store position of part number
                            part_numbers.push_back({x, y});
                        }
                    }
                    ++x;
                }
            }
        }
    }

    // find all gears and get their gear ratio
    int sum_ratio = 0;
    for (size_t y = 0; y < schematic.size(); y++) {
        for (size_t x = 0; x < schematic[y].size(); x++) {
            int ratio = getGearRatio(schematic, x, y, part_numbers);
            if (ratio != -1) {
                sum_ratio += ratio;
            }
        }
    }

    std::cout << "------------\nSum of all gear ratios: " << sum_ratio
              << std::endl;

    return 0;
}
