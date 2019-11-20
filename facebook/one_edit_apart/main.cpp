#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool one_diff_apart(const string& s1, const string& s2) {
    bool has_diff = false;
    for (size_t i = 0, j = 0; i < s1.size();) {
        if (s1[i] != s2[j]) {
            if (has_diff) {
                return false;
            } else {
                has_diff = true;
                if (s1.size() == s2.size()) {
                    i++;
                }
                j++;
            }
        } else {
            i++;
            j++;
        }
    }
    return true;
}

bool one_edit_apart(const string& s1, const string& s2) {
    if (s1.size() < s2.size()) {
        if (s2.size() - s1.size() == 1) {
            return one_diff_apart(s1, s2);
        } else {
            return false;
        }
    } else if (s1.size() > s2.size()) {
        if (s1.size() - s2.size() == 1) {
            return one_diff_apart(s2, s1);
        } else {
            return false;
        }
    } else {
        return one_diff_apart(s1, s2);
    }
}

int main() {
    vector<pair<string, string>> tests {
        {"cat", "dog"},
        {"cat", "cats"},
        {"cat", "cut"},
        {"cat", "cast"},
        {"cat", "at"},
        {"ct", "cat"},
        {"cat", "act"},
    };
    for (const auto& x : tests) {
        cerr << x.first << "\t" << x.second << "\t" << one_edit_apart(x.first, x.second) << endl;
    }
}
