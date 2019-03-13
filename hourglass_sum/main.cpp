#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>
#include <utility>

using namespace std;

int hourglassSum(const vector<vector<int>>& arr, const size_t size, const pair<int, int> pos)
{
    int sum = 0;
    auto add = [&](const size_t i, const size_t j) {
        sum += arr[pos.first + i][pos.second + j];
    };
    for (size_t i = 0; i <= size / 2; i++) {
        for (size_t j = i; j < size - i; j++) {
            add(i, j);
        }
    }
    for (size_t i = size - 1; i > size / 2; i--) {
        for (size_t j = size - (i + 1); j < i + 1; j++) {
            add(i, j);
        }
    }
    return sum;
}

int hourglassSum(const vector<vector<int>>& arr, const size_t size)
{
    if (arr.size() < size) {
        throw out_of_range("vertical size is too small");
    }

    int maxSum = numeric_limits<int>::min();
    for (size_t i = 0; i <= arr.size() - size; i++) {
        if (arr[i].size() < size) {
            throw out_of_range("horizontal size is too small");
        }

        for (size_t j = 0; j <= arr[i].size() - size; j++) {
            const int sum = hourglassSum(arr, size, {i, j});
            if (sum > maxSum) {
                maxSum = sum;
            }
        }
    }
    return maxSum;
}

int main() {
    constexpr size_t k = 3;

    vector<pair<vector<vector<int>>, int>> tests {
        {
            {
                {1, 1, 1, 0, 0, 0},
                {0, 1, 0, 0, 0, 0},
                {1, 1, 1, 0, 0, 0},
                {0, 0, 2, 4, 4, 0},
                {0, 0, 0, 2, 0, 0},
                {0, 0, 1, 2, 4, 0}
            },
            19
        },
        {
            {
                {1, 1, 1, 0, 0, 0},
                {0, 1, 0, 0, 0, 0},
                {1, 1, 1, 0, 0, 0},
                {0, 9, 2, -4, -4, 0},
                {0, 0, 0, -2, 0, 0},
                {0, 0, -1, -2, -4, 0}
            },
            13
        },
        {
            {
                {-9, -9, -9, 1, 1, 1},
                {0, -9, 0, 4, 3, 2},
                {-9, -9, -9, 1, 2, 3},
                {0, 0, 8, 6, 6, 0},
                {0, 0, 0, -2, 0, 0},
                {0, 0, 1, 2, 4, 0}
            },
            28
        }
    };

    for (const auto& x : tests) {
        const bool ok = hourglassSum(x.first, k) == x.second;
        cerr << (ok ? "OK" : "ERROR") << endl;
    }
}
