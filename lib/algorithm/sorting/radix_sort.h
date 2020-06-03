#include <climits>
#include <vector>

template <class T>
void radix_sort_impl(std::vector<T>& v, std::vector<T>& tmp, size_t bit_index, size_t begin, size_t end) {
    size_t mid = end;
    for (size_t i = begin; i < end; i++) {
        const T mask = static_cast<T>(1) << bit_index;
        if (mask & v[i]) {
            mid--;
        }
    }

    size_t j = begin;
    size_t k = mid;
    for (size_t i = begin; i < end; i++) {
        const T mask = static_cast<T>(1) << bit_index;
        if (mask & v[i]) {
            tmp[k++] = std::move(v[i]);
        } else {
            tmp[j++] = std::move(v[i]);
        }
    }

    for (size_t i = begin; i < end; i++) {
        v[i] = std::move(tmp[i]);
    }

    if (bit_index > 0) {
        if (begin < mid) {
            radix_sort_impl(v, tmp, bit_index - 1, begin, mid);
        }
        if (mid < end) {
            radix_sort_impl(v, tmp, bit_index - 1, mid, end);
        }
    }
}

// O(k*n), memory: O(k + n)
template <class T>
void radix_sort(std::vector<T>& v) {
    std::vector<T> tmp;
    tmp.resize(v.size());
    radix_sort_impl(v, tmp, sizeof(T) * CHAR_BIT - 1, 0, v.size());
}
