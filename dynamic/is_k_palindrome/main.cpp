#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class matrix {
public:
    matrix(size_t size)
        : Size_(size)
    {
        Data_.resize(size);
    }

    T& operator()(size_t i, size_t j) {
        return Data_[i * Size_ + j]; 
    }

private:
    size_t Size_;
    vector<T> Data_;
};

size_t is_k_palindrome_dynamic(const string& s) {
    if (s.size() < 2) {
        return 0;
    }

    matrix<size_t> k(s.size());
    for (size_t l = 1; l < s.size(); l++) {
        for (size_t begin = 0; begin < s.size() - l; begin++) {
            size_t end = begin + l;
            if (s[begin] == s[end]) {
                k(begin, end) = k(begin + 1, end - 1);
            } else {
                k(begin, end) = min(k(begin + 1, end), k(begin, end - 1)) + 1;
            }
        }
    }

    return k(0, s.size() - 1);
}

size_t is_k_palindrome(const string& s, size_t begin, size_t end) {
    if (begin >= end) {
        return 0;
    }

    if (s[begin] == s[end]) {
        return is_k_palindrome(s, begin + 1, end - 1);
    } else {
        return min(
            is_k_palindrome(s, begin + 1, end),
            is_k_palindrome(s, begin, end - 1)) + 1;
    }
}

size_t is_k_palindrome(const string& s) {
    return s.size() < 2 ? 0 : is_k_palindrome(s, 0, s.size() - 1);
}

int main() {
    const string s = "abcddcbae";
    cerr << is_k_palindrome(s) << endl;
    cerr << is_k_palindrome_dynamic(s) << endl;
}
