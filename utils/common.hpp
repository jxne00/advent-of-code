#ifndef UTILS_COMMON_HPP
#define UTILS_COMMON_HPP

#include <iostream>
#include <string>

namespace utils {
    // get input file path from command line arguments
    std::string get_input_path(int argc, char* argv[]) {
        if (argc < 2) {
            std::cout << "Usage: ./a.out <input_file.txt>" << std::endl;
            exit(1);
        }
        else if (argc > 2) {
            std::cout << "Too many arguments." << std::endl;
            exit(1);
        }
        else {
            // path: ./inputs/<filename>
            std::string filename = argv[1];
            return "./inputs/" + filename;
        }
        return "";
    }
}

#endif // UTILS_COMMON_HPP