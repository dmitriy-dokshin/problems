#include <lib/random/random.h>

#include <type_traits>
#include <unordered_set>

using namespace std;

template <class T>
class TDupsIterator {
public:
    static_assert(is_integral_v<T> && is_unsigned_v<T>);

    TDupsIterator(const vector<T>& v, T min_value, T max_value, size_t max_memory)
        : V_(v)
        , MinValue_(min_value)
    {
        size_t n = (max_value - min_value) + 1;
        if (n / 8 > max_memory) {
            throw runtime_error("Not enough memory");
        }

        Dups_.resize(n);
    }

    bool next(T& result) {
        while (Index_ < V_.size()) {
            const T& value = V_[Index_++];
            if (Dups_[value - MinValue_]) {
                result = value;
                return true;
            } else {
                Dups_[value - MinValue_] = true;
            }
        }
        return false;
    }

private:
    const vector<T>& V_;
    const T MinValue_;
    size_t Index_ = 0;
    vector<bool> Dups_;
};


template <class T>
vector<T> find_dups(const vector<T>& v, T min_value, T max_value, size_t max_memory) {
    vector<T> result;
    TDupsIterator it(v, min_value, max_value, max_memory);
    T x;
    while (it.next(x)) {
        result.emplace_back(x);
    }
    return result;
}

template <class T>
vector<T> find_dups_naive(const vector<T>& v) {
    vector<T> result;
    unordered_set<T> dups;
    for (const auto& x : v) {
        if (!dups.emplace(x).second) {
            result.emplace_back(x);
        }
    }
    return result;
}

template <class T>
bool operator==(const vector<T>& v1, const vector<T>& v2) {
    if (v1.size() != v2.size()) {
        return false;
    }

    for (size_t i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }

    return true;
}

template <class T>
bool operator!=(const vector<T>& v1, const vector<T>& v2) {
    return !(v1 == v2);
}

int main() {
    unsigned int min_value = 1;
    unsigned int max_value = 32000;
    size_t max_memory = 4 * 1024;
    size_t v_size = (max_value - min_value + 1) * 2;
    
    random_device rd;
    auto v = TRandom<unsigned int>::random_vector(v_size, min_value, max_value, rd(), /*debug=*/{true});

    if (find_dups(v, min_value, max_value, max_memory) != find_dups_naive(v)) {
        cerr << "Error" << endl;
    } else {
        cerr << "OK" << endl;
    }
}
