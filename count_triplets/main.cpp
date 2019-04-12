#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

template <class T>
size_t CountTriplets(const vector<T>& arr, const T r) {  
    unordered_map<T, size_t> p1;
    unordered_map<T, size_t> p2;
    size_t p3 = 0;
    for (const auto& x : arr) {
        if (x % r == 0) {
            p3 += p2[x / r];
            p2[x] += p1[x / r];
        }
        p1[x]++;
    }
    return p3;
}

int main() {
    size_t n;
    long r;
    cin >> n;
    cin >> r;
    cin.ignore();

    vector<long> arr(n);
    for (size_t i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cerr << CountTriplets(arr, r) << endl;
}
