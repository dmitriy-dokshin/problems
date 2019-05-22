#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "{";
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << " " << v[i];
        }
    }
    out << "}";
    return out;
}

template <class T>
void InsertionSort(vector<T>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        size_t j = i - 1;
        for (; j > 0; j--) {
            if (v[j + 1] < v[j]) {
                swap(v[j + 1], v[j]);
            }
        }
        if (v[j + 1] < v[j]) {
            swap(v[j + 1], v[j]);
        }
        cerr << v << endl;
    }
}

int main() {
    vector<int> v {9, 8, 7, 6, 5, 4, 3, 2, 1};
    cerr << v << endl;
    InsertionSort(v);
}
