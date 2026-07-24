// Упрощённая, самодостаточная версия secret_number: читает ТОЛЬКО из stdin
// (без input.txt) и не подключает secret_number.hpp — вся логика здесь же.
//
// Собрать и запустить:
//   g++ -std=c++23 -O2 secret_number/simple_version.cpp -o secret_number/.simple.exe
//   echo "3
//   21, 35, 28" | secret_number/.simple.exe        # -> 7
//
// Формат ввода (две строки):
//   строка 1: n              -- количество сообщений
//   строка 2: v1, v2, v3 ... -- сами числа через запятую (пробелы допускаются)
//
// Идея: берём НОД (gcd) всех чисел, затем наибольший простой делитель этого НОД.

#include <cstddef>    // std::size_t
#include <iostream>   // std::cin, std::cout, std::cerr, std::getline
#include <numeric>    // std::gcd
#include <sstream>    // std::istringstream
#include <string>     // std::string
#include <vector>     // std::vector

long long max_prime_factor(long long n) {
    long long max_prime = -1;

    // Сначала вынимаем множители 2 и 3, чтобы дальше перебирать только
    // кандидатов вида 6k±1 (все простые >3 имеют такой вид) -- это в ~3 раза
    // меньше итераций, чем перебор всех подряд.
    while (n % 2 == 0) { max_prime = 2; n /= 2; }
    while (n % 3 == 0) { max_prime = 3; n /= 3; }

    // Условие i <= n / i эквивалентно i*i <= n, но без переполнения long long
    // (i*i для больших n вылезает за диапазон и ломает цикл).
    for (long long i = 5; i <= n / i; i += 6) {
        while (n % i == 0)       { max_prime = i;     n /= i; }
        while (n % (i + 2) == 0) { max_prime = i + 2; n /= i + 2; }
    }

    if (n > 1) {  // оставшийся n сам является простым делителем
        max_prime = n;
    }
    return max_prime;
}

long long secret_number(std::size_t n, const std::vector<long long>& messages) {
    long long messages_gcd = messages.front();
    for (std::size_t i = 1; i < n; ++i) {
        messages_gcd = std::gcd(messages_gcd, messages[i]);
    }
    return max_prime_factor(messages_gcd);
}

int main() {
    std::string line_n;
    if (!std::getline(std::cin, line_n)) {
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
    std::getline(std::cin, line_values);
    for (char& c : line_values) {
        if (c == ',') c = ' ';  // запятые считаем разделителями
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

    std::cout << secret_number(n, messages) << '\n';
    return 0;
}
