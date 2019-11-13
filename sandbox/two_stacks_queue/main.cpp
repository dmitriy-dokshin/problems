#include "two_stacks_queue.h"

#include <iostream>
#include <stack>
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

template <class TStack_>
ostream& operator<<(ostream& out, TTwoStacksQueue<TStack_>& q) {
    out << "{";
    if (!q.Empty()) {
        out << q.Top();
        q.Pop();
        while (!q.Empty()) {
            out << ", " << q.Top();
            q.Pop();
        }
    }
    out << "}";
    return out;
}

int main() {
    vector<long> v {1, 2, 3, 4, 5};
    TTwoStacksQueue<stack<long>> q;
    for (const auto& x : v) {
        q.Push(x);
    }
    cerr << v << endl;
    cerr << q << endl;
}
