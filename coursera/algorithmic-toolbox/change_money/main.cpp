#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

template <class T>
istream& operator>>(istream& in, vector<T>& v) {
    T val;
    while (v.size() < v.capacity()) {
        in >> val;
        v.emplace_back(move(val));
    }
    return in;
}

template <class T>
size_t change_money(const vector<T>& coins, const T target) {
    vector<size_t> result;
    result.resize(target + 1);
    for (size_t t = 1; t < result.size(); t++) {
        for (const auto& coin : coins) {
            if (coin <= t) {
                size_t count = result[t - coin] + 1;
                result[t] = result[t] > 0 ? min(result[t], count) : count;
            }
        }
    }

    return result[target];
}

int main() {
    size_t n;
    cin >> n;

    vector<int> coins;
    coins.reserve(n);
    cin >> coins;

    int target;
    while (cin >> target) {
        cout << change_money(coins, target) << endl;
    }
}
