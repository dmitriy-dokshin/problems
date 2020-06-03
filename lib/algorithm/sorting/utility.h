#include <vector>

// O(n^2), memory: O(1)
template <class T>
bool is_sorted(const std::vector<T>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < v[i - 1]) {
            return false;
        }
    }
    return true;
}
