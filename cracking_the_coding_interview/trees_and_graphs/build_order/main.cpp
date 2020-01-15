#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "{";
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << ", " << v[i];
        }
    }
    out << "}";
    return out;
}

void visit(
    const string& p,
    const unordered_map<string, unordered_set<string>>& dependencies,
    unordered_set<string>& visited,
    unordered_set<string>& ancestors,
    vector<string>& result) {
    if (visited.find(p) != visited.end()) {
        return;
    }

    ancestors.emplace(p);
    auto descendants = dependencies.find(p);
    if (descendants != dependencies.end()) {
        for (const auto& x : descendants->second) {
            if (ancestors.find(x) != ancestors.end()) {
                throw runtime_error("Found a cycle: " + p + " depends on " + x);
            }

            visit(x, dependencies, visited, ancestors, result);
        }
    }

    ancestors.erase(ancestors.find(p));
    result.emplace_back(p);
    visited.emplace(p);
}

int main() {
    vector<string> projects {"a", "b", "c", "d", "e", "f"};
    unordered_map<string, unordered_set<string>> dependencies {
        {"a", {"f"}},
        {"b", {"f"}},
        {"c", {"d"}},
        {"d", {"a", "b"}}
    };

    vector<string> result;

    unordered_set<string> visited;
    for (const auto& p : projects) {
        unordered_set<string> ancestors;
        visit(p, dependencies, visited, ancestors, result);
    }

    cout << result << endl;
}
