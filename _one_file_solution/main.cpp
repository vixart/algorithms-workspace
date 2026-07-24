// secret_number (single-file variant): the algorithm AND main() live together
// here, with no separate header. The unit tests #include THIS file (with the
// main() guarded out) so they exercise exactly the same code -- see
// secret_number_test.cpp.
//
//   task run  -- secret_number_simple   # build & run the demo below
//   task test -- secret_number_simple   # build & run the unit tests
//
// Idea: take the gcd of all messages, then the largest prime factor of that gcd.

#include <cstddef>
#include <numeric>
#include <vector>

namespace algo {

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

// n должно совпадать с числом элементов в messages.
long long secret_number(std::size_t n, const std::vector<long long>& messages) {
    long long messages_gcd = messages.front();
    for (std::size_t i = 1; i < n; ++i) {
        messages_gcd = std::gcd(messages_gcd, messages[i]);
    }
    return max_prime_factor(messages_gcd);
}

}  // namespace algo

// The demo driver below is compiled only for `task run`. The tests define
// SECRET_NUMBER_SIMPLE_NO_MAIN before including this file so this main() is
// skipped and doesn't clash with the doctest runner's own main().
#ifndef SECRET_NUMBER_SIMPLE_NO_MAIN

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Reads two lines of input:
//   line 1: n            -- number of messages
//   line 2: v1,v2,v3,... -- the messages, comma-separated (spaces are allowed)
//
// Source: "input.txt" next to this subproject's executable (i.e. inside
// secret_number_simple/); if that file is missing, falls back to standard input.
// Prints the resulting secret number.
//
// Example:
//   3
//   21, 35, 28
// -> 7
int main(int argc, char** argv) {
    // input.txt is looked up next to the executable, so it works regardless of
    // the current directory.
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

#endif  // SECRET_NUMBER_SIMPLE_NO_MAIN
