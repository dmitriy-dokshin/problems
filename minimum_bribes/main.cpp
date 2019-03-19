#include <iostream>
#include <tuple>
#include <type_traits>
#include <vector>
#include <utility>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << " " << v[i];
        }
    }
    return out;
}

template <class T>
bool minimumBribes(vector<T>& v, size_t& result, size_t maxBribes = 2) {
    static_assert(numeric_limits<T>::is_integer, "Integer type required");

    vector<size_t> bribes(v.size());
    bool bribed;
    do {
        bribed = false;
        for (size_t i = 0; i < v.size() - 1; i++) {
            if (v[i] > v[i + 1]) {
                bribes[v[i] - 1]++;
                swap(v[i], v[i + 1]);
                bribed = true;
            }
        }
    } while (bribed);

    cerr << bribes << endl;

    size_t bribesSum = 0;
    for (const auto& x : bribes) {
        if (x > maxBribes) {
            return false;
        }
        bribesSum += x;
    }

    result = bribesSum;
    return true;
}

int main() {
    vector<tuple<vector<int>, bool, size_t>> tests {
        {{2, 1, 5, 3, 4}, true, 3},
        {{2, 5, 1, 3, 4}, false, 0}
    };

    for (auto& x : tests) {
        size_t result = 0;
        cerr << get<0>(x) << endl;
        const bool ok = minimumBribes(get<0>(x), result) == get<1>(x) && result == get<2>(x);
        cerr << get<0>(x) << endl;
        cerr << (ok ? "OK" : "ERROR") << endl;
    }
}
