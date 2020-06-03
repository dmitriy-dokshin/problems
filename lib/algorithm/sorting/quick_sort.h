#include <utility>
#include <vector>

template <class T>
void quick_sort_impl(std::vector<T>& v, size_t begin, size_t end) {
    if (end - begin > 1) {
        size_t pivot = begin + (end - begin) / 2;
        std::swap(v[begin], v[pivot]);
        size_t j = begin + 1;
        for (size_t i = begin + 1; i < end; i++) {
            if (v[i] < v[begin]) {
                std::swap(v[i], v[j++]);
            }
        }
        std::swap(v[begin], v[j - 1]);
        quick_sort_impl(v, begin, j - 1);
        quick_sort_impl(v, j, end);
    }
}

// Average: O(n*log(n)), worst case: O(n^2), memory: O(log(n)) (stack)
template <class T>
void quick_sort(std::vector<T>& v) {
    quick_sort_impl(v, 0, v.size());
}
