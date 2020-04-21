#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

using namespace std;

string reverse_shuffle_merge(string s) {
    unordered_map<char, size_t> total_counts;
    for (const auto& x : s) {
        total_counts[x]++;
    }

    unordered_map<char, size_t> required_counts;
    for (const auto& x : total_counts) {
        if (x.second % 2 != 0) {
            throw runtime_error("Unable to find required string");
        }

        required_counts.emplace(x.first, x.second / 2);
    }

    reverse(s.begin(), s.end());

    string result;
    result.reserve(s.size() / 2);
    size_t from = 0;
    while (result.size() < s.size() / 2) {
        unordered_map<char, size_t> counts = total_counts;
        for (size_t i = 0; i < from; i++) {
            counts[s[i]]--;
        }

        size_t min_index = s.size();
        for (size_t i = from; i < s.size(); i++) {
            if (required_counts[s[i]] == 0) {
                continue;
            }

            if (min_index == s.size() || s[i] < s[min_index]) {
                min_index = i;
            }

            counts[s[i]]--;
            if (counts[s[i]] < required_counts[s[i]]) {
                break;
            }
        }

        result += s[min_index];
        required_counts[s[min_index]]--;
        from = min_index + 1;
    }

    return result;
}

int main() {
    string s;
    cin >> s;
    cout << reverse_shuffle_merge(move(s)) << endl;
}
