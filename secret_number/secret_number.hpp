#pragma once
#include <cstddef>
#include <numeric>
#include <vector>

// secret_number: сначала берём НОД (gcd) всех сообщений,
// затем возвращаем наибольший простой делитель этого НОД.
namespace algo {

inline long long max_prime_factor(long long n) {
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
inline long long secret_number(std::size_t n, std::vector<long long> messages) {
    long long messages_gcd = messages.front();
    for (std::size_t i = 1; i < n; ++i) {
        messages_gcd = std::gcd(messages_gcd, messages[i]);
    }
    return max_prime_factor(messages_gcd);
}

}  // namespace algo
