#include <lib/algorithm/searching/binary_search.h>
#include <lib/algorithm/sorting/quick_sort.h>
#include <lib/random/random.h>

#include <iostream>

using namespace std;

int main() {
    random_device rd;
    auto v = TRandom<int>::random_vector(10, 1, 5, rd());
    quick_sort(v);
    for (size_t i = 0; i < v.size(); i++) {
        cerr << i << "\t" << v[i] << endl;
    }

    int value;
    cin >> value;
    auto result = binary_search(v, value);
    cerr << result.first << "\t" << result.second << endl;
}
