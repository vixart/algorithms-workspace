#include "doctest.h"

#include "solution.hpp"

// Test files must be named *_test.cpp and only #include "doctest.h"
// (main() is provided by common/doctest_main.cpp).
TEST_CASE("add sums two numbers") {
    CHECK(algo::add(2, 3) == 5);
    CHECK(algo::add(-1, 1) == 0);
}
