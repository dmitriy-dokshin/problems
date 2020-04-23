#include <iostream>
#include <stdexcept>

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

ostream& print(ostream& out, double x) {
    if (x <= 0.0L || x >= 1.0) {
        throw runtime_error("Invalid value");
    }

    while (x > 0.0L) {
        x *= 2.0L;
        bool bit = x >= 1.0L;
        out << bit;
        if (bit) {
            x -= 1.0L;
        }
    }

    return out;
}

int main() {
    double x;
    cin >> x;
    print(cerr, reinterpret_cast<const unsigned long&>(x)) << endl;
    if (x > 0.0L && x < 1.0L) {
        print(cerr, x) << endl;
    }
}
