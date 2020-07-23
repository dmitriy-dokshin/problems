#include <lib/matrix/matrix.h>

#include <cmath>
#include <limits>
#include <optional>
#include <queue>

using namespace std;

template <class T, class F>
bool go(const TMatrix<T>& m, const F& is_possible, TMatrix<optional<bool>>& visited, queue<pair<size_t, size_t>>& q, bool flag) {
    auto p = q.front();
    q.pop();

    if (visited.at(p)) {
        return *visited.at(p) != flag;
    }

    visited.at(p) = flag;

    if (p.first > 0) {
        pair<size_t, size_t> p1(p.first - 1, p.second);
        if (is_possible(m, p, p1)) {
            q.emplace(move(p1));
        }
    }

    if (p.second > 0) {
        pair<size_t, size_t> p1(p.first, p.second - 1);
        if (is_possible(m, p, p1)) {
            q.emplace(move(p1));
        }
    }

    if (p.first + 1 < m.height()) {
        pair<size_t, size_t> p1(p.first + 1, p.second);
        if (is_possible(m, p, p1)) {
            q.emplace(move(p1));
        }
    }

    if (p.second + 1 < m.width()) {
        pair<size_t, size_t> p1(p.first, p.second + 1);
        if (is_possible(m, p, p1)) {
            q.emplace(move(p1));
        }
    }

    return false;
}

template <class T>
bool route_exists(const TMatrix<T>& m, const T k) {
    TMatrix<optional<bool>> visited(m.height(), m.width());;

    queue<pair<size_t, size_t>> q1;
    q1.emplace(0, 0);

    queue<pair<size_t, size_t>> q2;
    q2.emplace(m.height() - 1, m.width() - 1);

    auto is_possible = [k](const TMatrix<T>& m, const pair<size_t, size_t>& source, const pair<size_t, size_t>& target) {
        return abs(m.at(target) - m.at(source)) <= k;
    };

    while (!q1.empty() && !q2.empty()) {
        if (go(m, is_possible, visited, q1, false) || go(m, is_possible, visited, q2, true)) {
            return true;
        }
    }

    return false;
}

template <class T>
T min_k(const TMatrix<T>& m) {
    T min_val = numeric_limits<T>::max();
    T max_val = numeric_limits<T>::min();
    for (size_t i = 0; i < m.height(); i++) {
        for (size_t j = 0; j < m.width(); j++) {
            const T& val = m.at(i, j);
            min_val = min(min_val, val);
            max_val = max(max_val, val);
        }
    }

    while (min_val < max_val) {
        T k = min_val + (max_val - min_val) / 2;
        if (route_exists(m, k)) {
            max_val = k;
        } else {
            min_val = k + 1;
        }
    }
    return min_val;
}

int main() {
    random_device rd;
    auto m = random_matrix<int>(5, 5, 0, 5, rd());
    cerr << m;
    cerr << "min_k: " << min_k(m) << endl;
}
