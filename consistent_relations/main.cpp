#include <iostream>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    auto x = v.begin();
    if (x != v.end()) {
        out << "{" << *x;
        x++;
        for (; x != v.end(); x++) {
            out << ", " << *x;
        }
        cerr << "}";
    }
    return out;
}

template <bool bidirected>
vector<vector<bool>> ToGraph(const vector<pair<size_t, size_t>>& v, const size_t n) {
    vector<vector<bool>> g(n);
    for (auto& x : g) {
        x.resize(n);
    }
    for (const auto& x : v) {
        g[x.first][x.second] = true;
        if (bidirected) {
            g[x.second][x.first] = true;
        }
    }
    return g;
}

vector<size_t> FindComponents(const vector<vector<bool>>& equal) {
    const size_t n = equal.size();
    vector<size_t> result(n);
    for (size_t x = 0; x < n; x++) {
        if (result[x] == 0) {
            queue<size_t> q;
            q.emplace(x);
            while (!q.empty()) {
                size_t i = q.front();
                result[i] = x + 1;
                for (size_t j = 0; j < equal.size(); j++) {
                    if (equal[q.front()][j] && result[j] == 0) {
                        q.emplace(j);
                    }
                }
                q.pop();
            }
        }
    }
    return result;
}

bool IsConsistent(
    const vector<pair<size_t, size_t>>& equal,
    const vector<pair<size_t, size_t>>& notEqual,
    const vector<pair<size_t, size_t>>& less,
    const size_t n) {
    vector<size_t> equalComponents = FindComponents(ToGraph</*bidirected=*/true>(equal, n));;

    for (const auto& x : notEqual) {
        if (equalComponents[x.first] == equalComponents[x.second]) {
            return false;
        }
    }

    auto gless = ToGraph</*bidirected=*/false>(less, n);
    for (size_t x = 0; x < n; x++) {
        unordered_set<size_t> components;
        queue<size_t> q;
        q.emplace(x);
        while (!q.empty()) {
            size_t i = q.front();
            if (!components.emplace(equalComponents[i]).second) {
                return false;
            }
            for (size_t j = 0; j < n; j++) {
                if (gless[i][j]) {
                    q.emplace(j);
                }
            }
            q.pop();
        }
    }
    
    return true;
}

int main() {
    const vector<pair<size_t, size_t>> equal {
        {1, 2},
        {3, 4},
        {2, 3}
    };
    const vector<pair<size_t, size_t>> notEqual {
        {5, 6}
    };
    const vector<pair<size_t, size_t>> less {
        {5, 6},
        {6, 7},
        {0, 2}
    };
    const size_t n = 10;
    cerr << IsConsistent(equal, notEqual, less, n) << endl;
}
