#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "secret_number.hpp"

// Reads two lines of input:
//   line 1: n            -- number of messages
//   line 2: v1,v2,v3,... -- the messages, comma-separated (spaces are allowed)
//
// Source: "input.txt" next to this subproject's executable (i.e. inside
// secret_number/); if that file is missing, falls back to standard input.
// Prints the resulting secret number.
//
// Example:
//   3
//   21, 35, 28
// -> 7
int main(int argc, char** argv) {
    // input.txt is looked up next to the executable, which lives in
    // secret_number/ -- so it works regardless of the current directory.
    std::ifstream file;
    if (argc > 0) {
        std::filesystem::path exe_dir =
            std::filesystem::absolute(argv[0]).parent_path();
        file.open(exe_dir / "input.txt");
    }
    
    std::istream& in = file.is_open() ? file : std::cin;
    if (!file.is_open()) {
         std::cout << "Enter your values:" << std::endl;
    }

    std::string line_n;
    if (!std::getline(in, line_n)) {
        std::cerr << "error: expected n on the first line\n";
        return 1;
    }
    std::size_t n;
    try {
        n = std::stoull(line_n);
    } catch (const std::exception&) {
        std::cerr << "error: first line must be a number (n), got: " << line_n << '\n';
        return 1;
    }

    std::string line_values;
    std::getline(in, line_values);
    for (char& c : line_values) {
        if (c == ',') c = ' ';  // treat commas as separators
    }

    std::vector<long long> messages;
    std::istringstream iss(line_values);
    for (long long value; iss >> value;) {
        messages.push_back(value);
    }

    if (messages.empty()) {
        std::cerr << "error: expected comma-separated numbers on the second line\n";
        return 1;
    }

    std::cout << algo::secret_number(n, messages) << '\n';
    return 0;
}
