#include "../utils/common.hpp"
#include <algorithm> // remove_if
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

// Node: <left, right>
using Node = std::pair<std::string, std::string>;

bool to_remove(char c) { return c == ',' || c == '(' || c == ')' || c == '='; }

int main(int argc, char *argv[]) {
    std::cout << "----- Day 8: Haunted Wasteland (Part 1) -----\n" << std::endl;

    std::ifstream input(utils::get_input_path(argc, argv));
    std::string line;

    std::string instructions, start_node, end_node;
    std::unordered_map<std::string, Node> network;

    // get instructions
    std::getline(input, instructions);

    while (std::getline(input, line)) {
        if (!line.empty()) {

            // remove not needed chars
            line.erase(std::remove_if(line.begin(), line.end(), to_remove),
                       line.end());

            std::istringstream iss(line);
            std::string node, left, right;

            // get values
            iss >> node >> left >> right;

            // add node to network
            if (!node.empty() && !left.empty() && !right.empty()) {
                network[node] = {left, right};

                if (start_node.empty()) {
                    start_node = node;
                } else {
                    end_node = node;
                }
            } else {
                return 1;
            }
        }
    }
    // print start and end nodes
    std::cout << "\nStart node: " << start_node << std::endl;
    std::cout << "End node: " << end_node << std::endl;

    std::string current_node = start_node;
    int steps = 0;

    std::cout << "\nPath:" << std::endl;

    // traverse network based on L/R instructions
    while (current_node != end_node) {
        for (char direction : instructions) {
            std::cout << current_node << " -> ";

            // get next element
            current_node = (direction == 'L') ? network[current_node].first
                                              : network[current_node].second;
            steps++;

            // destination reached
            if (current_node == end_node) {
                std::cout << end_node << "\n\nSteps taken = " << steps
                          << std::endl;
                return 0;
            }
        }
    }

    return 0;
}