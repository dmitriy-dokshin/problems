#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> spiral_array(const size_t n) {
    vector<vector<int>> v;
    v.resize(n);
    for (auto& x : v) {
        x.resize(n);
    }

    int val = 1;
    for (size_t k = 0; k < n / 2; k++) {
        size_t i, j;

        i = k;
        for (j = k; j < n - k - 1; j++) {
            v[i][j] = val++;
        }

        j = n - k - 1;
        for (i = k; i < n - k - 1; i++) {
            v[i][j] = val++;
        }

        i = n - k - 1;
        for (j = n - k - 1; j > k; j--) {
            v[i][j] = val++;
        }

        j = k;
        for (i = n - k - 1; i > k; i--) {
            v[i][j] = val++;
        }
    }

    if (n % 2 > 0) {
        v[n / 2][n / 2] = val++;
    }

    return v;
}

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
ostream& operator<<(ostream& out, const vector<vector<T>>& v) {
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << endl << v[i];
        }
    }
    return out;
}

int main(const int argc, const char* argv[]) {
    size_t n = 3;
    if (argc > 1) {
        n = stoi(argv[1]);
    }

    auto v = spiral_array(n);
    cerr << v << endl;
}
