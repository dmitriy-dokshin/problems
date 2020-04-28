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
T pairwise_swap(T x) {
    T mask = 0;
    for (size_t i = 0; i < sizeof(T) * 8; i++) {
        if (i % 2 == 0) {
            mask |= (1 << i);
        }
    }

    T even = (x & mask) << 1;
    T odd = (x & (mask << 1)) >> 1;
    T result = even | odd;
    return result;
}

int main() {
    unsigned int x;
    cin >> x;
    print(cerr, x) << endl;

    auto result = pairwise_swap(x);
    print(cout, result) << endl;
}
