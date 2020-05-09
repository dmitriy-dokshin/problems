#include <climits>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <class T>
T multiply(const T& x, const T& y) {
    T result = 0;
    for (size_t i = 0; i < sizeof(T) * CHAR_BIT; i++) {
        if (y & (static_cast<T>(1) << i)) {
            result += x << i;
        }
    }
    return result;
}


class THash {
public:
    template<class TFirst, class TSecond>
    size_t operator()(const pair<TFirst, TSecond>& x) const {
        return hash<TFirst>()(x.first) | hash<TSecond>()(x.second);
    }
};

template <class T>
T recursive_multiply(const T& x, const T& y, unordered_map<pair<T, T>, T, THash>& cache) {
    if (x == 0 || y == 0) {
        return 0;
    }
    if (x == 1) {
        return y;
    }
    if (y == 1) {
        return x;
    }

    auto it = cache.find({x, y});
    if (it != cache.end()) {
        return it->second;
    }

    it = cache.find({y, x});
    if (it != cache.end()) {
        return it->second;
    }

    T x1 = x / 2;
    T x2 = x - x / 2;
    T y1 = y / 2;
    T y2 = y - y / 2;
    T result =
        recursive_multiply(x1, y1, cache) +
        recursive_multiply(x1, y2, cache) +
        recursive_multiply(x2, y1, cache) +
        recursive_multiply(x2, y2, cache);
    return result;
}

template <class T>
T recursive_multiply(const T& x, const T& y) {
    unordered_map<pair<T, T>, T, THash> cache;
    return recursive_multiply(x, y, cache);
}

int main() {
    unsigned long x, y;
    cin >> x >> y;

    cout << (x * y) << endl;
    cout << multiply(x, y) << endl;
    cout << recursive_multiply(x, y) << endl;
}
