#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <class TFirst, class TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond>& p) {
    return out << "{" << p.first << ", " << p.second << "}";
}

template <class T>
pair<size_t, size_t> FindSegmentWithSum(vector<T>& v, const T targetSum) {
    for (size_t i = 1; i < v.size(); i++) {
        v[i] += v[i - 1];
    }
    unordered_map<T, size_t> rightSums;
    for (size_t i = 0; i < v.size(); i++) {
        T sum = v[v.size() - 1];
        if (i > 0) {
            sum -= v[i - 1];
        }
        rightSums[sum] = i;
    }
    for (size_t i = 0; i < v.size(); i++) {
        T sum = v[v.size() - 1];
        if (i > 0) {
            sum -= v[i - 1];
        }
        if (sum < targetSum) {
            break;
        }
        if (sum == targetSum) {
            return {i, v.size() - 1};
        }
        auto j = rightSums.find(sum - targetSum);
        if (j != rightSums.end() && i < j->second) {
            return {i, j->second - 1};
        }
    }
    throw runtime_error("Unable to find target sum");
}

int main() {
    vector<int> v{1, 2, 3, 4, 5};
    cerr << FindSegmentWithSum(v, 4) << endl;
}
