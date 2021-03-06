#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <class T>
bool operator==(const vector<T>& v1, const vector<T>& v2) {
    if (v1.size() == v2.size()) {
            for (size_t i = 0; i < v1.size(); i++) {
            if (v1[i] != v2[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

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

size_t SelectPivot(size_t from, size_t to) {
    return (from + to) / 2;
}

template <class T>
pair<size_t, size_t> Partition2(vector<T>& v, size_t from, size_t to) {
    swap(v[SelectPivot(from, to)], v[to - 1]);
    size_t j = from; 
    for (size_t i = from; i < to - 1; i++) {
        if (v[i] < v[to - 1]) {
            swap(v[i], v[j]);
            j++;
        }
    }
    swap(v[j], v[to - 1]);
    return {j, j + 1};
}

template <class T>
pair<size_t, size_t> Partition3(vector<T>& v, size_t from, size_t to) {
    auto val = v[SelectPivot(from, to)];
    size_t i = 0;
    while (from + i < to) {
        if (v[from + i] < val) {
            swap(v[from + i], v[from]);
            from++;
        } else if (v[from + i] > val) {
            swap(v[from + i], v[to - 1]);
            to--;
        } else {
            i++;
        }
    }
    return {from, to};
}

template <class T>
void QuickSort(vector<T>& v, size_t from, size_t to) {
    if (from == to) {
        return;
    }

    auto res = Partition2(v, from, to);
    QuickSort(v, from, res.first);
    QuickSort(v, res.second, to);
}

template <class T>
void QuickSort(vector<T>& v) {
    QuickSort(v, 0, v.size());
}

int main() {
    vector<pair<vector<int>, vector<int>>> tests {
        {{5, 2, 3, 1, 4}, {1, 2, 3, 4, 5}},
        {{1, 10, 5, 2, 7, 4, 3, 8, 9, 6}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
    };
    for (auto& test : tests) {
        QuickSort(test.first);
        const bool ok = test.first == test.second;
        cerr << (ok ? "OK" : "ERROR");
        if (!ok) {
            cerr << "\t" << test.first << " != " << test.second;
        }
        cerr << endl;
    }
}
