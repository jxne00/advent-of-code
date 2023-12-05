#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// checks if position is adjacent to a symbol
bool isPartNumber(const std::vector<std::string>& schematic, int x, int y) {
    // positions of adjacent places
    const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    // loop through all 8 adjacent places
    for (int i = 0; i < 8; ++i) {
        int adj_x = x + dx[i];
        int adj_y = y + dy[i];

        if (adj_y >= 0 && adj_y < schematic.size()
            && adj_x >= 0 && adj_x < schematic[adj_y].size())
        {
            // get the value at adjacent position
            char adj_val = schematic[adj_y][adj_x];

            // check if value is a symbol
            if (!std::isdigit(adj_val) && adj_val != '.') {
                return true;
            }
        }
    }
    return false;
}


int main() {
    std::cout << "----- Day 3: Gear Ratios (Part 1) -----\n\n";
    std::ifstream input("input.txt");

    std::string line;
    std::vector<std::string> schematic;

    // add each line in txt file to schematic
    while (std::getline(input, line)) {
        schematic.push_back(line);
    }

    int sum_parts = 0;
    for (int y = 0; y < schematic.size(); y++) {
        for (int x = 0; x < schematic[y].size(); x++) {
            // find digit
            if (std::isdigit(schematic[y][x])) {
                int number = 0;
                bool is_part = false;

                // get the full number and check if it is a part number
                while (x < schematic[y].size() && std::isdigit(schematic[y][x])) {
                    number = number * 10 + (schematic[y][x] - '0');
                    if (!is_part) { // once true keep it as true
                        is_part = isPartNumber(schematic, x, y);
                    }
                    ++x;
                }

                // add to sum if number is a part number
                if (is_part)
                    sum_parts += number;

                // prevent double increment of x
                if (x < schematic[y].size()) --x;

                std::cout << "-> " << number;
                is_part ? std::cout << " (is part)" << std::endl : std::cout << std::endl;
            }
        }
    }

    std::cout << "------------\nSum of all part numbers: " << sum_parts << std::endl;
    return 0;
}
