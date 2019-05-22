#include <iostream>
#include <vector>
#include <utility>

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
void BubbleSort(vector<T>& v) {
    bool swapped;
    do {
        swapped = false;
        for (size_t i = 1; i < v.size(); i++) {
            if (v[i] < v[i - 1]) {
                swap(v[i], v[i - 1]);
                swapped = true;
            }
        }
        if (swapped) {
            cerr << v << endl;
        }
    } while (swapped);
}

int main() {
    vector<int> v {9, 8, 7, 6, 5, 4, 3, 2, 1};
    cerr << v << endl;
    BubbleSort(v);
}
