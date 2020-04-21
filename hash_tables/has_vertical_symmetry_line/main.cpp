#include <bitset>
#include <functional>
#include <iostream>
#include <unordered_set>
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

template <>
struct hash<TPoint> {
    size_t operator()(const TPoint& p) const {
        return hash<int>()(p.X) ^ hash<int>()(p.Y);
    }
};

bool operator==(const TPoint& p1, const TPoint& p2) {
    return p1.X == p2.X && p1.Y == p2.Y;
}

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

int midpoint(const vector<TPoint>& points) {
    const int* min = nullptr;
    const int* max = nullptr;
    for (const auto& p : points) {
        if (!min) {
            min = &p.X;
            max = &p.X;
        } else {
            if (p.X < *min) {
                min = &p.X;
            }
            if (p.X > *max) {
                max = &p.X;
            }
        }
    }
    return *min + *max;
}

TPoint reflect(const TPoint& p, const int mid) {
    return {mid - p.X, p.Y};
}

bool hasVerticalSymmetryLine(const vector<TPoint>& points) {
    if (points.empty()) {
        return true;
    }

    const int mid = midpoint(points);
    const unordered_set<TPoint> pointsSet{points.begin(), points.end()};
    for (const auto& p : points) {
        const TPoint refl = reflect(p, mid);
        if (pointsSet.find(refl) == pointsSet.end()) {
            return false;
        }
    }

    return true;
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
