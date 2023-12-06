#include "../utils/common.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> tokenise(const std::string &str) {
    std::vector<int> tokens;
    std::istringstream iss(str);
    std::string token;

    while (getline(iss, token, ' ')) {
        if (!token.empty()) {
            tokens.push_back(std::stoi(token));
        }
    }

    return tokens;
}

int main(int argc, char *argv[]) {
    std::cout << "----- Day 4: Scratchcards (Part 1) -----\n\n";

    std::ifstream input(utils::get_input_path(argc, argv));
    std::string line;
    int total_score = 0;

    while (getline(input, line)) {
        std::cout << line << std::endl;

        // tokenise numbers
        std::vector<int> winning = tokenise(line.substr(
            line.find(':') + 2, line.find('|') - line.find(':') - 2));
        std::vector<int> numbers = tokenise(line.substr(
            line.find('|') + 2, line.length() - line.find('|') - 2));

        std::cout << "-> Matches: ";

        // check for matches
        int score = 0;
        for (auto &win : winning) {
            for (auto &num : numbers) {
                if (win == num) {
                    // +1 for first match, *2 after
                    (score == 0) ? score++ : score *= 2;
                    std::cout << win << " ";
                }
            }
        }

        // sum all scores
        total_score += score;

        if (score == 0)
            std::cout << "None\n" << std::endl;
        else
            std::cout << "(Score = " << score << ")\n" << std::endl;
    }

    std::cout << "--------------\nTotal score: " << total_score << std::endl;
    return 0;
}