#pragma once

#include <cstdint>
#include <utility>

enum class Dir {
    Asc, Desc
};

template <typename T>
void try_swap(T &a, T &b, Dir dir) {
    if ((dir == Dir::Asc && a > b) || (dir == Dir::Desc && a < b)) {
        std::swap(a, b);
    }
}

// Assume for now that we want to sort in ascending order
// Standard sequential bitonic sort implementation
template <typename Range>
void bitonic_sort_seq(Range &arr) {
    for (size_t block_size = 2; block_size <= arr.size(); block_size *= 2) {
        for (size_t stride = block_size / 2; stride > 0; stride /= 2) {
            for (size_t i = 0; i < arr.size(); i++) {
                size_t j = i ^ stride; // Bitwise XOR to find the partner index
                if (j > i) {
                    bool ascending = ((i & block_size) == 0);
                    try_swap(arr[i], arr[j], ascending ? Dir::Asc : Dir::Desc);
                }
            }
        }
    }
}