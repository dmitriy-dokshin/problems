#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <stack>
#include <vector>
#include <utility>

using namespace std;

template <class T>
T largest_rectangle(const vector<T>& v) {
    T largest = numeric_limits<T>::min();
    stack<pair<size_t, T>> tmp;
    for (const T& x : v) {
        size_t l = 0;
        while (!tmp.empty() && x < tmp.top().second) {
            l += tmp.top().first;
            largest = max(largest, static_cast<T>(l * tmp.top().second));
            tmp.pop();
        }
        tmp.emplace(l + 1, x);
    }

    size_t l = 0;
    while (!tmp.empty()) {
        l += tmp.top().first;
        largest = max(largest, static_cast<T>(l * tmp.top().second));
        tmp.pop();
    }

    return largest;
}

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

vector<long> prepare_input(long n = 5) {
    vector<long> v;
    v.reserve(n);
    for (long x = 1; x <= n; x++) {
        v.emplace_back(x);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(v.begin(), v.end(), g);

    return v;
}

int main() {
    vector<long> v = prepare_input();
    cerr << v << endl;
    cerr << "largest_rectangle: " << largest_rectangle(v) << endl;
}
