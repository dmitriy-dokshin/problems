#include <iostream>
#include <vector>

using namespace std;

size_t triple_step(const size_t n, const vector<size_t>& steps = {1, 2, 3}) {
    vector<size_t> result(n + 1);
    for (size_t i = 1; i <= n; i++) {
        for (const auto& x : steps) {
            if (i >= x) {
                result[i] += result[i - x] + 1;
            }
        }
    }
    return result[n];
}

int main() {
    size_t n;
    cin >> n;

    size_t ways = triple_step(n);
    cout << ways << endl;
}
