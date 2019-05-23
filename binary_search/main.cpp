#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <class T1, class T2>
ostream& operator<<(ostream& out, const pair<T1, T2>& p) {
    out << "{" << p.first << ", " << p.second << "}";
    return out;
}

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
size_t UpperBound(const vector<T>& v, const T& val) {
    if (v.empty()) {
        return 0;
    }

    size_t begin = 0;
    size_t end = v.size();
    while (end - begin > 1) {
        size_t i = (begin + end) / 2;
        if (val < v[i]) {
            end = i;
        } else {
            begin = i;
        }
    }

    return val < v[begin] ? begin : end;
}

template <class T>
size_t LowerBound(const vector<T>& v, const T& val) {
    if (v.empty()) {
        return 0;
    }

    size_t begin = 0;
    size_t end = v.size();
    while (end - begin > 1) {
        size_t i = (begin + end) / 2;
        if (v[i] < val) {
            begin = i;
        } else {
            end = i;
        }
    }

    return v[begin] < val ? end : begin;
}

template <class T>
pair<size_t, size_t> BinarySearch(const vector<T>& v, const T& val) {
    return {LowerBound(v, val), UpperBound(v, val)};
}

int main() {
    vector<int> v {1, 4, 4, 4, 4, 4, 5, 7, 9, 12};
    vector<pair<int, pair<size_t, size_t>>> tests {
        {4, {1, 6}},
        {0, {0, 0}},
        {13, {10, 10}},
        {6, {7, 7}}
    };

    for (const auto& x : tests) {
        auto bs = BinarySearch(v, x.first);
        if (x.second == bs) {
            cerr << "OK" << endl;
        } else {
            cerr << "ERROR: " << bs << endl;
        }
    }
}
