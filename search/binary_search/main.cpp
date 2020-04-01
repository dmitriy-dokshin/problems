#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
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
vector<T> random_array(size_t size, const T& min, const T& max, typename mt19937_64::result_type seed) {
    mt19937_64 gen(seed);
    uniform_int_distribution<T> dist(min, max);

    vector<T> v;
    v.reserve(size);
    while (v.size() < size) {
        v.emplace_back(dist(gen));
    }

    return v;
}

template <class T>
size_t bound_naive(const vector<T>& v, function<bool(const T&)> pred) {
    size_t begin = 0;
    size_t end = v.size();
    while (begin < end && pred(v[begin])) {
        begin++;
    }
    return begin;
}

template <class T>
size_t lower_bound_naive(const vector<T>& v, const T& val) {
    return bound_naive<T>(v, [&val](const T& x) { return x < val; });
}

template <class T>
size_t upper_bound_naive(const vector<T>& v, const T& val) {
    return bound_naive<T>(v, [&val](const T& x) { return x <= val; });
}

template <class T>
pair<size_t, size_t> binary_search_naive(const vector<T>& v, const T& val) {
    return {lower_bound_naive(v, val), upper_bound_naive(v, val)};
}

template <class T>
size_t bound(const vector<T>& v, function<bool(const T&)> pred) {
    size_t begin = 0;
    size_t end = v.size();
    while (begin < end) {
        size_t mid = (begin + end) / 2;
        if (pred(v[mid])) {
            begin = mid + 1;
        } else {
            end = mid;
        }
    }
    return begin;
}

template <class T>
size_t lower_bound(const vector<T>& v, const T& val) {
    return bound<T>(v, [&val](const T& x) { return x < val; });
}

template <class T>
size_t upper_bound(const vector<T>& v, const T& val) {
    return bound<T>(v, [&val](const T& x) { return x <= val; });
}

template <class T>
pair<size_t, size_t> binary_search(const vector<T>& v, const T& val) {
    return {lower_bound(v, val), upper_bound(v, val)};
}

int main(const int argc, const char* argv[]) {
    size_t size = 9;
    int min = -10;
    int max = 10;
    size_t tests_count = 10;

    random_device rd;
    typename mt19937_64::result_type seed = argc > 1 ? stoul(argv[1]) : rd();

    auto v = random_array<int>(size, min, max, seed);
    sort(v.begin(), v.end());
    cout << v << endl;

    mt19937_64 val_gen(seed + 1);
    uniform_int_distribution<int> val_dist(min, max);

    for (; tests_count > 0; tests_count--) {
        int val = val_dist(val_gen);
        auto result = binary_search(v, val);
        auto result_naive = binary_search_naive(v, val);
        cout << val << "\t" << result << "\t" << result_naive << "\t" <<(result == result_naive ? "OK" : "ERROR") << endl;
    }
}
