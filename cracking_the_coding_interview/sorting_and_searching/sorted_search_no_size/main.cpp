#include <lib/algorithm/searching/binary_search.h>
#include <lib/random/random.h>

#include <algorithm>
#include <iostream>
#include <optional>

using namespace std;

template <class T>
class TListy {
public:
    TListy(vector<T> data)
        : Data_(move(data))
    {
    }

    optional<T> operator[](size_t i) const {
        return i < Data_.size() ? make_optional(Data_.at(i)) : nullopt; 
    }

private:
    vector<T> Data_;
};

template <class T, class TComp = less<T>>
class TLessOptional {
public:
    using value_type = T;

    TLessOptional(TComp comp = {})
        : Comp_(move(comp))
    {
    }

    bool operator()(const optional<T>& x, const optional<T>& y) const {
        if (x && y) {
            return Comp_(*x, *y);
        } else if (x) {
            return true;
        } else {
            return false;
        }
    }

private:
    TComp Comp_;
};

template <class T>
size_t get_size(const TListy<T>& listy) {
    size_t size = 1;
    while (listy[size]) {
        size *= 2;
    }

    size = find_bound<TLessOptional<T>>(listy, nullopt, 0, size);
    return size;
}

template <class T>
pair<size_t, size_t> binary_search(const TListy<T>& listy, const optional<T>& value) {
    size_t size = get_size(listy);
    return {
        find_bound<TLessOptional<T>>(listy, value, 0, size),
        find_bound<TLessOptional<T, less_equal<T>>>(listy, value, 0, size)
    };
}

int main() {
    random_device rd;
    auto v = TRandom<int>::random_vector(10, 1, 5, rd());
    sort(v.begin(), v.end());
    for (size_t i = 0; i < v.size(); i++) {
        cerr << i << "\t" << v[i] << endl;
    }

    int value;
    cin >> value;
    TListy<int> listy(move(v));
    auto result = binary_search(listy, make_optional(value));
    cerr << result.first << "\t" << result.second << endl;
}
