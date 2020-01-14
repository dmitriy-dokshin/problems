#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

using namespace std;

/*
 * s = some_merge(reverse(A), some_shuffle(A))
 * Find A
*/
string reverse_shuffle_merge(string s) {
    // To iterate from left to right
    reverse(s.begin(), s.end());

    unordered_map<char, size_t> required_counts;
    for (const char x : s) {
        required_counts[x]++;
    }
    unordered_map<char, size_t> total_counts = required_counts;
    for (auto& x : required_counts) {
        x.second /= 2;
    }

    string result;
    result.reserve(s.size() / 2);
    size_t from = 0;
    while (result.size() < s.size() / 2) {
        unordered_map<char, size_t> current_counts;
        for (size_t i = 0; i < from; i++) {
            current_counts[s[i]]++;
        }

        size_t j = s.size();
        for (size_t i = from; i < s.size(); i++) {
            if (required_counts[s[i]] == 0) {
                continue;
            }

            if (j == s.size() || s[i] < s[j]) {
                j = i;
            }

            current_counts[s[i]]++;
            if (total_counts[s[i]] - current_counts[s[i]] < required_counts[s[i]]) {
                break;
            }
        }

        result += s[j];
        required_counts[s[j]]--;
        from = j + 1;
    }

    return result;
}


int main() {
    string s;
    cin >> s;
    cout << reverse_shuffle_merge(move(s)) << endl;
}
