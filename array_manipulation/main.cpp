#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <utility>

using namespace std;

template <class T>
class TSegment {
    static_assert(is_arithmetic<T>::value, "Type has to be arithmetic");
public:
    TSegment() = default;

    TSegment(const size_t begin, const size_t end, const T value)
        : Begin(begin)
        , End(end)
        , Value(value)
    {
    }

    template <class TValue>
    TSegment(const vector<TValue>& v)
        : Begin(v[0])
        , End(v[1])
        , Value(v[2])
    {
    }

    size_t Begin = 0;
    size_t End = 0;
    T Value = {};
};

template <class T>
ostream& operator<<(ostream& out, const TSegment<T>& segment) {
    out << "{" << segment.Begin << ", " << segment.End << ", " << segment.Value << "}";
    return out;
}

template <class T>
size_t LowerBound(const vector<TSegment<T>>& segments, const TSegment<T>& query) {
    size_t begin = 0;
    size_t end = segments.size();
    while (end - begin > 0) {
        size_t mid = (begin + end) / 2;
        if (segments[mid].End < query.Begin) {
            begin = mid + 1;
        } else {
            end = mid;
        }
    }
    return begin;
}

template <class T>
bool NotIntersected(const TSegment<T>& s1, const TSegment<T>& s2) {
    return s1.Begin > s2.End || s1.End < s2.Begin;
}

template <class T>
bool Intersected(const TSegment<T>& s1, const TSegment<T>& s2) {
    return !NotIntersected(s1, s2);
}

template <class T>
vector<TSegment<T>> Intersect(const TSegment<T>& s1, const TSegment<T>& s2) {
    if (NotIntersected(s1, s2)) {
        throw runtime_error("The segments do not intersect");
    }

    if (s1.Begin < s2.Begin) {
        if (s1.End < s2.End) {
            return {
                {s1.Begin, s2.Begin - 1, s1.Value},
                {s2.Begin, s1.End, s1.Value + s2.Value},
                {s1.End + 1, s2.End, s2.Value}
            };
        } else if (s1.End == s2.End) {
            return {
                {s1.Begin, s2.Begin - 1, s1.Value},
                {s2.Begin, s1.End, s1.Value + s2.Value}
            };
        } else {
            return {
                {s1.Begin, s2.Begin - 1, s1.Value},
                {s2.Begin, s2.End, s1.Value + s2.Value},
                {s2.End + 1, s1.End, s1.Value}
            };
        }
    } else if (s1.Begin == s2.Begin) {
        if (s1.End < s2.End) {
            return {
                {s1.Begin, s1.End, s1.Value + s2.Value},
                {s1.End + 1, s2.End, s2.Value}
            };
        } else if (s1.End == s2.End) {
            return {
                {s1.Begin, s1.End, s1.Value + s2.Value}
            };
        } else {
            return {
                {s1.Begin, s2.End, s1.Value + s2.Value},
                {s2.End + 1, s1.End, s1.Value}
            };
        }
    } else {
        if (s1.End < s2.End) {
            return {
                {s2.Begin, s1.Begin - 1, s2.Value},
                {s1.Begin, s1.End, s1.Value + s2.Value},
                {s1.End + 1, s2.End, s2.Value}
            };
        } else if (s1.End == s2.End) {
            return {
                {s2.Begin, s1.Begin - 1, s2.Value},
                {s1.Begin, s1.End, s1.Value + s2.Value}
            };
        } else {
            return {
                {s2.Begin, s1.Begin - 1, s2.Value},
                {s1.Begin, s2.End, s1.Value + s2.Value},
                {s2.End + 1, s1.End, s1.Value}
            };
        }
    }
}

template <class T>
vector<TSegment<T>> Intersect(const vector<TSegment<T>>& segments, const size_t begin, const size_t end, TSegment<T> query) {
    vector<TSegment<T>> result;
    for (size_t i = begin; i != end; i++) {
        const auto& segment = segments[i];
        auto intersection = Intersect(segment, query);
        result.insert(result.end(), make_move_iterator(intersection.begin()), make_move_iterator(intersection.end() - 1));
        query = move(intersection.back());
    }
    result.emplace_back(move(query));
    return result;
}

template <class T>
vector<TSegment<T>> Intersect(const vector<TSegment<T>>& queries) {
    vector<TSegment<T>> segments;
    for (const auto& query : queries) {
        size_t begin = LowerBound(segments, query);
        size_t end = begin;
        while (end < segments.size() && Intersected(segments[end], query)) {
            end++;
        }
        if (begin < end) {
            auto intersection = Intersect(segments, begin, end, query);
            segments.erase(segments.begin() + begin, segments.begin() + end);
            segments.insert(segments.begin() + begin, make_move_iterator(intersection.begin()), make_move_iterator(intersection.end()));
        } else {
            segments.emplace(segments.begin() + begin, query);
        }
    }
    return segments;
};

template <class T>
T CalculateMaxSum(const vector<TSegment<T>>& queries) {
    auto intersection = Intersect(queries);
    T max = numeric_limits<T>::min();
    for (const auto& x : intersection) {
        if (x.Value > max) {
            max = x.Value;
        }
    }
    return max;
}

template <class T>
T CalculateMaxSumOptimal(const vector<TSegment<T>>& queries) {
    vector<pair<size_t, T>> v;
    for (const auto& q : queries) {
        v.emplace_back(q.Begin, q.Value);
        v.emplace_back(q.End + 1, -q.Value);
    }
    sort(v.begin(), v.end(), [](const auto& x1, const auto& x2) { return x1.first < x2.first; });
    T max = numeric_limits<T>::min();
    T sum = 0;
    for (const auto& x : v) {
        sum += x.second;
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}

int main() {
    vector<vector<int>> queries {
        {2, 6, 8},
        {3, 5, 7},
        {1, 8, 1},
        {5, 9, 15}
    };
    cerr << CalculateMaxSum<long>({queries.begin(), queries.end()}) << endl;
    cerr << CalculateMaxSumOptimal<long>({queries.begin(), queries.end()}) << endl;
}
