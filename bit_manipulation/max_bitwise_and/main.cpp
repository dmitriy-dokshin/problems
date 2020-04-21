#include <iostream>

using namespace std;

template <class T>
T MaxBitwiseAnd(T n, T k) {
    auto a = k - 1;
    auto b = a | (a + 1);
    if (b <= n) {
        // includes case when a is even, so (a + 1) & a == a
        return k - 1;
    } else {
        // a is definitely odd and b is greater than n, then we know that k - 2 is even
        return k - 2;
    }
}

int main() {
    unsigned long t;
    cin >> t;

    while (t-- > 0) {
        unsigned long n;
        cin >> n;
        unsigned long k;
        cin >> k;
        cout << MaxBitwiseAnd(n, k) << endl;
    }
}
