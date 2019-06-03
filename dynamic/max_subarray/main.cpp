#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace std;

long MaxSubArr(const vector<int>& arr) {
    if (arr.empty()) {
        throw runtime_error("The array is empty");
    }

    long dp = arr[0];
    long maxSum = dp;
    for (size_t i = 1; i < arr.size(); i++) {
        dp = max(dp + arr[i], static_cast<long>(arr[i])); 
        if (dp > maxSum) {
            maxSum = dp;
        }
    }

    return maxSum;
}

long MaxSubSeq(const vector<int>& arr) {
    if (arr.empty()) {
        throw runtime_error("The array is empty");
    }

    int maxNonPositive = numeric_limits<int>::min();
    int sumPositive = 0;
    for (const auto& x : arr) {
        if (x > 0) {
            sumPositive += x;
        } else if (x > maxNonPositive) {
            maxNonPositive = x;
        }
    }

    return sumPositive > 0 ? sumPositive : maxNonPositive;
}

template <class T>
vector<T> ReadVector() {
    size_t n;
    cin >> n;
    cin.ignore();
    vector<T> arr;
    arr.reserve(n);
    for (size_t i = 0; i < n; i++) {
        T val;
        cin >> val;
        arr.emplace_back(move(val));
    }
    cin.ignore();
    return arr;
}

int main() {
    ofstream out(getenv("OUTPUT_PATH"));

    size_t t;
    cin >> t;
    cin.ignore();
    for (size_t i = 0; i < t; i++) {
        auto arr = ReadVector<int>();
        out << MaxSubArr(arr) << " " << MaxSubSeq(arr) << endl;
    }
}
