#include <iostream>
#include <vector>

using namespace std;

void ZeroMatrix(vector<vector<int>>& v, size_t n, size_t m) {
    for (size_t i = 1; i < n && v[0][0] != 0; i++) {
        if (v[i][0] == 0) {
            v[0][0] = 0;
        }
    }

    for (size_t j = 1; j < m && v[0][0] != 0; j++) {
        if (v[0][j] == 0) {
            v[0][0] = 0;
        }
    }

    for (size_t i = 1; i < n; i++) {
        for (size_t j = 1; j < m; j++) {
            if (v[i][j] == 0) {
                v[i][0] = 0;
                v[0][j] = 0;
            }
        }
    }

    for (size_t i = 1; i < n; i++) {
        for (size_t j = 1; j < m; j++) {
            if (v[i][0] == 0 || v[0][j] == 0) {
                v[i][j] = 0;
            }
        }
    }

    if (v[0][0] == 0) {
        for (size_t i = 1; i < n; i++) {
            v[i][0] = 0;
        }
        for (size_t j = 1; j < m; j++) {
            v[0][j] = 0;
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
