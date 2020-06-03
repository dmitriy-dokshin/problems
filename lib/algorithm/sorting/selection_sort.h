#include <utility>
#include <vector>

template <class T>
void selection_sort(std::vector<T>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < v.size(); j++) {
            if (v[j] < v[min_index]) {
                min_index = j;
            }
        }
        std::swap(v[i], v[min_index]);
    }
}
