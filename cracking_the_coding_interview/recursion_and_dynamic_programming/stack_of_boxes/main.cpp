#include <algorithm>
#include <random>
#include <vector>

#include <lib/io/io.h>

using namespace std;

template <class T>
vector<vector<T>> random_vectors(size_t n, size_t l, T min_val, T max_val, mt19937_64::result_type seed) {
    vector<mt19937_64> gen;
    gen.reserve(l);
    for (mt19937_64::result_type d = 0; d < l; d++) {
        gen.emplace_back(seed + d);
    }

    uniform_int_distribution<T> dist(min_val, max_val);

    vector<vector<T>> result;
    result.reserve(n);
    for (size_t i = 0; i < n; i++) {
        vector<T> box;
        box.reserve(l);
        for (size_t d = 0; d < l; d++) {
            box.emplace_back(dist(gen.at(d)));
        }
        result.emplace_back(move(box));
    }
    return result;
}

template <class T>
bool operator>(const vector<T>& v1, const vector<T>& v2) {
    if (v1.size() == v2.size()) {
        for (size_t i = 0; i < v1.size(); i++) {
            if (!(v1[i] > v2[i])) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

template <class T>
T stack_of_boxes_impl(const vector<vector<T>>& boxes, vector<T>& cache, const vector<T>* top = nullptr, size_t i = 0) {
    static const size_t HEIGHT_INDEX = 1;
    if (i < boxes.size()) {
        T h = 0;
        if (!top || *top > boxes[i]) {
            if (!cache[i]) {
                cache[i] = stack_of_boxes_impl(boxes, cache, &boxes[i], i + 1) + boxes[i].at(HEIGHT_INDEX);
            }
            h = cache[i];
        }
        h = max(h, stack_of_boxes_impl(boxes, cache, top, i + 1));
        return h;
    } else {
        return 0;
    }
}

template <class T>
T stack_of_boxes(vector<vector<T>> boxes) {
    sort(boxes.begin(), boxes.end(), [](const auto& box1, const auto& box2) { return box1.at(0) > box2.at(0); });
    print(cerr, boxes, "\n") << endl << endl;
    vector<T> cache(boxes.size());
    return stack_of_boxes_impl(boxes, cache);
}

int main() {
    random_device rd;

    auto boxes = random_vectors<unsigned int>(5, 3, 1, 10, rd());

    cerr << stack_of_boxes(boxes) << endl;
}
