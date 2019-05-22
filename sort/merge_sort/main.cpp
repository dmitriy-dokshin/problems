#include <iostream>
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
void Merge(vector<T>& v, vector<T>& tmp, size_t begin, size_t middle, size_t end) {
    size_t i = begin;
    size_t j = middle;
    size_t k = begin;
    while (i < middle && j < end) {
        tmp[k++] = move(v[i] < v[j] ? v[i++] : v[j++]);
    }
    while (i < middle) {
        tmp[k++] = move(v[i++]);
    }
    while (j < end) {
        tmp[k++] = move(v[j++]);
    }
    for (k = begin; k < end; k++) {
        v[k] = move(tmp[k]);
    }
}

template <class T>
void MergeSort(vector<T>& v, vector<T> tmp, size_t begin, size_t end) {
    if (end - begin < 2) {
        return;
    }

    size_t middle = (begin + end) / 2;
    MergeSort(v, tmp, begin, middle);
    MergeSort(v, tmp, middle, end);
    Merge(v, tmp, begin, middle, end);
}

template <class T>
void MergeSort(vector<T>& v) {
    vector<T> tmp(v.size());
    MergeSort(v, tmp, 0, v.size());
}

int main() {
    vector<int> v {9, 8, 7, 6, 5, 4, 3, 2, 1};
    cerr << v << endl;
    MergeSort(v);
    cerr << v << endl;
}
