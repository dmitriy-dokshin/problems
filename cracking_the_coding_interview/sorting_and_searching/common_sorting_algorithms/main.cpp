#include <lib/algorithm/sorting/bubble_sort.h>
#include <lib/algorithm/sorting/merge_sort.h>
#include <lib/algorithm/sorting/quick_sort.h>
#include <lib/algorithm/sorting/radix_sort.h>
#include <lib/algorithm/sorting/selection_sort.h>
#include <lib/algorithm/sorting/utility.h>
#include <lib/io/io.h>
#include <lib/random/random.h>

#include <stdexcept>

using namespace std;

template <class T>
void verify(const vector<T>& v) {
    if (!is_sorted(v)) {
        throw runtime_error("Sorting is invalid");
    }
}

template <class T, class F>
void test_sort(const vector<T>& v, F sort, const char* name) {
    auto tmp = v;
    sort(tmp);
    cerr << name << endl;
    cerr << tmp << endl << endl;
    verify(tmp);
}

int main() {
    random_device rd;
    auto v = TRandom<int>::random_vector(10, 1, 5, rd());
    cerr << v << endl << endl;

    test_sort(v, bubble_sort<typename decltype(v)::value_type>, "bubble_sort");
    test_sort(v, selection_sort<typename decltype(v)::value_type>, "selection_sort");
    test_sort(v, merge_sort<typename decltype(v)::value_type>, "merge_sort");
    test_sort(v, quick_sort<typename decltype(v)::value_type>, "quick_sort");
    test_sort(v, radix_sort<typename decltype(v)::value_type>, "radix_sort");
}
