#pragma once
#include <cstddef>
#include <optional>
#include <vector>

// Classic iterative binary search over a sorted (ascending) vector.
// Returns the index of `target` if present, std::nullopt otherwise.
namespace algo {

inline std::optional<std::size_t> binary_search(const std::vector<int>& sorted, int target) {
    std::size_t lo = 0;
    std::size_t hi = sorted.size();
    while (lo < hi) {
        std::size_t mid = lo + (hi - lo) / 2;
        if (sorted[mid] == target) return mid;
        if (sorted[mid] < target) lo = mid + 1;
        else hi = mid;
    }
    return std::nullopt;
}

}  // namespace algo
