#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using TResult = tuple<unsigned long, unsigned long, unsigned long>;

ostream& operator<<(ostream& out, const TResult& result) {
    out << "{" << get<0>(result) << ", " << get<1>(result) << ", " << get<2>(result) << "}";
    return out;
}

TResult MaxBitwiseAndBruteForce(const unsigned long n, const unsigned long k) {
    TResult result;
    for (unsigned long i = 1; i < n; i++) {
        for (unsigned long j = i + 1; j <= n; j++) {
            const auto val = i & j;
            if (val < k && val > get<2>(result)) {
                result = {i, j, val};
            }
        }
    }
    return result;
}

TResult MaxBitwiseAnd(const unsigned long n, const unsigned long k) {
    const auto a = k - 1;
    const auto b = a | (a + 1);
    if (b <= n) {
        // includes case when a is even, so (a + 1) & a == a
        return {a, b, a & b}; // a & b == a
    } else {
        // a is definitely odd and b is greater than n, then we know that k - 2 is even
        return {k - 2, k - 1, k - 2};
    }
}

int main() {
    const unsigned n = 100;
    for (unsigned long k = 2; k <= n; k++) {
        const bool ok = MaxBitwiseAndBruteForce(n, k) == MaxBitwiseAnd(n, k);
        cerr << k << "\t";
        if (!ok) {
            cerr << MaxBitwiseAndBruteForce(n, k) << " != " << MaxBitwiseAnd(n, k) << endl;
            break;
        } else {
            cerr << MaxBitwiseAnd(n, k) << endl;
        }
    }
}
