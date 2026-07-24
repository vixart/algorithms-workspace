#include "doctest.h"

// The algorithm lives in main.cpp together with the demo's main(). We pull it in
// here with the main() guarded out, so the tests run against the very same code
// (no separate header). main() for the test runner comes from doctest_main.cpp.
#define SECRET_NUMBER_SIMPLE_NO_MAIN
#include "main.cpp"

TEST_CASE("max_prime_factor returns the largest prime divisor") {
    CHECK(algo::max_prime_factor(7) == 7);
    CHECK(algo::max_prime_factor(6) == 3);   // 2 * 3
    CHECK(algo::max_prime_factor(12) == 3);  // 2^2 * 3
    CHECK(algo::max_prime_factor(2) == 2);
    CHECK(algo::max_prime_factor(4) == 2);   // 2^2
}

TEST_CASE("secret_number = gcd of messages, then its largest prime factor") {
    CHECK(algo::secret_number(3, {21, 35, 28}) == 7);  // gcd=7  -> 7
    CHECK(algo::secret_number(3, {12, 18, 24}) == 3);  // gcd=6  -> 3
    CHECK(algo::secret_number(2, {8, 12}) == 2);       // gcd=4  -> 2
}
