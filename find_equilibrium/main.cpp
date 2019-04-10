#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <utility>

using namespace std;

template <class T>
size_t FindEquilibrium(vector<T>& v) {
    static_assert(is_arithmetic<T>::value, "Type has to be arithmetic");

    if (v.size() == 1) {
        return 0;
    }

    for (size_t i = 1; i < v.size(); i++) {
        v[i] += v[i - 1];
    }

    for (size_t i = 1; i < v.size() - 1; i++) {
        if (v[i - 1] == v.back() - v[i]) {
            return i;
        }
    }

    throw runtime_error("Unable to find equilibrium");
}

template <class T>
size_t FindEquilibrium(const vector<T>& v) {
    static_assert(is_arithmetic<T>::value, "Type has to be arithmetic");

    T rightSum = {};
    T leftSum = {};
    for (const auto& x : v) {
        rightSum += x;
    }

    for (size_t i = 0; i < v.size(); i++) {
        rightSum -= v[i];
        if (leftSum == rightSum) {
            return i;
        }
        leftSum += v[i];
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
