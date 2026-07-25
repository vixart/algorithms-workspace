#include "doctest.h"

#include "validate_token.hpp"

TEST_CASE("first set of tokens") {
    CHECK(algo::validate_token("4539-1488-0343-6467") == true);
    CHECK(algo::validate_token("8273 1232 7352 0569") == false);
    CHECK(algo::validate_token("79927398713") == true);
    CHECK(algo::validate_token("1234-5678-9012-345a") == false);
}

TEST_CASE("second set of tokens") {
    CHECK(algo::validate_token("0") == true);
    CHECK(algo::validate_token("18") == true);
    CHECK(algo::validate_token("26") == true);
    CHECK(algo::validate_token("59") == true);
    CHECK(algo::validate_token("00") == true);
}
