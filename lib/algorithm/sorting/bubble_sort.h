#pragma once

#include <utility>
#include <vector>

// O(n^2), memory: O(1)
template <class T>
void bubble_sort(std::vector<T>& v) {
    bool swapped;
    do {
        swapped = false;
        for (size_t i = 1; i < v.size(); i++) {
            if (v[i] < v[i - 1]) {
                std::swap(v[i], v[i - 1]);
                swapped = true;
            }
        }
    } while (swapped);
}
