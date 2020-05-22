#include <iostream>
#include <utility>
#include <vector>

using namespace std;

size_t coins(const size_t n, const vector<size_t>& coins_set) {
    vector<size_t> result(n + 1);
    result[0] = 1;
    for (size_t i = 1; i <= n; i++) {
        size_t x = 0;
        for (const size_t c : coins_set) {
            if (c <= i) {
                x += result[i - c];
            }
        }
        result[i] = x;
    }
    return result[n];
}

size_t coins_optimized(const size_t n, const vector<size_t>& coins_set) {
    size_t max_coin = 0;
    for (const size_t c : coins_set) {
        max_coin = max(max_coin, c);
    }

    vector<size_t> result(max_coin + 1);
    result[0] = 1;
    for (size_t i = 1; i <= n; i++) {
        size_t x = 0;
        for (const size_t c : coins_set) {
            if (c <= i) {
                x += result[(i - c) % result.size()];
            }
        }
        result[i % result.size()] = x;
    }
    return result[n % result.size()];
}

int main() {
    vector<size_t> coins_set{1, 5, 10, 25};
    bool has_error = false;
    for (size_t n = 1; n < 1000; n++) {
        size_t result = coins(n, coins_set);
        size_t result_optimized = coins_optimized(n, coins_set);
        if (result != result_optimized) {
            cerr << n << ": " << result << " != " << result_optimized << endl;
            has_error = true;
            break;
        }
    }
    if (!has_error) {
        cerr << "Done." << endl;
    }
}
