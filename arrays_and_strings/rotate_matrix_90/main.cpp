#include <stdexcept>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<vector<T>>& v) {
    for (const auto& row : v) {
        for (const auto& x : row) {
            out << x << "\t";
        }
        out << endl;
    }
    return out;
}

template <class T>
bool operator==(const vector<vector<T>>& v1, const vector<vector<T>>& v2) {
    if (v1.size() != v2.size()) {
        return false;
    }

    for (size_t i = 0; i < v1.size(); i++) {
        if (v1[i].size() != v2[i].size()) {
            return false;
        }

        for (size_t j = 0; j < v1[i].size(); j++) {
            if (v1[i][j] != v2[i][j]) {
                return false;
            }
        }
    }

    return true;
}

template <class T>
void RotateMatrix90(vector<vector<T>>& v) {
    if (v.empty()) {
        return;
    }

    for (const auto& x : v) {
        if (x.size() != v.size()) {
            throw runtime_error("Matrix is not square");
        }
    }

    if (v.size() < 2) {
        return;
    }

    const size_t n = v.size();
    for (size_t i = 0; i < n / 2; i++) {
        for (size_t j = i; j < n - i - 1; j++) {
            swap(v[i][j], v[j][n - i - 1]);
            swap(v[i][j], v[n - i - 1][n - j - 1]);
            swap(v[i][j], v[n - j - 1][i]);
        }
    }
}

int main() {
    const vector<size_t> tests {0, 1, 2, 3, 4, 5, 99, 100};

    for (const auto& n : tests) {
        int val = 1;
        vector<vector<int>> v;
        v.reserve(n);
        for (size_t i = 0; i < n; i++) {
            vector<int> row;
            row.reserve(n);
            for (size_t j = 0; j < n; j++) {
                row.emplace_back(val++);
            }
            v.emplace_back(move(row));
        }

        vector<vector<int>> vRotated;
        vRotated.resize(v.size());
        for (size_t i = 0; i < n; i++) {
            vRotated[i].resize(n);
            for (size_t j = 0; j < n; j++) {
                vRotated[i][n - j - 1] = v[j][i];
            }
        }

        RotateMatrix90(v);

        if (v == vRotated) {
            cerr << n << "\tOK" << endl;
        } else {
            cerr << v << "!=" << endl << vRotated << endl;
        }
    }
}
