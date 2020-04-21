#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "{";
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << ", " <<  v[i];
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
T sum(const vector<T>& v, size_t begin, size_t end) {
    T sum = 0;
    for (size_t i = begin; i < end; i++) {
        sum += v[i];
    }
    return sum;
}

template <class T>
bool subarray_sum_naive(const vector<T>& v, const T& target_sum) {
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j <= v.size(); j++) {
            if (sum(v, i, j) == target_sum) {
                return true;
            }
        }
    }

    return false;
}

template <class T>
bool subarray_sum(const vector<T>& v, const T& target_sum) {
    unordered_map<T, size_t> sums;
    T sum = 0;
    for (size_t i = 0; i < v.size(); i++) {
        sum += v[i];
        if (sum == target_sum) {
            return true;
        }
        sums.emplace(sum, i);
    }

    T total_sum = sum;
    sum = 0;
    for (size_t i = v.size(); i > 1; i--) {
        sum += v[i - 1]; 
        if (sum == target_sum) {
            return true;
        }
        auto x = sums.find(total_sum - (sum + target_sum));
        if (x != sums.end() && x->second < i - 2) {
            return true;
        }
    }

    return false;
}

int main(int argc, const char* argv[]) {
    size_t size = 10;
    long min = -10;
    long max = 10;

    random_device rd;
    typename mt19937_64::result_type seed = argc > 1 ? stoul(argv[1]) : rd();

    auto v = random_array<long>(size, min, max, seed);

    cerr << v << endl;

    size_t tests_count = 10;
    auto total_sum = sum(v, 0, v.size());
    mt19937_64 sum_gen(seed + 1);
    uniform_int_distribution<long> sum_dist(static_cast<decltype(min)>(size) * min, static_cast<decltype(max)>(size) * max);
    for (size_t i = 0; i < tests_count; i++) {
        auto target_sum = sum_dist(sum_gen);
        bool exists = subarray_sum_naive(v, target_sum);
        bool ok = exists == subarray_sum(v, target_sum);
        cerr << target_sum << "\t" << (exists ? "true" : "false") << "\t" << (ok ? "OK" : "ERROR") << endl;
    }
}
