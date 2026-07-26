#include <cstddef>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "validate_token.hpp"

int main() {
    std::string line_n;
    std::getline(std::cin, line_n);

    std::size_t n;
    try {
        n = std::stoull(line_n);
    } catch (const std::exception&) {
        std::cerr << "error: first line must be a number (n), got: " << line_n << '\n';
        return 1;
    }

    std::vector<std::string> tokens(n);
    for (auto& t : tokens) {
        std::getline(std::cin, t);
    }

    for (std::string token : tokens) {
        if (algo::validate_token(token)) {
            std::cout << "VALID" << std::endl;
        } else {
            std::cout << "INVALID" << std::endl;
        }
    }

    return 0;
}
