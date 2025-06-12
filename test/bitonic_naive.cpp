#include <iostream>

#include <openssl/rand.h>
#include <parlay/sequence.h>

#include "bitonic.h"

int main(int argc, char *argv[]) {
    // Generate random values
    const size_t n = 16;
    const size_t range = 1000;
    auto arr = parlay::sequence<int>::uninitialized(n);
    if (RAND_bytes(reinterpret_cast<unsigned char *>(arr.data()), n * sizeof(int)) != 1) {
        std::cerr << "Error generating random bytes." << std::endl;
        return 1;
    }
    parlay::parallel_for(0, n, [&](size_t i) {
        arr[i] = (arr[i] % range + range) % range;
    });

    // Sort the array using bitonic sort
    bitonic_sort_naive(arr);

    // Verify that the array is sorted
    for (size_t i = 1; i < n; ++i) {
        if (arr[i - 1] > arr[i]) {
            std::cerr << "Array is not sorted" << std::endl;
            return 1;
        }
    }
    std::cout << "Array is sorted successfully" << std::endl;

    return 0;
}