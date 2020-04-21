#include <iostream>
#include <limits>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << " " << v[i];
        }
    }
    return out;
}

template <class T>
istream& operator>>(istream& in, vector<T>& v) {
    while (v.size() < v.capacity()) {
        T value;
        in >> value;
        v.emplace_back(move(value));
    }
    return in;
}

template <class T>
vector<T> min_max_riddle(const vector<T>& v) {
    vector<size_t> next_less(v.size(), v.size());
    stack<pair<size_t, T>> min;
    for (size_t i = 0; i < v.size(); i++) {
        while (!min.empty() && v[i] < min.top().second) {
            next_less[min.top().first] = i;
            min.pop();
        }
        min.emplace(i, v[i]);
    }

    vector<size_t> prev_less(v.size(), v.size());
    min = {};
    for (size_t i = v.size(); i > 0; i--) {
        while (!min.empty() && v[i - 1] < min.top().second) {
            prev_less[min.top().first] = i - 1;
            min.pop();
        }
        min.emplace(i - 1, v[i - 1]);
    }


    vector<T> res(v.size(), numeric_limits<T>::min());
    for (size_t i = 0; i < v.size(); i++) {
        size_t d = next_less[i] - (prev_less[i] < v.size() ? prev_less[i] + 1 : 0);
        res[d - 1] = max(res[d - 1], v[i]);
    }

    for (size_t i = v.size() - 1; i > 0; i--) {
        res[i - 1] = max(res[i - 1], res[i]);
    }

    return res;
}

int main() {
    size_t n;
    cin >> n;
    cin.ignore();

    vector<long> v;
    v.reserve(n);
    cin >> v;
    cin.ignore();

    cout << min_max_riddle(v) << endl;
}
