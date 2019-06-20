#include <cmath>
#include <ctime>
#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "{";
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << " " << v[i];
        }
    }
    out << "}";
    return out;
}

template <class T>
inline T GetDigit(const T& val, const size_t pos) {
    static_assert(is_integral<T>::value && is_unsigned<T>::value, "Unsupported type");

    const T bit = 1 << pos;
    return (val & bit) == bit;
}

template <class T>
void RadixSort(vector<T>& v) {
    static_assert(is_integral<T>::value && is_unsigned<T>::value, "Unsupported type");

    vector<T> tmp(v.size());
    for (size_t i = 0; i < sizeof(T) * 8; i++) {
        vector<size_t> radix(2);
        for (const auto& x : v) {
            radix[GetDigit(x, i)]++;
        }

        size_t begin = v.size(); 
        for (size_t i = radix.size(); i > 0; i--) {
            begin -= radix[i - 1];
            radix[i - 1] = begin;
        }

        for (const auto& x : v) {
            tmp[radix[GetDigit(x, i)]++] = x;
        }

        v = tmp;
    }
}

template <class T>
bool IsSorted(const vector<T>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        if (!(v[i - 1] < v[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(nullptr));

    size_t n = 10;
    vector<unsigned int> v;
    v.reserve(n);
    for (size_t i = 0; i < n; i++) {
        v.emplace_back(rand());
    }

    RadixSort(v);

    cerr << (IsSorted(v) ? "OK" : "ERROR") << endl;
}
