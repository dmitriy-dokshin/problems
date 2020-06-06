#include <lib/io/io.h>
#include <lib/random/random.h>

using namespace std;

template <class T>
size_t max_index(const vector<T>& v, const vector<size_t>& indexes) {
    size_t max_i = indexes[0];
    for (const auto& i : indexes) {
        if (i < v.size() && v[i] > v[max_i]) {
            max_i = i;
        }
    }
    return max_i;
}

template <class T>
void peaks_and_valleys(vector<T>& v) {
    for (size_t i = 1; i < v.size(); i += 2) {
        size_t max_i = max_index(v, {i - 1, i, i + 1});
        if (max_i != i) {
            swap(v[i], v[max_i]);
        }
    }
}

int main() {
    random_device rd;
    auto v = TRandom<int>::random_vector_unique(10, 1, 30, rd());
    cerr << v << endl;
    peaks_and_valleys(v);
    cout << v << endl;
}
