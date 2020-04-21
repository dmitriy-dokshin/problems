#include <cmath>
#include <chrono>
#include <iostream>
#include <type_traits>

// O(min(x, y))
template <class T>
T GCDNaive(T x, T y) {
    static_assert(std::is_unsigned<T>::value, "Unsigned type required");

    if (x < y) {
        std::swap(x, y);
    }

    T gcd = 1;
    for (T q = 2; q < std::min(x, y); q++) {
        if (x % q == 0 && y % q == 0) {
            gcd = q;
        }
    }
    return gcd;
}

// O(log(x*y))
template <class T>
T GCDEuclidean(T x, T y) {
    static_assert(std::is_unsigned<T>::value, "Unsigned type required");

    if (x < y) {
        std::swap(x, y);
    }

    if (x == 0) {
        return y;
    }
    if (y == 0) {
        return x;
    }

    T q = x / y;
    T r = x % y;
    while (r != 0) {
        x = y;
        y = r;
        q = x / y;
        r = x % y;
    }
    return y;
}

int main() {
    unsigned long x, y;
    std::cerr << "x:\t";
    std::cin >> x;
    std::cerr << "y:\t";
    std::cin >> y;

    {
        auto t0 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
        unsigned long gcd = GCDNaive(x, y);
        auto t1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
        std::cerr << "gcd (naive):\t\t" << gcd << "\t" << (t1 - t0).count() << " (mcs)" << std::endl;
    }

    {
        auto t0 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
        unsigned long gcd = GCDEuclidean(x, y);
        auto t1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
        std::cerr << "gcd (Euclidean):\t" << gcd << "\t" << (t1 - t0).count() << " (mcs)" << std::endl;
    }
}
