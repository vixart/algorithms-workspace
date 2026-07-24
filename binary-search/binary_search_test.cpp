#include "doctest.h"

#include "binary_search.hpp"

using algo::binary_search;
using Idx = std::optional<std::size_t>;

TEST_CASE("finds elements that are present") {
    std::vector<int> v{1, 3, 5, 7, 9, 11};
    CHECK(binary_search(v, 1) == Idx(0));
    CHECK(binary_search(v, 7) == Idx(3));
    CHECK(binary_search(v, 11) == Idx(5));
}

TEST_CASE("reports missing elements as nullopt") {
    std::vector<int> v{1, 3, 5, 7, 9, 11};
    CHECK(binary_search(v, 0) == std::nullopt);
    CHECK(binary_search(v, 4) == std::nullopt);
    CHECK(binary_search(v, 12) == std::nullopt);
}

TEST_CASE("handles edge cases") {
    CHECK(binary_search(std::vector<int>{}, 5) == std::nullopt);
    CHECK(binary_search(std::vector<int>{42}, 42) == Idx(0));
    CHECK(binary_search(std::vector<int>{42}, 7) == std::nullopt);
}
