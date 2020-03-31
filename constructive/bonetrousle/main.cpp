#include <algorithm>
#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;

template <class T>
istream& operator>>(istream& in, vector<T>& v) {
    T val;
    while (v.size() < v.capacity()) {
        in >> val;
        v.emplace_back(move(val));
    }
    return in;
}

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << " " << v[i];
        }
    }
    return out;
}

template <class T>
vector<T> bonetrousle(T n, T k, T b) {
    static_assert(is_integral<T>::value && is_unsigned<T>::value, "Type has to be integral and unsigned");

    T min_sum = b * (b + 1) / 2;
    T max_sum = k * b - b * (b - 1) / 2; // k * (k + 1) / 2 - (k - b) * (k - b + 1) / 2;
    if (n < min_sum || n > max_sum) {
        return {};
    }

    T sum = min_sum;
    vector<T> result;
    result.reserve(b);
    for (T x = b; x > 0; x--) {
        if (sum < n) {
            T max_x = min(k, x + (n - sum));
            sum += max_x - x;
            k = max_x - 1;
            result.emplace_back(max_x);
        } else {
            result.emplace_back(x);
        }
    }

    // For verbosity
    reverse(result.begin(), result.end());

    return result;
}

int main() {
    size_t t;
    cin >> t;

    while (t > 0) {
        vector<unsigned long> input;
        input.reserve(3);
        cin >> input;
        auto result = bonetrousle(input.at(0), input.at(1), input.at(2));
        if (result.empty()) {
            cout << "-1" << endl;
        } else {
            cout << result << endl;
        }
        t--;
    }
}
