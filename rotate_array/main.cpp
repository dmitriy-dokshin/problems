#include <functional>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (const auto& x : v) {
        out << x << "\t";
    }
    return out;
}

template <class T>
void Rotate(vector<T>& v, size_t n, std::function<size_t(size_t)> index = [](const size_t i) { return i; }) {
    size_t size = v.size();
    while (size > 1) {
        for (size_t k = 0; k < n; k++) {
            for (size_t i = k + n; i < size; i += n) {
                swap(v[index(k)], v[index(i)]);
            }
        }

        const size_t newSize = n;
        const size_t newN = n - size % n;
        size = newSize;
        n = newN;
    }
}

template <class T>
void RotateRight(vector<T>& v, size_t n) {
    Rotate(v, n);
}

template <class T>
void RotateLeft(vector<T>& v, size_t n) {
    Rotate(v, n, [&v](const size_t i) { return v.size() - 1 - i; });
}

int main() {
    vector<int> v {1, 2, 3, 4, 5};
    cerr << v << endl;
    RotateRight(v, 3);
    cerr << v << endl;
    RotateLeft(v, 3);
    RotateLeft(v, 3);
    cerr << v << endl;
}
