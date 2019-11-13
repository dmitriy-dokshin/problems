#include "min_queue.h"

#include <algorithm>
#include <iostream>
#include <random>
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

    TMinQueue<long> q;

    vector<long> min;
    for (const auto& x : v) {
        q.Push(x);
        min.emplace_back(q.Min());
    }
    cerr << min << endl;

    min.clear();
    while (!q.Empty()) {
        min.emplace_back(q.Min());
        q.Pop();
    }
    cerr << min << endl;
}
