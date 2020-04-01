#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

bool AreOneDeleteAway(const string& s, const string& b) {
    if (b.size() - s.size() > 1) {
        return false;
    }

    bool deleted = false;
    for (size_t i = 0, j = 0; i < s.size() && j < b.size(); j++) {
        if (s[i] == s[j]) {
            i++;
        } else {
            if (deleted) {
                return false;
            }

            deleted = true;
        }
    }

    return true;
}

bool AreOneEditAway(const string& x, const string& y) {
    bool edited = false;
    for (size_t i = 0; i < x.size(); i++) {
        if (x[i] != y[i]) {
            if (edited) {
                return false;
            }

            edited = true;
        }
    }

    return true;
}

bool AreAlmostEqual(const string& x, const string& y) {
    if (x.size() < y.size()) {
        return AreOneDeleteAway(x, y);
    } else if (x.size() > y.size()) {
        return AreOneDeleteAway(y, x);
    } else {
        return AreOneEditAway(x, y);
    }
}

int main() {
    vector<tuple<string, string, bool>> tests {
        {"pale", "ple", true},
        {"pales", "pale", true},
        {"pale", "bale", true},
        {"pale", "bake", false}
    };

    for (const auto& x : tests) {
        bool ok = AreAlmostEqual(get<0>(x), get<1>(x)) == get<2>(x);
        cerr << (ok ? "OK" : "ERROR") << endl;
    }
}
