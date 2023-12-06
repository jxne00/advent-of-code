// UNSOLVED
#include "../utils/common.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
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

int getCardNumber(const std::string &card) {
    // tokenise card number
    std::string card_str = card.substr(card.find("Card") + 4, card.find(':'));

    // remove spaces and convert to int
    int number = std::stoi(card_str.substr(
        card_str.find_first_not_of(' '),
        card_str.find_last_not_of(' ') - card_str.find_first_not_of(' ') + 1));

    return number;
}

int main(int argc, char *argv[]) {
    std::cout << "----- Day 4: Scratchcards (Part 2) -----\n\n";

    std::ifstream input(utils::get_input_path(argc, argv));
    std::vector<std::string> scratchcards;
    std::queue<std::string> cards_queue;

    std::string line;

    // get number of lines in input
    while (getline(input, line)) {
        scratchcards.push_back(line);
        cards_queue.push(line);
    }

    std::cout << "Unique cards: " << scratchcards.size() << "\n" << std::endl;

    // card numbers already passed
    std::unordered_set<int> passed_cards;

    int total_cards = 0;
    while (!cards_queue.empty()) {
        // get next card and remove from queue
        std::string card = cards_queue.front();
        cards_queue.pop();

        std::cout << card << std::endl;

        // tokenise numbers
        std::vector<int> winning = tokenise(card.substr(
            card.find(':') + 2, card.find('|') - card.find(':') - 2));
        std::vector<int> numbers = tokenise(card.substr(card.find('|') + 2));

        // count number of matches
        int match_count = 0;
        for (int win_num : winning) {
            for (int num : numbers) {
                if (win_num == num) {
                    match_count++;
                    break;
                }
            }
        }
        std::cout << "-> " << match_count << " matches\n" << std::endl;

        total_cards++;

        // get the current card number
        int card_number = getCardNumber(card);

        // skip if card has already been processed
        if (passed_cards.find(card_number) != passed_cards.end()) {
            continue;
        }
        passed_cards.insert(card_number);

        // add copy of subsequent "match_count" cards to queue
        for (int i = 1; i <= match_count; i++) {
            size_t next_pos = card_number + i - 1;
            if (next_pos < scratchcards.size()) {
                int next_card = getCardNumber(scratchcards[next_pos]);
                if (passed_cards.find(next_card) == passed_cards.end()) {
                    cards_queue.push(scratchcards[next_pos]);
                }
            }
        }
    }
    std::cout << "--------------\nTotal cards: " << total_cards << std::endl;
    return 0;
}