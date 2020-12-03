#include <iostream>
#include <vector>

#include <lib/io/io.h>
#include <lib/random/random.h>

using namespace std;

// Count of [i, j] segments such as a[i] * a[i + 1] * ... * a[j] < target
// a[i] >= 1
// target >= 1
template <class T>
size_t count_multiplication_segments(const vector<T>& v, const T& target) {
    size_t begin = 0;
    size_t end = 0;
    T product = 1;
    size_t result = 0;
    while (begin < v.size()) {
        size_t end_prev = end;
        while (end < v.size() && product * v[end] < target) {
            product *= v[end];
            end++;
        }

        static const auto f = [](size_t n) { return n * (n + 1) / 2; };
        if (end != end_prev) {
            result += f(end - begin) - f(end_prev - begin);
        }

        product /= v[begin];
        begin++;
    }

    return result;
}

template <class T>
size_t count_multiplication_segments_naive(const vector<T>& v, const T& target) {
    size_t result = 0;
    for (size_t i = 0; i < v.size(); i++) {
        T product = 1;
        for (size_t j = i; j < v.size() && product * v[j] < target; j++) {
            product *= v[j];
            result++;
        }
    }
    return result;
}

int main() {
    random_device rd;
    vector<int> v = TRandom<int>::random_vector(10, 1, 10, rd());
    cerr << v << endl;
    int target = 100;
    cerr << "count_multiplication_segments\t" << count_multiplication_segments(v, target) << endl;
    cerr << "count_multiplication_segments_naive\t" << count_multiplication_segments_naive(v, target) << endl;
}
