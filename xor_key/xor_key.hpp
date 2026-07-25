#pragma once
#include <string>
#include <stdexcept>

namespace algo {

inline std::string hex_to_bytes(std::string& hex) {
    if (hex.size() % 2 != 0) {
        throw std::invalid_argument("hex string must have even length");
    }

    std::string bytes;
    for (std::size_t i = 0; i < hex.size(); i += 2) {
        std::string byte_str = hex.substr(i, 2);
        unsigned int byte_val = std::stoul(byte_str, nullptr, 16);
        bytes.push_back(static_cast<char>(byte_val));
    }

    return bytes;
}

inline std::string xor_strings(std::string str1, std::string str2, size_t n) {
    std::string result;
    for (size_t i = 0; i < n; ++i) {
        result.push_back(str1[i] ^ str2[i]);
    }

    return result;
}

inline std::string find_key(size_t key_length, std::string handshake, std::string ciphertext) {
    std::string ciphered_handshake = ciphertext.substr(0, handshake.length() * 2);
    std::string ciphered_handshake_in_bytes = hex_to_bytes(ciphered_handshake);

    std::string xored = xor_strings(handshake, ciphered_handshake_in_bytes, key_length);

    // std::cout << "Debug: " << handshake << " " << ciphered_handshake << " \"" << ciphered_handshake_in_bytes.size() << "\" " << xored << std::endl;

    return xored;
}

inline std::string decipher_text(std::string key, std::string ciphertext) {
    std::string ciphertext_in_bytes = hex_to_bytes(ciphertext);
    
    std::string deciphered_text;
    deciphered_text.reserve(ciphertext_in_bytes.length());
    for (size_t i = 0; i < ciphertext_in_bytes.length(); ++i) {
        size_t j = i % key.length();
        deciphered_text.push_back(ciphertext_in_bytes[i] ^ key[j]);
    }

    return deciphered_text;
}

}  // namespace algo
