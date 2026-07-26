#pragma once
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <string>

// validate_token: убираем разделители ('-' и пробел), проверяем, что остались
// только цифры, и подтверждаем контрольную сумму по алгоритму Луна (Luhn).
namespace algo {

inline std::string remove_special_characters(std::string str) {
    str.erase(
        std::remove_if(
            str.begin(),
            str.end(),
            [](char c) {
                return c == ' ' || c == '-';
            }
        ),
        str.end()
    );

    return str;
}

inline bool is_digits_only(std::string str)  {
    bool is_not_empty = str.length() > 0;
    bool is_digits_only = std::all_of(str.begin(), str.end(), ::isdigit);
    return is_not_empty && is_digits_only;
}

inline bool check_luhn_algorithm_is_valid(std::string str) {
    std::size_t i = 0;
    unsigned int total = 0;
    for (auto it = str.rbegin(); it != str.rend(); ++it, ++i) {
        unsigned int x = *it - '0';
        if (i % 2 != 0) {
            x *= 2;
            if (x > 9) {
                x -= 9;
            }
        }
        total += x;
    }

    return total % 10 == 0 ? true : false;
}

inline bool validate_token(std::string token) {
    std::string trimed_token = remove_special_characters(token);
    if (is_digits_only(trimed_token) == false) {
        return false;
    }
    return check_luhn_algorithm_is_valid(trimed_token);
}

}  // namespace algo
