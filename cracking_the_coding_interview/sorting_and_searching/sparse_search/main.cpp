#include <lib/algorithm/searching/binary_search.h>
#include <lib/random/random.h>

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <utility>

using namespace std;

ostream& operator<<(ostream& out, const optional<string>& s) {
    out << '"' << (s ? *s : "") << '"';
    return out;
}

vector<optional<string>> random_strings(size_t size, size_t min_len, size_t max_len, char min_val, char max_val, float empty_prob) {
    random_device rd;
    auto sizes = TRandom<size_t>::random_vector(size, min_len, max_len, rd()); 

    vector<optional<string>> result;
    result.reserve(size);
    for (size_t i = 0; i < sizes.size(); i++) {
        auto s = TRandom<char>::random_vector(sizes[i], min_val, max_val, rd());
        result.emplace_back(make_optional<string>(s.begin(), s.end()));
    }

    sort(result.begin(), result.end());

    auto empty_probs = TRandom<float>::random_vector(size, 0.0f, 1.0f, rd());
    for (size_t i = 0; i < empty_probs.size(); i++) {
        if (empty_probs[i] < empty_prob) {
            result[i].reset();
        }
    }

    return result;
}

template <class TComp, class T>
size_t sparse_find_bound(const vector<optional<T>>& v, const T& value, size_t begin, size_t end, TComp comp = {}) {
    if (begin < end) {
        size_t mid = begin + (end - begin) / 2;
        if (!v[mid].has_value()) {
            if (size_t result = sparse_find_bound(v, value, begin, mid, comp); result < mid) {
                return result;
            } else {
                return sparse_find_bound(v, value, mid + 1, end, comp);
            }
        } else if (comp(*v[mid], value)) {
            return sparse_find_bound(v, value, mid + 1, end, comp);
        } else {
            return sparse_find_bound(v, value, begin, mid, comp);
        }
    } else {
        return begin;
    }
}

template <class T>
size_t sparse_lower_bound(const vector<optional<T>>& v, const T& value) {
    return sparse_find_bound<less<T>>(v, value, 0, v.size());
}

template <class T>
size_t sparse_upper_bound(const vector<optional<T>>& v, const T& value) {
    return sparse_find_bound<less_equal<T>>(v, value, 0, v.size());
}

template <class T>
class TLessOptional {
public:
    bool operator()(const optional<T>& x, const optional<T>& y) const {
        if (x && y) {
            return *x < *y;
        } else if (x) {
            return true;
        } else {
            return false;
        }
    }
};

template <class T>
pair<size_t, size_t> sparse_search(const vector<optional<T>>& v, const T& value) {
    size_t begin = sparse_lower_bound(v, value);
    size_t end = sparse_upper_bound(v, value);
    end = find_bound<TLessOptional<T>>(v, nullopt, begin, end);
    return {begin, end};
}

int main() {
    auto v = random_strings(32, 2, 5, 'a', 'z', 0.4);
    for (size_t i = 0; i < v.size(); i++) {
        cerr << i << "\t" <<  v[i] << endl;
    }

    string value;
    cin >> value;
    auto result = sparse_search(v, value);
    cerr << result.first << "\t" << result.second << endl;
}
