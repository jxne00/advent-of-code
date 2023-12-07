#include "../utils/common.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// calculate number of ways to beat record for each race
std::vector<int> get_num_ways(std::vector<int> time_vals,
                              std::vector<int> dist_vals) {
    std::vector<int> ways;
    for (size_t i = 0; i < time_vals.size(); i++) {
        int race_time = time_vals[i];
        int beaten = 0;
        // calculate dist for each ms of button press
        for (int j = 0; j < race_time; j++) {
            int dist = j * (race_time - j);
            // if dist surpasses the record
            if (dist > dist_vals[i]) {
                beaten++;
            }
        }
        ways.push_back(beaten);
    }
    return ways;
}

int main(int argc, char *argv[]) {
    std::cout << "----- Day 6: Wait For It (Part 1) -----\n" << std::endl;

    std::ifstream input(utils::get_input_path(argc, argv));
    std::string line;

    // store time & dist values into vectors
    std::vector<int> time_vals, dist_vals;
    while (std::getline(input, line)) {
        std::vector<std::string> tokens = utils::tokenise(line);
        if (!tokens.empty()) {
            if (tokens[0] == "Time:" || tokens[0] == "Distance:") {
                auto &target_vec =
                    (tokens[0] == "Time:") ? time_vals : dist_vals;
                for (size_t i = 1; i < tokens.size(); i++) {
                    target_vec.push_back(std::stoi(std::move(tokens[i])));
                }
            }
        }
    }

    // get number of ways to beat record for each race
    std::vector<int> num_ways = get_num_ways(time_vals, dist_vals);

    // calculate product of all ways
    int product = 1;
    for (auto &ways : num_ways) {
        product *= ways;
    }

    // print results
    std::cout << "time_vals: ";
    utils::print_vector(time_vals);
    std::cout << "dist_vals: ";
    utils::print_vector(dist_vals);

    std::cout << "\n-> Result: " << product << " (";
    for (auto &ways : num_ways) {
        if (ways == num_ways.back())
            std::cout << ways;
        else
            std::cout << ways << " * ";
    }
    std::cout << ")" << std::endl;

    return 0;
}