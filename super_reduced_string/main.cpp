#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

void SuperReduce(string& s) {
    size_t n;
    size_t pos = s.size();
    do {
        n = pos;
        pos = 0;
        size_t i = 0;
        while (i < n) {
            size_t j = i + 1;
            while (j < n && s[i] == s[j]) {
                j++;
            }
            if ((j - i) % 2 == 1) {
                s[pos] = s[i];
                pos++;
            }
            i = j;
        }
    } while (pos < n);
    s.erase(n);
}

int main() {
    vector<pair<string, const string>> tests {
        {"aa", ""},
        {"baab", ""},
        {"aaabccddd", "abd"}
    };
    for (auto& x : tests) {
        SuperReduce(x.first);
        if (x.first != x.second) {
            cerr << "ERROR\t\"" << x.first << "\" != \"" << x.second << "\"" << endl;
        } else {
            cerr << "OK" << endl;
        }
    }
}
