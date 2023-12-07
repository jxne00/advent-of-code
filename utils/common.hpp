#ifndef UTILS_COMMON_HPP
#define UTILS_COMMON_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace utils {
// get input file path from command line arguments
std::string get_input_path(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./a.out <input_file.txt>" << std::endl;
        exit(1);
    } else if (argc > 2) {
        std::cout << "Too many arguments." << std::endl;
        exit(1);
    } else {
        // path: ./inputs/<filename>
        std::string filename = argv[1];
        return "./inputs/" + filename;
    }
    return "";
}

// tokenise a string by whitespace
std::vector<std::string> tokenise(std::string str) {
    std::istringstream iss(str);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// print contents of a vector
template <typename T> void print_vector(std::vector<T> vec) {
    for (auto &elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

} // namespace utils

#endif // UTILS_COMMON_HPP