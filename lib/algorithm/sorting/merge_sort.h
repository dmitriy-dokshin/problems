#include <vector>

template <class T>
void merge(std::vector<T>& v, std::vector<T>& tmp, size_t begin, size_t mid, size_t end) {
    size_t i = begin;
    size_t j = mid;
    size_t k = begin;
    while (i < mid && j < end) {
        if (v[i] < v[j]) {
            tmp[k++] = std::move(v[i++]);
        } else {
            tmp[k++] = std::move(v[j++]);
        }
    }
    while (i < mid) {
        tmp[k++] = std::move(v[i++]);
    }
    while (j < end) {
        tmp[k++] = std::move(v[j++]);
    }
    for (i = begin; i < end; i++) {
        v[i] = std::move(tmp[i]);
    }
}

template <class T>
void merge_sort_impl(std::vector<T>& v, std::vector<T>& tmp, size_t begin, size_t end) {
    if (end - begin > 1) {
        size_t mid = begin + (end - begin) / 2;
        merge_sort_impl(v, tmp, begin, mid);
        merge_sort_impl(v, tmp, mid, end);
        merge(v, tmp, begin, mid, end);
    }
}

// O(n*log(n)), memory: O(n)
template <class T>
void merge_sort(std::vector<T>& v) {
    std::vector<T> tmp;
    tmp.resize(v.size());
    merge_sort_impl(v, tmp, 0, v.size());
}
