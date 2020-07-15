#include <climits>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

using namespace std;

template <class T>
bool get_bit(const T& x, size_t n) {
    return (static_cast<T>(1) << n) & x;
}

template <class T>
void set_bit(T& x, size_t n) {
    x |= (static_cast<T>(1) << n);
}

template <class T>
T next(T x) {
    T result = 0;
    size_t size = sizeof(T) * CHAR_BIT;
    for (size_t i = 1; i < size - 1; i++) {
        if (get_bit(x, i - 1) == get_bit(x, i + 1)) {
            set_bit(result, i);
        }
    }
    return result;
}

template <class T>
T from_vector(const vector<bool>& v) {
    size_t size = sizeof(T) * CHAR_BIT;
    if (v.size() != size) {
        throw runtime_error("Invalid input");
    }

    T x = 0;
    for (size_t i = 0; i < size; i++) {
        if (v.at(i)) {
            set_bit(x, i);
        }
    }
    return x;
}

template <class T>
vector<bool> to_vector(const T& x) {
    size_t size = sizeof(T) * CHAR_BIT;
    vector<bool> v(size);
    for (size_t i = 0; i < size; i++) {
        v.at(i) = get_bit(x, i);
    }
    return v;
}

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "[";
    if (v.size() > 0) {
        out << v.at(0);
        for (size_t i = 1; i < v.size(); i++) {
            out << ", " << v.at(i);
        }
    }
    out << "]";
    return out;
}

template <>
ostream& operator<<<unsigned char>(ostream& out, const vector<unsigned char>& v) {
    out << "[";
    if (v.size() > 0) {
        out << to_vector(v.at(0));
        for (size_t i = 1; i < v.size(); i++) {
            out << "\n" << i << " " << to_vector(v.at(i));
        }
    }
    out << "]";
    return out;
}

vector<bool> prison_cells_after_n_days(const vector<bool>& cells, size_t n) {
    using T = unsigned char;
    
    T x = from_vector<T>(cells);
    
    vector<T> values{x};
    unordered_map<T, size_t> values_indexes{{x, 0}};
    while (n > 0 && values_indexes.emplace(next(x), values.size()).second) {
        x = next(x);
        values.emplace_back(x);
        n--;
    }
    cerr << values << endl;

    if (n > 0) {
        x = next(x);
        n--;
        size_t period = values.size() - values_indexes.at(x);
        cerr << period << endl;
        n %= period;
        x = values.at(values_indexes.at(x) + n);
    }

    return to_vector(x);
}

int main() {
    vector<bool> cells{1,0,0,1,0,0,1,0};
    vector<bool> result = prison_cells_after_n_days(cells, static_cast<int>(1000000000)); // LeetCode bug
    cout << result << endl;
}
