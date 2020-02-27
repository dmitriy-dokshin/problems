#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <class T>
class TSegment {
public:
    TSegment() = default;

    TSegment(T begin, T end)
        : Begin(begin)
        , End(end)
    {
    }

    T Begin = {};
    T End = {};
};

template <class T>
vector<T> compute_optimal_points(vector<TSegment<T>> segments) {
    sort(segments.begin(), segments.end(), [](const auto& s1, const auto& s2) { return s1.Begin < s2.End; });

    vector<T> result;
    T max_begin = segments[0].Begin;
    T min_end = segments[0].End;
    for (size_t i = 1; i < segments.size(); i++) {
        const auto& x = segments[i];

        if (x.Begin > min_end) {
            result.emplace_back(max_begin);
            min_end = x.End;
        } else if (x.End < min_end) {
            min_end = x.End;
        }

        max_begin = x.Begin;
    }

    result.emplace_back(max_begin);

    return result;
}

int main() {
    vector<pair<vector<TSegment<int>>, size_t>> tests {
        {{{1, 3}, {2, 5}, {3, 6}}, 1},
        {{{4, 7}, {1, 3}, {2, 5}, {5, 6}}, 2},
        {{{0, 2}, {1, 9}, {6, 12}, {4, 8}}, 2}
    };

    for (size_t i = 0; i < tests.size(); i++) {
        auto& test = tests[i];
        const bool ok = compute_optimal_points(test.first).size() == test.second;
        cerr << i << "\t" << (ok ? "OK" : "ERROR") << endl;
    }
}
