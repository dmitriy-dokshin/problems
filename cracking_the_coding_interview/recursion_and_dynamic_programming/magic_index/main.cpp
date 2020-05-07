#include <algorithm>
#include <iostream>
#include <string>
#include <random>
#include <stdexcept>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << "\t" << v[i];
        }
    }
    return out;
}

template <class T>
vector<T> build_input(const size_t n, const double add_prob, const double rep_prob, const T min_value, const typename mt19937_64::result_type seed) {
    mt19937_64 add_gen(seed);
    mt19937_64 rep_gen(seed + 1);
    uniform_real_distribution<> dist;
    vector<T> result;
    result.reserve(n);
    T x = min_value;
    while (result.size() < n) {
        if (dist(add_gen) <= add_prob) {
            result.emplace_back(x);
        }
        if (dist(rep_gen) <= 1 - rep_prob) {
            x++;
        }
    }
    return result;
}

template <class T>
size_t magic_index_naive(const vector<T>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == static_cast<T>(i)) {
            return i;
        }
    }
    return v.size();
}

template <class T>
size_t magic_index_unique(const vector<T>& v) {
    size_t begin = 0;
    size_t end = v.size();
    while (begin < end) {
        size_t mid = begin + (end - begin) / 2;
        if (v[mid] < static_cast<T>(mid)) {
            begin = mid + 1;
        } else {
            end = mid;
        }
    }
    return begin;
}

template <class T>
size_t magic_index(const vector<T>& v, size_t begin, size_t end) {
    if (begin < end) {
        size_t mid = begin + (end - begin) / 2;
        size_t result = v.size();
        if (v[mid] < static_cast<T>(mid)) {
            result = magic_index(v, begin, max<T>(v[mid], 0));
        } else if (v[mid] > static_cast<T>(mid)) {
            result = magic_index(v, min<T>(v[mid], end), end);
        } else {
            result = mid;
        }

        if (result < v.size() && v[result] == result) {
            begin = result;
        } else {
            if (v[mid] < static_cast<T>(mid)) {
                begin = magic_index(v, mid + 1, end);
            } else {
                begin = magic_index(v, begin, mid);
            }
        }
    }

    return begin;
}

int main(int argc, const char* argv[]) {
    const size_t n = 16;
    const float add_prob = 0.2;
    const float rep_prob = 0.5;
    const int min_value = -5;

    random_device rd;
    const auto seed = argc > 1 ? stoul(argv[1]) : rd();
    cerr << seed << endl;

    vector<int> v = build_input<int>(n, add_prob, rep_prob, min_value, seed);
    cerr << v << endl;

    vector<size_t> indexes;
    indexes.reserve(n);
    for (size_t i = 0; i < n; i++) {
        indexes.emplace_back(i);
    }
    cerr << indexes << endl;

    size_t result = v.size();
    if (rep_prob > 0) {
        result = magic_index(v, 0, v.size());
    } else {
        result = magic_index_unique(v);
    }

    if (result < v.size() && v[result] == result) {
        cout << result << endl;
    } else {
        if (magic_index_naive(v) != v.size()) {
            throw runtime_error("The algorithm is corrupted");
        }
        cout << "Magic index not found" << endl;
    }
}
