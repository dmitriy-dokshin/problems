#include <algorithm>
#include <functional>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "{";
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << ", " << v[i];
        }
    }
    out << "}";
    return out;
}

template <class T, class C>
size_t MinSwaps(vector<T> v, C compare) {
    auto tmp = v;
    sort(tmp.begin(), tmp.end(), compare);
    size_t swaps = 0;
    for (size_t i = 0; i < v.size(); i++) {
        bool swapped;
        do {
            swapped = false;
            const auto r = equal_range(tmp.begin(), tmp.end(), v[i], compare);
            size_t j = r.first - tmp.begin();
            if (i != j) {
                swapped = true;
                swaps++;
                swap(v[i], v[j]);
            }
        } while (swapped);
    }
    return swaps;
}

template <class T>
size_t MinSwaps(const vector<T>& v) {
    return min(MinSwaps(v, less<T>()), MinSwaps(v, greater<T>()));
}

int main() {
    vector<int> v {3, 4, 2, 5, 1};
    cerr << v << endl;
    cerr << MinSwaps(v) << endl;
}
