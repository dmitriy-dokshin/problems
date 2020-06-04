#include <functional>
#include <utility>
#include <vector>

template <class T, class TComp>
size_t find_bound(const std::vector<T>& v, const T& value, size_t begin, size_t end, TComp comp = {}) {
    if (begin < end) {
        size_t mid = begin + (end - begin) / 2;
        if (comp(v[mid], value)) {
            return find_bound(v, value, mid + 1, end, comp);
        } else {
            return find_bound(v, value, begin, mid, comp);
        }
    } else {
        return begin;
    }
}

template <class T>
size_t lower_bound(const std::vector<T>& v, const T& value) {
    return find_bound<T, std::less<T>>(v, value, 0, v.size());
}

template <class T>
size_t upper_bound(const std::vector<T>& v, const T& value) {
    return find_bound<T, std::less_equal<T>>(v, value, 0, v.size());
}

template <class T>
std::pair<size_t, size_t> binary_search(const std::vector<T>& v, const T& value) {
    return {lower_bound(v, value), upper_bound(v, value)};
}
