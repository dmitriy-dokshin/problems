#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

bool IsSubstring(const string& s, const string sub) {
    return s.find(sub) != string::npos;
}

bool IsRotation(const string& s1, const string& s2) {
    if (s1.size() != s2.size()) {
        return false;
    }

    for (size_t i = 0; i < s1.size(); i++) {
        size_t j = 0;
        while (i + j < s1.size() && s1[i + j] == s2[j]) {
            j++;
        }

        if (i + j == s1.size() && IsSubstring(s1.substr(0, i), s2.substr(j))) {
            return true;
        }
    }

    return false;
}

bool IsRotationFast(const string& s1, const string& s2) {
    return IsSubstring(s1 + s1 + s1, s2);
}

int main() {
    vector<tuple<string, string, bool>> tests {
        {"waterbottle", "erbottlewat", true},
        {"aaabbb", "aabbba", true},
        {"aaa", "bbb", false},
        {"aaa", "aaa", true}
    };
    for (const auto& x : tests) {
        const string& s1 = get<0>(x);
        const string& s2 = get<1>(x);
        bool ok = IsRotation(s1, s2) == get<2>(x) && IsRotation(s2, s1) == get<2>(x)
            && IsRotationFast(s1, s2) == get<2>(x) && IsRotationFast(s2, s1) == get<2>(x);
        cerr << (ok ? "OK" : "ERROR") << endl;
    }
}
