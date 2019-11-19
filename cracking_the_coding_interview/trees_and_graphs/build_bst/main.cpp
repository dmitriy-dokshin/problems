#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <utility>
#include <vector>

template <class T>
class TNode {
public:
    T Value;
    std::unique_ptr<TNode> Left;
    std::unique_ptr<TNode> Right;
};

template <class T>
std::unique_ptr<TNode<T>> build_bst(const std::vector<T>& v, size_t begin, size_t end) {
    if (end - begin == 0) {
        return nullptr;
    }

    size_t mid = (begin + end) / 2;
    auto node = std::make_unique<TNode<T>>();
    node->Value = v[mid];
    node->Left = build_bst(v, begin, mid);
    node->Right = build_bst(v, mid + 1, end);
    return node;
}

template <class T>
bool exists(const TNode<T>& node, const T& val) {
    if (val < node.Value) {
        if (node.Left) {
            return exists(*node.Left, val);
        }
    } else if (val > node.Value) {
        if (node.Right) {
            return exists(*node.Right, val);
        }
    } else {
        return true;
    }
    return false;
}

template <class T>
size_t lower_bound(const std::vector<T>& v, const T& val) {
    size_t begin = 0;
    size_t end = v.size();
    while (begin < end) {
        size_t mid = (begin + end) / 2;
        // Eventually begin points to the element that is >= than val
        if (v[mid] < val) {
            begin = mid + 1;
        } else {
            end = mid;
        }
    }
    return begin;
}

template <class T>
size_t upper_bound(const std::vector<T>& v, const T& val) {
    size_t begin = 0;
    size_t end = v.size();
    while (begin < end) {
        size_t mid = (begin + end) / 2;
        // Eventually begin points to the element that is > than val
        if (v[mid] <= val) {
            begin = mid + 1;
        } else {
            end = mid;
        }
    }
    return begin;
}

template <class T>
std::pair<size_t, size_t> equal_range(const std::vector<T>& v, const T& val) {
    return {lower_bound(v, val), upper_bound(v, val)};
}

template <class T>
bool exists(const std::vector<T>& v, const T& val) {
    auto r = equal_range(v, val);
    return r.second - r.first > 0;
}

template <class T>
std::vector<T> prepare_input(size_t n, T min, T max) {
    std::random_device device;
    std::default_random_engine engine(device());
    std::uniform_int_distribution<T> rand(min, max);
    std::vector<T> v;
    v.reserve(n);
    for (size_t i = 0; i < n; i++) {
        v.emplace_back(rand(engine));
    }
    std::sort(v.begin(), v.end());
    return v;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << " " << v[i];
        }
    }
    return out;
}

template <class T>
void run(size_t n, T min, T max) {
    auto v = prepare_input<T>(n, min, max);
    auto bst = build_bst(v, 0, n);
    std::cerr << v << std::endl;
    for (T val = min; val <= max; val++) {
        std::cerr << val << "\t" << exists(v, val) << "\t" << exists(*bst, val) << std::endl; 
    }
}

int main() {
    run<short>(5, 0, 9);
}
