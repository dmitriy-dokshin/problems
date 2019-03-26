#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <utility>

using namespace std;

template <class T>
size_t FindEquilibrium(const vector<T>& v) {
    static_assert(is_arithmetic<T>::value, "Type has to be arithmetic");

    if (v.size() == 1) {
        return 0;
    }

    vector<T> left(v.begin(), v.end());
    for (size_t i = 1; i < v.size(); i++) {
        left[i] += left[i - 1];
    }

    vector<T> right(v.begin(), v.end());
    for (long i = v.size() - 2; i >= 0; i--) {
        right[i] += right[i + 1];
    }

    for (size_t i = 1; i < v.size() - 1; i++) {
        if (left[i - 1] == right[i + 1]) {
            return i;
        }
    }

    throw runtime_error("Unable to find equilibrium");
}

int main() {
    vector<pair<vector<long>, size_t>> tests {
        {{1, 3, 5, 2, 2}, 2}
    };
    for (const auto& x : tests) {
        const bool ok = FindEquilibrium(x.first) == x.second;
        cerr << (ok ? "OK" : "ERROR") << endl;
    }
}
