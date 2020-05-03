#include <iostream>
#include <vector>

using namespace std;

vector<bool> build_lockers(const size_t n) {
    vector<bool> lockers(n);
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = i - 1; j < n; j += i) {
            lockers[j] = !lockers[j];
        }
    }
    return lockers;
}

int main() {
    const size_t n = 1000;
    vector<bool> lockers = build_lockers(n);
    size_t open_count = 0;
    for (size_t i = 0; i < n; i++) {
        if (lockers[i]) {
            open_count++;
        }
        cerr << (i + 1) << "\t" << open_count << endl;
    }
}
