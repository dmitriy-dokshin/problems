#include <iostream>
#include <vector>

using namespace std;

void ZeroMatrix(vector<vector<int>>& v, size_t n, size_t m) {
    vector<bool> rows(n);
    vector<bool> cols(m);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            if (v[i][j] == 0) {
                rows[i] = true;
                cols[j] = true;
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            if (rows[i] || cols[j]) {
                v[i][j] = 0;
            }
        }
    }
}

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    auto x = v.begin();
    if (x != v.end()) {
        out << *x;
        x++;
        for (; x != v.end(); x++) {
            out << '\t' << *x;
        }
    }
    return out;
}

template <class T>
ostream& operator<<(ostream& out, const vector<vector<T>>& v) {
    auto x = v.begin();
    if (x != v.end()) {
        out << *x;
        x++;
        for (; x != v.end(); x++) {
            out << endl << *x;
        }
    }
    return out;
}

int main() {
    vector<vector<int>> v {
        {1, 2, 3, 4},
        {5, 0, 7, 8},
        {9, 0, 11, 12},
        {13, 14, 15, 0},
        {17, 18, 19, 20}
    };
    cerr << "before:" << endl << v << endl;
    ZeroMatrix(v, v.size(), v[0].size());
    cerr << "after:" << endl << v << endl;
}
