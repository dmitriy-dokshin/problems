#include <algorithm>
#include <iostream>
#include <stdexcept>
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

template <class T>
istream& operator>>(istream& in, vector<T>& v) {
    for (T& x : v) {
        cin >> x;
    }
    return in;
}

template <class T>
vector<T> Multiply(const vector<T>& a, const vector<T>& b, const size_t n) {
    vector<T> res;
    res.resize(2 * n - 1);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            res[i + j] += a[i] * b[j];
        }
    }

    return res;
}

template <class T>
vector<T> MultiplyDivideAndConquer(const vector<T>& a, const vector<T>& b, size_t n) {
    vector<T> res;
    if (n == 0) {
        res = {};
    } else if (n == 1) {
        res = {a[0] * b[0]};
    } else {
        res.resize(2 * n - 1);

        vector<T> a0(a.begin(), a.begin() + n / 2);
        vector<T> a1(a.begin() + n / 2, a.end());
        a0.resize(a1.size());

        vector<T> b0(b.begin(), b.begin() + n / 2);
        vector<T> b1(b.begin() + n / 2, b.end());
        b0.resize(b1.size());

        vector<T> a0b0 = MultiplyDivideAndConquer(a0, b0, a0.size());
        for (size_t i = 0; i < a0b0.size(); i++) {
            res[i] += a0b0[i];
        }

        vector<T> a0b1 = MultiplyDivideAndConquer(a0, b1, a0.size());
        for (size_t i = 0; i < a0b1.size(); i++) {
            res[i + n / 2] += a0b1[i];
        }

        vector<T> a1b0 = MultiplyDivideAndConquer(a1, b0, a0.size());
        for (size_t i = 0; i < a1b0.size(); i++) {
            res[i + n / 2] += a1b0[i];
        }

        vector<T> a1b1 = MultiplyDivideAndConquer(a1, b1, a0.size());
        for (size_t i = 0; i < a1b1.size(); i++) {
            res[i + n / 2 * 2] += a1b1[i]; // 3 != 3 / 2 * 2 while using integers
        }
    }

    // cerr << a << " * " << b << " = " << res << endl;

    return res;
}

int main() {
    size_t n;
    cin >> n;

    vector<long> a(n);
    cin >> a;
    reverse(a.begin(), a.end());

    vector<long> b(n);
    cin >> b;
    reverse(b.begin(), b.end());

    {
        vector<long> res = Multiply(a, b, n);
        reverse(res.begin(), res.end());
        cout << res << endl;
    }

    {
        vector<long> res = MultiplyDivideAndConquer(a, b, n);
        reverse(res.begin(), res.end());
        cout << res << endl;
    }
}
