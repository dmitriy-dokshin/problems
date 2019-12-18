#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

string LCS(const string& a, const string& b) {
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

    string result;
    result.resize(tmp[a.size()][b.size()]);
    for (size_t i = a.size(), j = b.size(); i > 0 && j > 0;) {
        if (a[i - 1] == b[j - 1]) {
            result[tmp[i][j] - 1] = a[i - 1];
            i--;
            j--;
        } else if (tmp[i - 1][j] > tmp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return result;
}

int main() {
    vector<tuple<string, string, string>> tests {
        {"ABCDEF", "FBDAMN", "BD"},
        {"SHINCHAN", "NOHARAAA", "NHA"},
        {"AA", "BB", ""},
        {"HARRY", "SALLY", "AY"},
        {"", "", ""}
    };
    for (const auto& x : tests) {
        string result = LCS(get<0>(x), get<1>(x));
        const bool ok = result == get<2>(x);
        cerr << (ok ? "OK" : "ERROR: " + result + " != " + get<2>(x)) << endl;
    }
}
