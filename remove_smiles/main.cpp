#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>

using namespace std;

void removeSubstring(string& s, const string& subs) {
    if (subs.empty()) {
        throw runtime_error("Substring is empty");
    }

    size_t subsPos = 0;
    size_t writeAt = 0;

    auto getSubsPos = [&] {
        return min(subs.size() - 1, subsPos);
    };

    auto writeSubs = [&] {
        if (subsPos < subs.size()) {
            for (size_t j = 0; j < subsPos; j++, writeAt++) {
                s[writeAt] = subs[j];
            }
        }
    };

    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] != subs[getSubsPos()]) {
            writeSubs();
            subsPos = 0;
        }

        if (s[i] == subs[getSubsPos()]) {
            subsPos++;
        } else {
            if (writeAt != i) {
                s[writeAt] = s[i];
            }
            writeAt++;
        }
    }

    writeSubs();

    if (writeAt < s.size()) {
        s.erase(writeAt);
    }
}

int main() {
    vector<pair<string, string>> tests {
        {"Я работаю в Гугле :-)))", "Я работаю в Гугле "},
        {"везет :-) а я туда собеседование завалил:-((", "везет  а я туда собеседование завалил"},
        {"лол:)", "лол:)"},
        {"Ааааа!!!!! :-))(())", "Ааааа!!!!! (())"}
    };

    for (auto& x : tests) {
        removeSubstring(x.first, ":-)");
        removeSubstring(x.first, ":-(");
        const bool ok = x.first == x.second;
        cerr << (ok ? "OK" : "ERROR") << endl;
    }
}
