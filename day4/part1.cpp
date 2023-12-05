#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> tokenise(const std::string& str) {
    std::vector<int> tokens;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, ' ')) {
        if (!token.empty()) {
            tokens.push_back(std::stoi(token));
        }
    }

    return tokens;
}

int main() {
    std::cout << "----- Day 4: Scratchcards (Part 1) -----\n\n";

    std::ifstream input("input.txt");
    std::string line;
    int total_score = 0;

    while (std::getline(input, line)) {
        std::cout << line << std::endl;

        // tokenise numbers
        std::vector<int> winning = tokenise(line.substr(
            line.find(':') + 2,
            line.find('|') - line.find(':') - 2
        ));
        std::vector<int> numbers = tokenise(line.substr(
            line.find('|') + 2,
            line.length() - line.find('|') - 2
        ));

        std::cout << "-> Matches: ";

        // check for matches
        int score = 0;
        for (int i = 0; i < winning.size(); i++) {
            for (int j = 0; j < numbers.size(); j++) {
                if (winning[i] == numbers[j]) {
                    // +1 for first match, *2 after
                    (score == 0) ? score++ : score *= 2;
                    std::cout << winning[i] << " ";
                }
            }
        }

        // sum all scores
        total_score += score;

        if (score == 0) std::cout << "None\n" << std::endl;
        else std::cout << "(Score = " << score << ")\n" << std::endl;
    }

    std::cout << "--------------\nTotal score: " << total_score << std::endl;
    return 0;
}