#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "{";
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << ", " << v[i];
        }
    }
    out << "}";
    return out;
}

template <class T>
void Merge(vector<T>& v, size_t begin, size_t middle, size_t end, size_t& swaps) {
    size_t i = begin;
    size_t j = middle;
    while (i < middle && j < end) {
        if (v[j] < v[i]) {
            auto val = std::move(v[j]);
            for (size_t k = j; k > i; k--) {
                v[k] = std::move(v[k - 1]);
            }
            v[i] = std::move(val);
            j++;
            middle++;
            swaps++;
        }
        i++;
    }
}

template <class T>
void Sort(vector<T>& v, size_t begin, size_t end, size_t& swaps) {
    if (end - begin < 2) {
        return;
    }

    size_t middle = (begin + end) / 2;
    Sort(v, begin, middle, swaps);
    Sort(v, middle, end, swaps);
    Merge(v, begin, middle, end, swaps);
}

int main() {
    vector<int> v {7, 5, 3, 1};
    size_t swaps = 0;
    Sort(v, 0, v.size(), swaps); 
    cerr << v << endl;
    cerr << swaps << endl;
}
