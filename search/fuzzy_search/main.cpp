#include <string>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

bool FuzzySearch(const string& text, const string& query) {
    size_t j = 0;
    for (size_t i = 0; i < text.size(); i++) {
        if (j < query.size()) {
            if (text[i] == query[j]) {
                j++;
            }
        } else {
            return true;
        }
    }
    return j == query.size();
}

int main() {
    vector<tuple<string, string, bool>> tests {
        {"car", "cartwheel" , true},
        {"cwhl", "cartwheel", true},
        {"cwheel", "cartwheel", true},
        {"cartwheel", "cartwheel", true},
        {"cwheeel", "cartwheel", false},
        {"lw", "cartwheel", false},
    };
    for (const auto& x : tests) {
        const bool ok = FuzzySearch(get<1>(x), get<0>(x)) == get<2>(x);
        cerr << (ok ? "OK" : "ERROR") << endl;
    }
}
