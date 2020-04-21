#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <utility>

using namespace std;

template <class T>
size_t maxConsecutive1(T value, string* s = nullptr) {
    static_assert(numeric_limits<T>::is_integer && !numeric_limits<T>::is_signed, "Invalid type");

    size_t cur = 0;
    size_t max = 0;
    for (size_t i = 0; value / (1 << i) > 0; i++) {
        if (value % (1 << (i + 1)) == (1 << i)) {
            cur++;
            value -= 1 << i;
            if (s) {
                *s += '1';
            }
        } else {
            cur = 0;
            if (s) {
                *s += '0';
            }
        }

        if (cur > max) {
            max = cur;
        }
    }

    if (s) {
        reverse(s->begin(), s->end());
    }

    return max;
}

int main() {
    vector<pair<unsigned int, size_t>> tests {
        {5, 1},
        {13, 2},
        {99, 2},
        {128, 1}
    };

    for (const auto& x : tests) {
        string s;
        const bool ok = maxConsecutive1(x.first, &s) == x.second;
        cerr << (ok ? "OK" : "ERROR") << "\t" << x.first << "\t" << s << endl;;
    }
}
