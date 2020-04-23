#include <iostream>

using namespace std;

template <class T>
ostream& print(ostream& out, const T& value) {
    for (size_t i = sizeof(value) * 8; i > 0; i--) {
        T mask = 1;
        mask <<= (i - 1);
        bool bit = value & mask;
        out << bit;
    }
    return out;
}

template <class T>
T insert(T n, T m, size_t i, size_t j) {
    size_t size = j - i + 1;
    T mask = ~(((1 << size) - 1) << i);
    n &= mask;
    n |= m << i;
    return n;
}

int main() {
    int n = 1 << 10;
    print(cerr, n) << endl;

    int m = 19;
    print(cerr, m) << endl;

    int result = insert(n, m, 2, 6);
    print(cout, result) << endl;
}
