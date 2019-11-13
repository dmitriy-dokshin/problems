#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <random>

size_t parent(size_t i) {
    return (i - 1) / 2;
}

size_t left(size_t i) {
    return 2 * i + 1;
}

size_t right(size_t i) {
    return 2 * i + 2;
}

template <class T, class TComp_>
void heapify(std::vector<T>& v, TComp_ comp) {
    for (size_t i = 1; i < v.size(); i++) {
        size_t j = i;
        while (j > 0 && comp(v[j], v[parent(j)])) {
            std::swap(v[j], v[parent(j)]);
            j = parent(j);
        }
    }
}

template <class T, class TComp_>
T pop_min(std::vector<T>& v, size_t size, TComp_ comp) {
    T min = std::move(v[0]);
    v[0] = std::move(v[size - 1]);
    size--;

    size_t next = 0;
    size_t i = 0;
    do {
        i = next;
        if (left(i) < size && comp(v[left(i)], v[next])) {
            next = left(i);
        }
        if (right(i) < size && comp(v[right(i)], v[next])) {
            next = right(i);
        }
        std::swap(v[i], v[next]);
    } while (next != i);

    return min;
}

template <class T, class TComp_>
void heap_sort(std::vector<T>& v, TComp_ comp) {
    heapify(v, comp);
    for (size_t size = v.size(); size > 1; size--) {
        v[size - 1] = pop_min(v, size, comp);
    }
}

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
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

std::vector<long> prepare_input(long n = 5, size_t dups = 0) {
    std::vector<long> v;
    v.reserve(n);
    for (long x = 1; x <= n; x++) {
        v.emplace_back(x);
        for (size_t i = 0; i < dups; i++) {
            v.emplace_back(x);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(v.begin(), v.end(), g);

    return v;
}

template <class T, class TComp_>
bool is_sorted(const std::vector<T>& v, TComp_ comp) {
    for (size_t i = 1; i < v.size(); i++) {
        if (!comp(v[i - 1], v[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<long> v = prepare_input(9, 1);
    std::cerr << v << std::endl;
    heap_sort(v, std::greater<long>());
    std::cerr << v << std::endl;
    std::cerr << (is_sorted(v, std::less_equal<long>()) ? "OK" : "ERROR") << std::endl;
}
