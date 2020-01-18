#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template <class T>
class TNode {
public:
    std::unique_ptr<TNode> Left;
    std::unique_ptr<TNode> Right;
    T Value = {};
};

template <class T>
void set_or_insert(unique_ptr<TNode<T>>& node, const T& value) {
    if (node) {
        insert(*node, value);
    } else {
        node = make_unique<TNode<T>>();
        node->Value = value;
    }
}

template <class T>
void insert(TNode<T>& node, const T& value) {
    if (value < node.Value) {
        set_or_insert(node.Left, value);
    } else {
        set_or_insert(node.Right, value);
    }
}

template <class T>
unique_ptr<TNode<T>> build_bst(const vector<T>& v) {
    unique_ptr<TNode<T>> head;
    for (const auto& value : v) {
        set_or_insert(head, value);
    }

    return head;
}

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "{";
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << ", " << v[i];
        }
    }
    out << "}";
    return out;
}

template <class T>
vector<vector<T>> get_all_sequences(const TNode<T>& node) {
    vector<T> v0 {node.Value};

    vector<vector<T>> left;
    if (node.Left) {
        left = get_all_sequences(*node.Left);
    }

    vector<vector<T>> right;
    if (node.Right) {
        right = get_all_sequences(*node.Right);
    }

    vector<vector<T>> result;
    for (const auto& l : left) {
        vector<T> v1 = v0;
        v1.insert(v1.end(), l.begin(), l.end());
        for (const auto& r : right) {
            vector<T> v2 = v1;
            v2.insert(v2.end(), r.begin(), r.end());
            result.emplace_back(std::move(v2));
        }
    }

    for (const auto& r : right) {
        vector<T> v1 = v0;
        v1.insert(v1.end(), r.begin(), r.end());
        for (const auto& l : left) {
            vector<T> v2 = v1;
            v2.insert(v2.end(), l.begin(), l.end());
            result.emplace_back(std::move(v2));
        }
    }

    if (result.empty()) {
        result.emplace_back(std::move(v0));
    }

    return result;
}

int main() {
    vector<int> v {4, 5, 2, 1, 3};

    cout << v << endl;

    auto bst = build_bst(v);

    auto result = get_all_sequences(*bst);

    for (const auto& x : result) {
        cout << x << endl;
    }
}
