#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

bool IsPrime(unsigned long n) {
    if (n < 2) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }

    const unsigned long max = static_cast<unsigned long>(sqrt(n));
    for (unsigned long a = 3; a <= max; a += 2) {
        if (n % a == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<pair<unsigned long, bool>> tests {
        {1, false},
        {2, true},
        {3, true},
        {4, false},
        {5, true},
        {6, false},
        {1000, false},
        {1001, false}
    };
    for (const auto& x : tests) {
        const bool ok = IsPrime(x.first) == x.second;
        cerr << x.first << "\t" << (ok ? "OK" : "ERROR") << endl;
    }
}
