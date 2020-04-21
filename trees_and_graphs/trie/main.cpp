#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class TNode {
public:
    bool Has(const string& word) const {
        const TNode* node = this;
        for (const auto& x : word) {
            auto ptr = node->Children.find(x);
            if (ptr == node->Children.end()) {
                return false;
            }
            node = &ptr->second;
        }
        return true;
    }

    unordered_map<char, TNode> Children;
};

int main() {
    TNode trie;
    vector<string> words {
        "abc",
        "a",
        "xyz"
    };

    for (const auto& word : words) {
        TNode* node = &trie;
        for (const auto& x : word) {
            node = &node->Children[x];
        }
    }

    vector<pair<string, bool>> tests {
        {"ab", true},
        {"abcd", false},
        {"a", true},
        {"xyz", true},
        {"l", false}
    };

    for (const auto& x : tests) {
        bool ok = trie.Has(x.first) == x.second;
        cerr << x.first << "\t" << (ok ? "OK" : "ERROR") << endl;
    }
}
