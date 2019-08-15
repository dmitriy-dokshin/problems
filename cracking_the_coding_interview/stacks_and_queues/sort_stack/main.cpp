#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>

using namespace std;

template <class T>
void Sort(stack<T>& source) {
    stack<T> tmp;
    while (!source.empty()) {
        T x = move(source.top());
        source.pop();
        while (!tmp.empty() && tmp.top() < x) {
            source.emplace(move(tmp.top()));
            tmp.pop();
        }
        tmp.push(move(x));
    }
    source = move(tmp);
}

template <class T>
ostream& operator<<(ostream& out, stack<T>& source) {
    out << "{";
    if (!source.empty()) {
        stack<T> tmp;
        while (!source.empty()) {
            tmp.emplace(move(source.top()));
            source.pop();
        }
        cerr << tmp.top();
        source.emplace(move(tmp.top()));
        tmp.pop();
        while (!tmp.empty()) {
            cerr << ", " << tmp.top();
            source.emplace(move(tmp.top()));
            tmp.pop();
        }
    }
    out << "}";
    return out;
}

int main() {
    srand(time(nullptr));

    stack<int> source;
    size_t n = 10;
    for (size_t i = 0; i < n; i++) {
        source.emplace(rand() % n);
    }

    cerr << source << endl;

    Sort(source);

    cerr << source << endl;
}
