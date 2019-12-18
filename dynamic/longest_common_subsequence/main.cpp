#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

size_t LCS(const string& a, const string& b) {
    vector<vector<size_t>> tmp;
    tmp.resize(a.size() + 1);
    for (auto& x : tmp) {
        x.resize(b.size() + 1);
    }

    for (size_t i = 1; i <= a.size(); i++) {
        for (size_t j = 1; j <= b.size(); j++) {
            if (a[i - 1] == b[j - 1]) {
                tmp[i][j] = tmp[i - 1][j - 1] + 1;
            } else {
                tmp[i][j] = max(tmp[i - 1][j], tmp[i][j - 1]);
            }
        }
    }

    return tmp[a.size()][b.size()];
}

int main() {
    vector<tuple<string, string, size_t>> tests {
        {"ABCDEF", "FBDAMN", 2},
        {"SHINCHAN", "NOHARAAA", 3},
        {"AA", "BB", 0},
        {"HARRY", "SALLY", 2},
        {"", "", 0}
    };
    for (const auto& x : tests) {
        const bool ok = LCS(get<0>(x), get<1>(x)) == get<2>(x);
        cerr << (ok ? "OK" : "ERROR") << endl;
    }
}
