#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

// Wrong
size_t ReduceString(const string& s) {
    if (s.empty()) {
        return 0;
    }
    stack<char> result;
    for (size_t i = 0; i < s.size(); i++) {
        char x = s[i];
        while (!result.empty() && result.top() != x) {
            switch (x) {
                case 'a':
                    switch (result.top()) {
                        case 'b':
                            x = 'c';
                            break;
                        case 'c':
                            x = 'b';
                            break;
                    }
                    break;
                case 'b':
                    switch (result.top()) {
                        case 'a':
                            x = 'c';
                            break;
                        case 'c':
                            x = 'a';
                            break;
                    }
                    break;
                case 'c':
                    switch (result.top()) {
                        case 'a':
                            x = 'b';
                            break;
                        case 'b':
                            x = 'a';
                            break;
                    }
                    break;
            }
            result.pop();
        }
        result.push(x);
    }
    return result.size();
}

enum class EBool {
    None = 0,
    True = 1,
    False = 2
};

static const vector<char> CHARS = {'a', 'b', 'c'};

unordered_map<char, vector<vector<EBool>>> MakeDP(const string& s) {
    unordered_map<char, vector<vector<EBool>>> dp;
    dp.reserve(CHARS.size());
    for (const auto& c : CHARS) {
        vector<vector<EBool>> v;
        v.resize(s.size());
        for (auto& x : v) {
            x.resize(s.size());
        }
        dp.emplace(c, move(v));
    }
    return dp;
}

EBool SetDP(const string& s, const char c, const size_t from, const size_t to, unordered_map<char, vector<vector<EBool>>>& dp) {
    if (from == to) {
        dp[c][from][to] = s[from] == c ? EBool::True : EBool::False;
    } else {
        for (size_t i = from + 1; i <= to; i++) {
            for (const char c1 : CHARS) {
                for (const char c2: CHARS) {
                    if (c1 != c && c2 != c && c1 != c2 && dp[c1][from][i - 1] == EBool::True && dp[c2][i][to] == EBool::True) {
                        dp[c][from][to] = EBool::True;
                        return dp[c][from][to];
                    }
                }
            }
        }
        dp[c][from][to] = EBool::False;
    }
    return dp[c][from][to];
}

size_t ReduceStringDynamic(const string& s) {
    size_t maxL = 0;
    auto dp = MakeDP(s);
    for (size_t l = 0; l < s.size(); l++) {
        for (const char c : CHARS) {
            for (size_t from = 0; from < s.size() - l; from++) {
                size_t to = from + l;
                if (SetDP(s, c, from, to, dp) == EBool::True) {
                    maxL = l;
                }
            }
        }
    }
    return s.size() - maxL;
}

int main() {
    size_t n;
    vector<string> tests;
    {
        ifstream in("input.txt");
        in >> n;
        in.ignore();
        tests.reserve(n);
        for (size_t i = 0; i < n; i++) {
            string s;
            getline(in, s);
            tests.emplace_back(move(s));
        }
    }

    vector<size_t> results;
    {
        ifstream in("output.txt");
        tests.reserve(n);
        for (size_t i = 0; i < n; i++) {
            size_t x;
            in >> x;
            in.ignore();
            results.emplace_back(x);
        }
    }

    for (size_t i = 0; i < tests.size(); i++) {
        size_t size = ReduceStringDynamic(tests[i]);
        if (size != results[i]) {
            cerr << tests[i] << endl;
            cerr << size << " != " << results[i] << endl;
            break;
        } else {
            cerr << "OK" << endl;
        }
    }
}
