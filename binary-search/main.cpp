#include <iostream>
#include <vector>

#include "binary_search.hpp"

// Optional demo driver for this subproject (run with: task run -- binary-search).
int main() {
    std::vector<int> data{1, 3, 5, 7, 9, 11};
    for (int target : {7, 8}) {
        auto idx = algo::binary_search(data, target);
        if (idx)
            std::cout << target << " found at index " << *idx << '\n';
        else
            std::cout << target << " not found\n";
    }
    return 0;
}
