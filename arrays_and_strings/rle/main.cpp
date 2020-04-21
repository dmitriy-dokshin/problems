#include <iostream>
#include <string>

using namespace std;

size_t ToString(size_t val, string& s, size_t i) {
    size_t size = 1;
    size_t div = 10;
    while (div < val) {
        div *= 10;
        size++;
    }
    div /= 10;

    while (div > 0) {
        s[i++] = '0' + val / div;
        val = val % div;
        div /= 10;
    }

    return size;
}

void RLE(string& s) {
    size_t i = 0;
    size_t j = 0;
    while (i < s.size()) {
        s[j++] = s[i];
        size_t size = 1;
        while (i + size < s.size() && s[i + size] == s[i]) {
            size++;
        }
        if (size > 1) {
            j += ToString(size, s, j);
        }
        i += size;
    }
    s.erase(j);
}

int main() {
    string s = "AAAABBBCCXYZDDDDEEEFFFAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBB";
    RLE(s);
    cerr << s << endl;
}
