#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
istream& operator>>(istream& in, vector<T>& v) {
    T val;
    while (v.size() < v.capacity()) {
        in >> val;
        v.emplace_back(move(val));
    }
    return in;
}

template <class V, class W>
V knapsack_with_repetitions(const vector<V>& values, const vector<W>& weights, const W capacity) {
    vector<V> result;
    result.resize(capacity + 1);
    for (size_t w = 1; w < result.size(); w++) {
        for (size_t j = 0; j < weights.size(); j++) {
            if (weights[j] <= w) {
                result[w] = max(result[w], result[w - weights[j]] + values[j]);
            }
        }
    }

    return result[capacity];
}

template <class V, class W>
V knapsack_without_repetitions(const vector<V>& values, const vector<W>& weights, const W capacity) {
    vector<vector<V>> result;
    result.resize(capacity + 1);
    for (size_t w = 0; w < result.size(); w++) {
        result[w].resize(weights.size());
        for (size_t i = 0; i < weights.size(); i++) {
            if (weights[i] <= w) {
                result[w][i] = i > 0 ? max(result[w - weights[i]][i - 1] + values[i], result[w][i - 1]) : values[i];
            } else if (i > 0) {
                result[w][i] = result[w][i - 1];
            }
        }
    }

    V max_value = 0;
    for (size_t i = 0; i < weights.size(); i++) {
        max_value = max(max_value, result[capacity][i]);
    }

    return max_value;
}

int main() {
    size_t n;
    cin >> n;

    vector<long> values;
    values.reserve(n);
    cin >> values;

    vector<long> weights;
    weights.reserve(n);
    cin >> weights;

    long capacity;
    while (cin >> capacity) {
        cout
            << knapsack_with_repetitions(values, weights, capacity)
            << "\t"
            << knapsack_without_repetitions(values, weights, capacity)
            << endl;
    }
}
