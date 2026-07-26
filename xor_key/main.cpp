#include <ios>       // std::streamsize
#include <iostream>
#include <limits>    // std::numeric_limits
#include <string>
#include <vector>

#include "xor_key.hpp"

int main() {
    unsigned int key_length, messages_number;
    std::cout << "Enter key length and messages number:" << std::endl;
    if (!(std::cin >> key_length >> messages_number)) {
        std::cerr << "error: expected two numbers\n";
        return 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter handshake string:" << std::endl;
    std::string handshake;
    getline(std::cin, handshake);

    std::cout << "Enter ciphertexts:" << std::endl;
    std::vector<std::string> ciphertexts(messages_number);
    for (auto& t : ciphertexts) {
        getline(std::cin, t);
    }

    std::string key = algo::find_key(key_length, handshake, ciphertexts[0]);
    for (auto& t : ciphertexts) {
        std::cout << algo::decipher_text(key, t) << std::endl;
    }
    
    return 0;
}
