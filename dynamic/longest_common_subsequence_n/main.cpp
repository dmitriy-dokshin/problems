#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

string random_string(size_t size, typename mt19937::result_type seed) {
    mt19937_64 gen(seed);
    uniform_int_distribution<char> dist('a', 'c');
    string s;
    s.reserve(size);
    while (s.size() < size) {
        s += dist(gen);
    }
    return s;
}

vector<string> random_strings(size_t n, size_t min_size, size_t max_size, typename mt19937::result_type seed) {
    mt19937_64 seed_gen(seed);
    uniform_int_distribution<unsigned long> seed_dist;

    mt19937_64 size_gen(seed_dist(seed_gen));
    uniform_int_distribution<size_t> size_dist(min_size, max_size);

    vector<string> sequences;
    sequences.reserve(n);
    while (sequences.size() < n) {
        sequences.emplace_back(random_string(size_dist(size_gen), seed_dist(seed_gen)));
    }

    return sequences;
}

template <class T>
class TMultiDimensionalArray {
public:
    TMultiDimensionalArray(const vector<size_t>& sizes) {
        size_t array_size = 1;
        Sizes_.reserve(sizes.size());
        for (size_t i = sizes.size(); i > 0; i--) {
            Sizes_.emplace_back(array_size);
            array_size *= sizes[i - 1];
        }
        reverse(Sizes_.begin(), Sizes_.end());
        Array_.resize(array_size);
    }

    T& operator[](const vector<size_t>& index) {
        size_t array_index = 0;
        for (size_t i = 0; i < index.size(); i++) {
            array_index += index[i] * Sizes_[i];
        }
        return Array_[array_index];
    }

private:
    vector<size_t> Sizes_;
    vector<T> Array_;
};

template <class F>
void iterate(const vector<size_t>& sizes, vector<size_t>& index, F f, size_t d = 0) {
    for (size_t i = 0; i < sizes[d]; i++) {
        index[d] = i;
        if (d < index.size() - 1) {
            iterate(sizes, index, f, d + 1);
        } else {
            f(index);
        }
    }
}

template <class T>
bool equal_at(const vector<T>& sequences, const vector<size_t>& index) {
    for (size_t i = 1; i < sequences.size(); i++) {
        if (sequences[i][index[i]] != sequences[i - 1][index[i - 1]]) {
            return false;
        }
    }
    return true;
}

template <class T>
size_t lcs_n(const vector<T>& sequences) {
    vector<size_t> sizes;
    sizes.reserve(sequences.size());
    for (const auto& s : sequences) {
        if (s.size() > 0) {
            sizes.emplace_back(s.size());
        } else {
            return 0;
        }
    }

    TMultiDimensionalArray<size_t> res(sizes);
    vector<size_t> index;
    index.resize(sequences.size());
    iterate(
        sizes, index,
        [&res, &sequences](vector<size_t>& index) {
            if (equal_at(sequences, index)) {
                size_t i = 0;
                for (; i < index.size() && index[i] > 0; i++) {
                    index[i]--;
                }
                size_t x = i < index.size() ? 0 : res[index];
                for (; i > 0; i--) {
                    index[i - 1]++;
                }
                res[index] = x + 1;
            } else {
                for (size_t i = 0; i < index.size(); i++) {
                    if (index[i] > 0) {
                        index[i]--;
                        size_t x = res[index];
                        index[i]++;
                        res[index] = max(res[index], x);
                    }
                }
            }
        });

    for (size_t& size : sizes) {
        size--;
    }

    return res[sizes];
}

int main(int argc, const char* argv[]) {
    const size_t n = 3;
    const size_t min_size = 5;
    const size_t max_size = 10;

    random_device rd;
    typename mt19937::result_type seed = argc > 1 ? stoul(argv[1]) : rd();

    vector<string> sequences = random_strings(n, min_size, max_size, seed);

    for (const auto& s : sequences) {
        cerr << s << endl;
    }

    cout << lcs_n(sequences) << endl;
}
