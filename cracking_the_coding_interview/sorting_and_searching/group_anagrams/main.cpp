#include <lib/random/random.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

vector<string> random_strings(size_t n, size_t len, char min_val, char max_val) {
    random_device rd;
    vector<string> result;
    result.reserve(n);
    while (result.size() < n) {
        auto v = TRandom<char>::random_vector(len, min_val, max_val, rd());
        result.emplace_back(v.begin(), v.end());
    }
    return result;
}

void group_anagrams(vector<string>& v) {
    unordered_map<string, vector<size_t>> map;
    for (size_t i = 0; i < v.size(); i++) {
        string key = v[i];
        sort(key.begin(), key.end());
        map[key].emplace_back(i);
    }

    vector<string> result;
    result.reserve(v.size());
    for (const auto& x : map) {
        cerr << x.first << endl;
        for (const size_t i : x.second) {
            result.emplace_back(v[i]);
            cerr << "\t" << v[i] << endl;
        }
    }
    v = result;
}

int main() {
    vector<string> v = random_strings(10, 5, 'a', 'b');
    cerr << "before:" << endl;
    for (const auto& x : v) {
        cerr << x << endl;
    }

    cerr << endl << "debug:" << endl;
    group_anagrams(v);

    cerr << endl << "after:" << endl;
    for (const auto& x : v) {
        cerr << x << endl;
    }
}
