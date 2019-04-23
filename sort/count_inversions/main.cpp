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
void Merge(vector<T>& v, vector<T>& tmp, size_t begin, size_t middle, size_t end, size_t& inversions) {
    size_t i = begin;
    size_t j = middle;
    size_t k = begin;
    while (i < middle && j < end) {
        if (v[i] <= v[j]) {
            tmp[k++] = std::move(v[i]);
            i++;
        } else {
            inversions += middle - i;
            tmp[k++] = std::move(v[j]);
            j++;
        }
    }
    while (i < middle) {
        tmp[k++] = std::move(v[i]);
        i++;
    }
    while (j < end) {
        tmp[k++] = std::move(v[j]);
        j++;
    }
    for (k = begin; k < end; k++) {
        v[k] = std::move(tmp[k]);
    }
    cerr << v << endl;
}

template <class T>
void Sort(vector<T>& v, vector<T>& tmp, size_t begin, size_t end, size_t& inversions) {
    if (end - begin < 2) {
        return;
    }

    size_t middle = (begin + end) / 2;
    Sort(v, tmp, begin, middle, inversions);
    Sort(v, tmp, middle, end, inversions);
    Merge(v, tmp, begin, middle, end, inversions);
}

template <class T>
void Sort(vector<T>& v, size_t& inversions) {
    vector<T> tmp(v.size());
    Sort(v, tmp, 0, v.size(), inversions);
}

int main() {
    vector<int> v {2, 1, 3, 1, 2};
    size_t inversions = 0;
    cerr << v << endl;
    Sort(v, inversions); 
    cerr << inversions << endl;
}
