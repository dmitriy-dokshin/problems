#include <algorithm>
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
size_t flip_bit_to_win(const T& x) {
    size_t size = sizeof(T) * 8;
    size_t second_to_last_zero = size;
    size_t last_zero = size;
    size_t max_one_len = 0;
    for (size_t i = 0; i < size; i++) {
        bool bit = x & (1 << (size - i - 1));
        if (bit == 0) {
            if (second_to_last_zero < size) {
                max_one_len = max(max_one_len, i - second_to_last_zero - 1);
            }
            second_to_last_zero = last_zero;
            last_zero = i;
        }
    }

    if (second_to_last_zero < size) {
        max_one_len = max(max_one_len, size - second_to_last_zero - 1);
    }

    return max_one_len;
}

int main() {
    unsigned int x;
    cin >> x;
    print(cerr, x) << endl;

    cout << flip_bit_to_win(x) << endl;
}
