#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

// see Insertion Sort Advanced Analysis https://www.hackerrank.com/challenges/insertion-sort/problem

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
size_t Merge(vector<T>& v, vector<T>& tmp, size_t begin, size_t middle, size_t end) {
    size_t inversions = 0;
    size_t i = begin;
    size_t j = middle;
    size_t k = begin;
    while (i < middle && j < end) {
        if (v[j] < v[i]) {
            tmp[k++] = std::move(v[j++]);
            inversions += middle - i;
        } else {
            tmp[k++] = std::move(v[i++]);
        }
    }
    while (i < middle) {
        tmp[k++] = std::move(v[i++]);
    }
    while (j < end) {
        tmp[k++] = std::move(v[j++]);
    }
    for (k = begin; k < end; k++) {
        v[k] = std::move(tmp[k]);
    }
    return inversions;
}

template <class T>
size_t MergeSort(vector<T>& v, vector<T>& tmp, size_t begin, size_t end) {
    if (end - begin < 2) {
        return 0;
    }

    size_t inversions = 0;
    size_t middle = (begin + end) / 2;
    inversions += MergeSort(v, tmp, begin, middle);
    inversions += MergeSort(v, tmp, middle, end);
    inversions += Merge(v, tmp, begin, middle, end);
    return inversions;
}

template <class T>
size_t MergeSort(vector<T>& v) {
    vector<T> tmp(v.size());
    return MergeSort(v, tmp, 0, v.size());
}

int main() {
    vector<int> v {2, 1, 3, 1, 2};
    cerr << v << endl;
    cerr << MergeSort(v) << endl; 
}
