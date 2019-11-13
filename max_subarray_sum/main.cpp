#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

template <class T>
T max_subarray_sum(const vector<vector<T>>& queries) {
    vector<pair<size_t, T>> v;
    for (const auto& q : queries) {
        v.emplace_back(q[0], q[2]);
        v.emplace_back(q[1], -q[2]);
    }
    sort(v.begin(), v.end(), [](const auto& x1, const auto& x2) { return x1.first < x2.first; });
    T max = numeric_limits<T>::min();
    T sum = 0;
    for (const auto& x : v) {
        sum += x.second;
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}

int main() {
    // from, to, value
    vector<vector<long>> queries {
        {2, 6, 8},
        {3, 5, 7},
        {1, 8, 1},
        {5, 9, 15}
    };
    cerr << max_subarray_sum<long>(queries) << endl;
}
