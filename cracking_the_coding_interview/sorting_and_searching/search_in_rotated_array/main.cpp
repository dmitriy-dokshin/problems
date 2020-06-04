#include <lib/io/io.h>
#include <lib/random/random.h>

#include <algorithm>

using namespace std;

template <class T>
void rotate_array(vector<T>& v) {
    if (v.size() > 0) {
        auto x = move(v[v.size() - 1]);
        for (size_t i = v.size(); i > 1; i--) {
            v[i - 1] = move(v[i - 2]);
        }
        v[0] = move(x);
    }
}

template <class T>
void rotate_array(vector<T>& v, size_t n) {
    for (size_t i = 0; i < n; i++) {
        rotate_array(v);
    }
}

class TIndexer {
public:
    TIndexer() = default;

    template <class T>
    TIndexer(const vector<T>& v)
        : Size_(v.size())
    {
        for (size_t i = 1; i < v.size(); i++) {
            if (v[i] < v[i - 1]) {
                N_ = i;
                break;
            }
        }
    }

    size_t operator()(size_t i) const {
        return (i + N_) % Size_;
    }

private:
    size_t Size_ = 0;
    size_t N_ = 0;
};

template <class T, class TComp>
size_t find_bound(const std::vector<T>& v, const T& value, size_t begin, size_t end, const TIndexer& indexer, TComp comp = {}) {
    if (begin < end) {
        size_t mid = begin + (end - begin) / 2;
        if (comp(v[indexer(mid)], value)) {
            return find_bound(v, value, mid + 1, end, indexer, comp);
        } else {
            return find_bound(v, value, begin, mid, indexer, comp);
        }
    } else {
        return indexer(begin);
    }
}

template <class T>
size_t lower_bound(const std::vector<T>& v, const T& value, const TIndexer& indexer) {
    return find_bound<T, std::less<T>>(v, value, 0, v.size(), indexer);
}

template <class T>
size_t upper_bound(const std::vector<T>& v, const T& value, const TIndexer& indexer) {
    return find_bound<T, std::less_equal<T>>(v, value, 0, v.size(), indexer);
}

template <class T>
std::pair<size_t, size_t> binary_search(const std::vector<T>& v, const T& value) {
    TIndexer indexer(v);
    return {lower_bound(v, value, indexer), upper_bound(v, value, indexer)};
}

int main() {
    random_device rd;
    auto v = TRandom<int>::random_vector(16, 1, 20, rd());
    sort(v.begin(), v.end());

    size_t n = rd() % v.size();
    rotate_array(v, n);
    for (size_t i = 0; i < v.size(); i++) {
        size_t index = i < n ? i + v.size() - n : i - n;
        cerr << i << "\t" << index << "\t" << v[i] << endl;
    }

    int value;
    cin >> value;
    auto result = binary_search(v, value);
    cerr << result.first << "\t" << result.second << endl;
}
