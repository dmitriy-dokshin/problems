#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int rand6() {
    return rand() % 6;
}

int rand2() {
    return rand6() % 2;
}

int rand12() {
    return rand6() * 2 + rand2();
}

int randx(function<int()> f, int limit) {
    int x;
    do {
        x = f();
    } while (x >= limit);
    return x;
}

int rand30() {
    return rand6() * 5 + randx(rand6, 5);
}

int rand29() {
    return randx(rand30, 29);
}

int main() {
    unordered_map<int, size_t> counts;
    for (size_t i = 0; i < 5 * 1000 * 1000; i++) {
        counts[rand29()]++;
    }

    vector<pair<int, size_t>> counts_v(counts.begin(), counts.end());
    sort(counts_v.begin(), counts_v.end());
    for (const auto& x : counts_v) {
        cerr << x.first << "\t" << x.second << endl;
    }
}
