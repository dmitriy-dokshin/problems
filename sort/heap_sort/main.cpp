#include <iostream>
#include <stdexcept>
#include <cstdlib>
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

inline size_t Left(size_t i) {
    return 2 * i + 1; // 2 * i for 1 based indexing
}

inline size_t Right(size_t i) {
    return 2 * (i + 1); // 2 * i + 1 for 1 based indexing
}

inline size_t Parent(size_t i) {
    if (i == 0) {
        throw runtime_error("Root item has no parent");
    }

    if (i % 2 == 1) {
        return (i - 1) / 2; // left
    } else {
        return i / 2 - 1; // right
    }
}

template <class T>
void HeapifyUp(vector<T>& heap, size_t i) {
    while (i > 0) {
        size_t parent = Parent(i);
        if (heap[parent] < heap[i]) {
            swap(heap[i], heap[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

template <class T>
void HeapifyDown(vector<T>& heap, size_t size) {
    size_t i = 0;
    size_t left = Left(i);
    size_t right = Right(i);
    while (left < size || right < size) {
        size_t max = i;
        if (left < size && heap[left] > heap[max]) {
            max = left;
        }
        if (right < size && heap[right] > heap[max]) {
            max = right;
        }
        if (max != i) {
            swap(heap[i], heap[max]);
            i = max;
            left = Left(i);
            right = Right(i);
        } else {
            break;
        }
    }
}

template <class T>
void HeapSort(vector<T>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        HeapifyUp(v, i);
    }

    size_t size = v.size();
    while (size > 1) {
        swap(v[0], v[size - 1]);
        size--;
        HeapifyDown(v, size);
    }
}

template <class T>
bool IsSorted(const vector<T>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        if (!(v[i - 1] < v[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    size_t n = 1000;
    vector<int> v;
    v.reserve(n);
    for (size_t i = 0; i < n; i++) {
        v.emplace_back(rand());
    }

    HeapSort(v);

    cerr << (IsSorted(v) ? "OK" : "ERROR") << endl;
}
