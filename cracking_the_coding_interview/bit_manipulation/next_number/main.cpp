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
void next_number(const T& x, T& prev, T& next) {
    for (size_t i = 0; i < sizeof(x) * 8 - 1 && (!prev || !next); i++) {
        bool bit = x & (1 << i);
        bool next_bit = x & (1 << (i + 1));
        if (next_bit == 0 && bit == 1) {
            if (!next) {
                next = x + (1 << i);
            }
        } else if (next_bit == 1 && bit == 0) {
            if (!prev) {
                prev = x - (1 << i);
            }
        }
    }
}

int main() {
    unsigned int x;
    cin >> x;
    cerr << x << endl;
    print(cerr, x) << endl;

    unsigned int prev = 0;
    unsigned int next = 0;
    next_number(x, prev, next);

    cout << prev << endl;
    print(cerr, prev) << endl;

    cout << next << endl;
    print(cerr, next) << endl;

}
