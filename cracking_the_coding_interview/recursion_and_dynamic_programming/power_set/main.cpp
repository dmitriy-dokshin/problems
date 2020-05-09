#include <iostream>
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
        T x;
        in >> x;
        v.emplace_back(move(x));
    }
    return in;
}

template <class T>
void power_set(const vector<T>& v, ostream& out, vector<T> result = {}, size_t i = 0) {
    if (i < v.size()) {
        power_set(v, out, result, i + 1);
        result.emplace_back(v[i]);
        power_set(v, out, std::move(result), i + 1);
    } else {
        out << result << endl;
    }
}

int main() {
    size_t n;
    cin >> n;

    vector<int> v;
    v.reserve(n);
    cin >> v;

    power_set(v, cout);
}
