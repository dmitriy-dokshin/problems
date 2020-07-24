#include <iostream>
#include <optional>
#include <vector>
#include <utility>

#include <lib/io/io.h>

using namespace std;

vector<int> single_number(const vector<int>& nums) {
    int xor_res = 0;
    for (const auto& x : nums) {
        xor_res ^= x;
    }

    int mask = 1;
    while (!(xor_res & mask)) {
        mask <<= 1;
    }

    int res1 = 0;
    int res2 = 0;
    for (const auto& x : nums) {
        if (x & mask) {
            res1 ^= x;
        } else {
            res2 ^= x;
        }
    }

    return {res1, res2};
}

int main() {
    vector<int> nums{2, 14, 5, 3, 14, 299, 2, 5, 51, 51};
    cerr << nums << endl;
    cerr << single_number(nums) << endl;
}
