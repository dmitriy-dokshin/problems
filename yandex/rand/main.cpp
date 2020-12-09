#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>

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
    map<int, size_t> counts;
    for (size_t i = 0; i < 2000000; i++) {
        counts[rand29()]++;
    }
    for (const auto& x : counts) {
        cerr << x.first << "\t" << x.second << endl;
    }
}
