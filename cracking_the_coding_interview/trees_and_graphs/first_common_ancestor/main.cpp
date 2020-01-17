#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

template <class T>
class TNode {
public:
    shared_ptr<TNode> Left;
    shared_ptr<TNode> Right;
    T Value = {};
};

template <class T>
class TResult {
public:
    bool P = false;
    bool Q = false;
    const TNode<T>* Node = nullptr;
};

template <class T>
TResult<T> find(const TNode<T>* node, const TNode<T>* p, const TNode<T>* q) {
    if (node == nullptr) {
        return {};
    }

    if (p == q) {
        TResult<T> result;
        result.Node = p;
        return result;
    }

    TResult<T> left;
    if (node->Left) {
        left = find(node->Left.get(), p, q);
    }

    if (left.Node) {
        return left;
    }

    if (left.P && node == q || left.Q && node == p) {
        left.Node = node;
        return left;
    }

    TResult<T> right;
    if (node->Right) {
        right = find(node->Right.get(), p, q);
    }

    if (right.Node) {
        return right;
    }

    if (right.P && node == q || right.Q && node == p) {
        right.Node = node;
        return right;
    }

    if (left.P && right.Q || left.Q && right.P) {
        TResult<T> result;
        result.Node = node;
        return result;
    }

    if (left.P || left.Q) {
        return left;
    }

    if (right.P || right.Q) {
        return right;
    }

    TResult<T> result;
    result.P = node == p;
    result.Q = node == q;
    return result;
}


template <class T>
const TNode<T>* first_common_ancestor(const TNode<T>* root, const TNode<T>* p, const TNode<T>* q) {
    auto result = find(root, p, q);
    return result.Node;
}

vector<shared_ptr<TNode<size_t>>> build_tree(const vector<pair<size_t, size_t>>& v) {
    vector<shared_ptr<TNode<size_t>>> nodes;
    nodes.reserve(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        nodes.emplace_back(make_shared<TNode<size_t>>());
    }

    for (size_t i = 0; i < v.size(); i++) {
        if (v[i].first) {
            nodes[i]->Left = nodes[v[i].first];
        }
        if (v[i].second) {
            nodes[i]->Right = nodes[v[i].second];
        }
        nodes[i]->Value = i;
    }

    return nodes;
}

int main() {
    vector<pair<size_t, size_t>> v;
    v.resize(9);
    v[0] = {1, 2};
    v[1] = {3, 4};
    v[2] = {5, 6};
    v[6] = {7, 8};

    auto nodes = build_tree(v);

    auto fca = first_common_ancestor(nodes[0].get(), nodes[5].get(), nodes[8].get());

    cerr << fca->Value << endl;
}
