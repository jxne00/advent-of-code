#!/bin/bash

# -------------------
# USAGE: ./run.sh <path/to/cpp_file> <input_file>
# EXAMPLE: ./run.sh day1/part1 input
# -------------------

# check if source and input files are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <path/to/cppfile> <input_filename>"
    exit 1
fi

SOURCE_FILE="$1.cpp"
INPUT_FILE="$2.txt"

SOURCE_DIR=$(dirname "$SOURCE_FILE")        # directory of .cpp file
SOURCE_BASENAME=$(basename "$SOURCE_FILE")  # .cpp file name

EXECUTABLE_FILE="${SOURCE_DIR}/${SOURCE_BASENAME%.*}.out"

OUTPUT_DIR="${SOURCE_DIR}/outputs"
OUTPUT_FILE="outputs/${SOURCE_BASENAME%.*}_output.txt"

# compile c++ program
echo "... clang++ -std=c++20 -Wall -Wextra -Werror $SOURCE_FILE -o $EXECUTABLE_FILE"
clang++ -std=c++20 -Wall -Wextra -Werror "$SOURCE_FILE" -o "$EXECUTABLE_FILE"  || exit 1

# create "output" directory if not exist
mkdir -p "$OUTPUT_DIR"

echo "++++++++++++++++++++++++++++++++++++++"

# go to source directory and run executable
cd "$SOURCE_DIR" || exit 1

# run executable with input file
"./${SOURCE_BASENAME%.*}.out" "$INPUT_FILE"

# save output to file
"./${SOURCE_BASENAME%.*}.out" "$INPUT_FILE" > "$OUTPUT_FILE"

# clean output file
rm "${SOURCE_BASENAME%.*}.out"
