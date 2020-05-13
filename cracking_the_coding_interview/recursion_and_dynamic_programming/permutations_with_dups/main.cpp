#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> permutations_without_dups(const string& s, size_t i = 0) {
    if (i < s.size()) {
        if (i == s.size() - 1) {
            return {{s[i]}};
        } else {
            vector<string> res;
            vector<string> tmp = permutations_without_dups(s, i + 1);
            for (const auto& x : tmp) {
                for (size_t j = 0; j < x.size(); j++) {
                    if (x[j] != s[i]) {
                        res.emplace_back(x.substr(0, j) + string{s[i]} + x.substr(j));
                    }
                }
                res.emplace_back(x + string{s[i]});
            }
            return res;
        }
    } else {
        return {};
    }
}

int main() {
    string s;
    cin >> s;

    for (const auto& x : permutations_without_dups(s)) {
        cout << x << endl;
    }
}
