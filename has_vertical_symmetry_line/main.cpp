#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class TPoint {
public:
    TPoint() = default;

    TPoint(const int x, const int y)
        : X(x)
        , Y(y)
    {
    }

    int X = 0;
    int Y = 0;
};

ostream& operator<<(ostream& out, const TPoint& p) {
    out << "{" << p.X << ", " << p.Y << "}";
    return out;
}

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (const auto& x : v) {
        out << x << " ";
    }
    return out;
}

bool operator<(const TPoint& p1, const TPoint& p2) {
    if (p1.Y < p2.Y) {
        return true;
    }
    if (p1.Y > p2.Y) {
        return false;
    }
    return p1.X < p2.X;
}

bool operator==(const TPoint& p1, const TPoint& p2) {
    return p1.Y == p2.Y && p1.X == p2.X;
}

bool hasVerticalSymmetryLine(vector<TPoint> points) {
    sort(points.begin(), points.end());

    for (auto& p : points) {
        p.X *= 2;
    }

    int mid = 0;
    for (size_t i = 0; i < points.size() && points[i].Y == points[0].Y; i++) {
        mid = (points[i].X + points[0].X) / 2;
    }

    for (auto& p : points) {
        p.X -= mid;
        if (p.X < 0) {
            p.X = -p.X;
        }
    }

    sort(points.begin(), points.end());

    const TPoint* prev = nullptr;
    bool symmetric = true;
    for (const auto& p : points) {
        if (!symmetric) {
            if (p == *prev) {
                symmetric = true;
            } else {
                break;
            }
        } else if (p.X) {
            symmetric = false;
        }
        prev = &p;
    }

    return symmetric;
}

int main() {
    vector<pair<vector<TPoint>, bool>> tests {
        {{{1, 3}, {6, 3}, {2, 2}, {5, 2}}, true},
        {{{1, 1}}, true},
        {{{1, 1}, {1, 2}}, true},
        {{{1, 1}, {2, 1}}, true},
        {{{1, 1}, {2, 1}, {4, 1}}, false},
        {{{1, 1}, {2, 2}}, false}
    };

    for (auto& x : tests) {
        const bool ok = hasVerticalSymmetryLine(x.first) == x.second;
        cerr << (ok ? "OK" : "ERROR") << "\t" << x.first << endl; 
    }
}
