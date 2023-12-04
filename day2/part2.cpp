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

int main() {
    std::ifstream file("input.txt");
    std::string line;
    int game_id = 1;
    int power_sum = 0;

    while (getline(file, line)) {
        std::cout << line << "\n";
        bool valid = true;

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

        std::cout << "-> Power: " << power << '\n';

        game_id++;
        std::cout << '\n';
    }

    std::cout << "===============\nSum of powers: " << power_sum << '\n';

    return 0;
}
