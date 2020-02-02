#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

template <class T>
size_t count_subarrays_with_sum(const vector<T>& v, const T& target) {
    size_t count = 0;
    unordered_set<T> sums;
    T sum = 0;
    for (const auto& x : v) {
        sum += x;
        sums.emplace(sum);
        if (sum == target || sums.find(sum - target) != sums.end()) {
            count++;
        }
    }
    return count;
}

int main() {
    vector<int> v{1, 2, 3, -4, 5};
    cerr << count_subarrays_with_sum(v, 1) << endl;
}
