#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

template <class T>
class T2DVector {
public:
    T2DVector(size_t n, size_t m)
        : Data_(n * m)
        , N_(n)
        , M_(m)
    {
    }

    T& operator()(size_t i, size_t j) {
        return Data_[i * M_ + j];
    }

    vector<T> Data_;
    size_t N_;
    size_t M_;
};

template <class T>
class TOptional {
public:
    TOptional() = default;

    template <class T_>
    TOptional(T_&& value)
        : Value_(move(value))
    {
    }

    template <class T_>
    TOptional& operator=(T_&& value) {
        HasValue_ = true;
        Value_ = move(value);
        return *this;
    }

    operator bool() {
        return HasValue_;
    }

    T& operator*() {
        return Value_;
    }

private:
    T Value_;
    bool HasValue_ = false;
};

size_t LCSTopDown(const string& s1, const string& s2, const size_t l1, const size_t l2, T2DVector<TOptional<size_t>>& result) {
    if (l1 < 1 || l2 < 1) {
        return 0;
    }
    size_t i = l1 - 1;
    size_t j = l2 - 1;
    if (result(i, j)) {
        return *result(i, j);
    }
    if (s1[i] == s2[j]) {
        result(i, j) = LCSTopDown(s1, s2, l1 - 1, l2 - 1, result) + 1;
    } else {
        result(i, j) = max(LCSTopDown(s1, s2, l1 - 1, l2, result), LCSTopDown(s1, s2, l1, l2 - 1, result));
    }
    return *result(i, j);
}

size_t LCSTopDown(const string& s1, const string& s2) {
    T2DVector<TOptional<size_t>> result(s1.size(), s2.size());
    return LCSTopDown(s1, s2, s1.size(), s2.size(), result);
}

size_t LCSBottomUp(const string& s1, const string& s2) {
    if (s1.empty() || s2.empty()) {
        return 0;
    }

    vector<vector<size_t>> result(s1.size() + 1);
    for (auto& x : result) {
        x.resize(s2.size() + 1);
    }
    for (size_t i = 1; i <= s1.size(); i++) {
        for (size_t j = 1; j <= s2.size(); j++) {
            if (s1[i - 1] == s2[j - 1]) {
                result[i][j] = result[i - 1][j - 1] + 1;
            } else {
                result[i][j] = max(result[i][j - 1], result[i - 1][j]);
            }
        }
    }
    return result[s1.size()][s2.size()];
}

int main() {
    vector<tuple<string, string, size_t>> tests {
        {"ABCDEF", "FBDAMN", 2},
        {"SHINCHAN", "NOHARAAA", 3},
        {"AA", "BB", 0},
        {"HARRY", "SALLY", 2},
        {"", "", 0}
    };
    for (const auto& x : tests) {
        const bool ok = LCSTopDown(get<0>(x), get<1>(x)) == get<2>(x) && LCSBottomUp(get<0>(x), get<1>(x)) == get<2>(x);
        cerr << (ok ? "OK" : "ERROR") << endl;
    }
}
