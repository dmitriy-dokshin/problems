#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using namespace std;

template <class T>
class TPoint {
public:
    TPoint() = default;

    TPoint(T x, T y)
        : X(x)
        , Y(y)
    {
    }

    T X = {};
    T Y = {};
};

template <class T>
vector<TPoint<T>> random_points(size_t n, T min, T max) {
    random_device rd;
    mt19937 x_gen(rd());
    mt19937 y_gen(rd());
    uniform_real_distribution<T> dist(min, max);

    vector<TPoint<T>> points;
    points.reserve(n);
    for (size_t i = 0; i < n; i++) {
        points.emplace_back(dist(x_gen), dist(y_gen));
    }

    return points;
}

template <class T>
T distance(const TPoint<T>& p1, const TPoint<T>& p2) {
    return sqrt(pow(p1.X - p2.X, 2) + pow(p1.Y - p2.Y, 2));
}

template <class T, class P>
vector<T> where(const vector<T>& v, P pred) {
    vector<T> res;
    for (const auto& x : v) {
        if (pred(x)) {
            res.emplace_back(x);
        }
    }
    return res;
}

template <class T>
T min_distance(const vector<TPoint<T>>& points_x, const vector<TPoint<T>>& points_y, size_t begin, size_t end) {
    if (end - begin < 2) {
        return numeric_limits<T>::max();
    } else if (end - begin == 2) {
        return distance(points_x[begin], points_x[begin + 1]);
    }

    size_t mid = begin + (end - begin) / 2;
    T xmid = points_x[mid].X;
    T ld = min_distance(points_x, where(points_y, [&](const auto& p) { return p.X < xmid; }), begin, mid);
    T rd = min_distance(points_x, where(points_y, [&](const auto& p) { return p.X >= xmid; }), mid, end);
    T d = min(ld, rd);
    const auto points_y_d = where(points_y, [&](const auto& p) { return p.X >= xmid - d && p.X < xmid + d; });
    for (size_t i = 0; i < points_y_d.size() - 1; i++) {
        for (size_t j = i + 1; j < points_y_d.size() && points_y_d[j].Y - points_y_d[i].Y < d; j++) {
            d = min(d, distance(points_y_d[i], points_y_d[j]));
        }
    }

    return d;
}

template <class T>
T min_distance(const vector<TPoint<T>>& points) {
    auto points_x = points;
    sort(points_x.begin(), points_x.end(), [](const auto& p1, const auto& p2) { return p1.X < p2.X; });

    auto points_y = points;
    sort(points_y.begin(), points_y.end(), [](const auto& p1, const auto& p2) { return p1.Y < p2.Y; });

    return min_distance(points_x, points_y, 0, points_x.size());
}

template <class T>
T min_distance_naive(const vector<TPoint<T>>& points) {
    T d = numeric_limits<T>::max();
    for (size_t i = 0; i < points.size() - 1; i++) {
        for (size_t j = i + 1; j < points.size(); j++) {
            d = min(d, distance(points[i], points[j]));
        }
    }

    return d;
}

int main() {
    vector<size_t> sizes{1000, 5000, 10000};
    for (const size_t n : sizes) {
        auto points = random_points(n, -100.0f, 100.0f);
        cerr << "n: " << n << endl;

        auto start = chrono::system_clock::now();
        auto d1 = min_distance_naive(points);
        auto finish = chrono::system_clock::now();
        cerr << "min_distance_naive: " << chrono::duration_cast<chrono::milliseconds>(finish - start).count() << "ms" << endl;

        start = chrono::system_clock::now();
        auto d2 = min_distance(points);
        finish = chrono::system_clock::now();
        cerr << "min_distance: " << chrono::duration_cast<chrono::milliseconds>(finish - start).count() << "ms" << endl;

        if (d1 == d2) {
            cerr << "OK: " << d1 << endl;
        } else {
            cerr << "ERROR: " << d1 << " != " << d2 << endl;
        }

        cerr << endl;
    }
}
