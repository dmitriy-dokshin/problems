#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "{";
    if (v.size() > 0) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << ", " << v[i];
        }
    }
    out << "}";
    return out;
}

template <class T>
vector<T> Bonetrousle(T n, T k, T sum) {
    static_assert(is_integral<T>::value && is_unsigned<T>::value, "Type has to be integral and unsigned");

    if (k > n) {
        throw runtime_error("Unable to get enough numbers");
    }

    T sMin = k * (k + 1) / 2;
    T sMax = k * n - k * (k - 1) / 2;
    if (sum < sMin || sum > sMax) {
        throw runtime_error("Unable to get numbers for required sum");
    }

    T sDiff = sum - sMin;
    vector<T> result;
    result.reserve(k);
    for (T i = 0; i < k - sDiff % k; i++) {
        T val = i + 1 + sDiff / k;
        result.emplace_back(val);
    }
    for (T i = k - sDiff % k; i < k; i++) {
        T val = i + 1 + sDiff / k + 1;
        result.emplace_back(val);
    }

    return result;
}

int main() {
    auto result = Bonetrousle<unsigned int>(8, 3, 12);
    cerr << result << endl;
}
