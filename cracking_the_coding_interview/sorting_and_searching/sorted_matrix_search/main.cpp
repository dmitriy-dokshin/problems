#include <lib/matrix/matrix.h>
#include <lib/random/random.h>

#include <algorithm>
#include <utility>

using namespace std;

template <class F>
void iterate(size_t i, size_t j, size_t w, const F& f) {
    while (i > 0 && j < w) {
        f(i - 1, j);
        i--;
        j++;
    }
}

template <class F>
void iterate(size_t w, size_t h, const F& f) {
    for (size_t i = 0; i < h; i++) {
        iterate(i + 1, 0, w, f);
    }
    for (size_t j = 1; j < w; j++) {
        iterate(h, j, w, f);
    }
}

template <class F>
size_t find_bound(size_t begin, size_t end, const F& f) {
    if (begin < end) {
        size_t mid = begin + (end - begin) / 2;
        if (f(mid)) {
            return find_bound(mid + 1, end, f);
        } else {
            return find_bound(begin, mid, f);
        }
    } else {
        return begin;
    }
}

template <class T, class F>
void find(
    const TMatrix<T>& m, const T& value,
    size_t i_begin, size_t i_end,
    size_t j_begin, size_t j_end,
    bool horizontal, const F& f) {
    if (i_begin < i_end && j_begin < j_end) {
        if (horizontal) {
            pair<size_t, size_t> result(
                find_bound(j_begin, j_end, [&](size_t j) { return m.at(i_begin, j) < value; }),
                find_bound(j_begin, j_end, [&](size_t j) { return m.at(i_begin, j) <= value; }));
            j_end = result.first;
            // + 1 for deduplication
            for (size_t j = result.first + 1; j < result.second; j++) {
                f(i_begin, j);
            }
        } else {
            pair<size_t, size_t> result(
                find_bound(i_begin, i_end, [&](size_t i) { return m.at(i, j_end - 1) < value; }),
                find_bound(i_begin, i_end, [&](size_t i) { return m.at(i, j_end - 1) <= value; }));
            i_begin = result.first;
            for (size_t i = result.first; i < result.second; i++) {
                f(i, j_end - 1);
            }
        }
        find(m, value, i_begin, i_end, j_begin, j_end, !horizontal, f);
    }
}

template <class T, class F>
void find(const TMatrix<T>& m, const T& value, const F& f) {
    find(m, value, 0, m.height(), 0, m.width(), true, f);
}

int main() {
    size_t min_width = 4;
    size_t max_width = 8;
    size_t min_height = 4;
    size_t max_height = 8;

    random_device rd;

    size_t w = min_width + (rd() % (max_width - min_width));
    size_t h = min_height + (rd() % (max_height - min_height));

    auto v = TRandom<int>::random_vector(w * h, 1, 9, rd());
    sort(v.begin(), v.end());

    TMatrix<typename decltype(v)::value_type> m(w, h);
    size_t k = 0;
    iterate(w, h, [&](size_t i, size_t j) { m.at(i, j) = v.at(k++); });

    cerr << m;

    int value;
    cin >> value;
    find(m, value, [&m](size_t i, size_t j) { cerr << "(" << i << ", " << j << ")\t" << m.at(i, j) << endl; });
}
