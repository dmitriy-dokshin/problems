#include <lib/algorithm/sorting/quick_sort.h>
#include <lib/random/random.h>
#include <lib/io/io.h>

using namespace std;

template <class T>
void sorted_merge(vector<T>& a, vector<T>& b) {
    size_t size = a.size();
    a.resize(a.size() + b.size());
    for (size_t i = size; i > 0; i--) {
        a[a.size() - (size - i) - 1] = move(a[i - 1]);
    }
    size_t i = a.size() - size;
    size_t j = 0;
    size_t k = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) {
            a[k++] = move(a[i++]);
        } else {
            a[k++] = move(b[j++]);
        }
    }
    while (i < a.size()) {
        a[k++] = move(a[i++]);
    }
    while (j < b.size()) {
        a[k++] = move(b[j++]);
    }
}

int main() {
    random_device rd;

    auto a = TRandom<int>::random_vector(10, 0, 9, rd());
    quick_sort(a);
    cerr << a << endl;

    auto b = TRandom<int>::random_vector(5, 0, 9, rd());
    quick_sort(b);
    cerr << b << endl;

    sorted_merge(a, b);
    cerr << a << endl;
}
