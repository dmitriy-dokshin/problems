#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
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

template <class T>
void in_order_traversal(const TNode<T>& node, function<void(const T& value)> visit) {
    if (node.Left) {
        in_order_traversal(*node.Left, visit);
    }
    visit(node.Value);
    if (node.Right) {
        in_order_traversal(*node.Right, visit);
    }
}

class TBreakException: public exception {
};

bool check_subtree(const TNode<size_t>& t1, const TNode<size_t>& t2) {
    vector<size_t> v2;
    in_order_traversal<size_t>(t2, [&v2](const size_t& value) { v2.emplace_back(value); });

    for (const auto& x : v2) {
        cerr << " " << x;
    }
    cerr << endl;

    size_t i = 0;
    try {
        in_order_traversal<size_t>(t1,
            [&v2, &i] (const size_t& value) {
                if (i < v2.size()) {
                    cerr << " " << value;
                    if (v2[i] == value) {
                        i++;
                    } else {
                        i = 0;
                    }
                } else {
                    throw TBreakException();
                }
            });
    } catch (const TBreakException&) {
    }

    cerr << endl;

    return i == v2.size();
}

int main() {
    vector<pair<size_t, size_t>> v1;
    v1.resize(10);
    v1[0] = {1, 2};
    v1[1] = {3, 4};
    v1[2] = {8, 9};
    v1[4] = {5, 6};
    v1[6] = {7, 0};
    auto t1 = build_tree(v1);

    vector<pair<size_t, size_t>> v2;
    v2.resize(4);
    v2[0] = {1, 2};
    v2[2] = {3, 0};
    auto t2 = build_tree(v2);
    t2[0]->Value = 4;
    t2[1]->Value = 5;
    t2[2]->Value = 6;
    t2[3]->Value = 7;

    cerr << check_subtree(*t1[0], *t2[0]) << endl;

    vector<pair<size_t, size_t>> v3;
    v3.resize(2);
    v3[0] = {1, 0};
    auto t3 = build_tree(v3);
    t3[0]->Value = 2;
    t3[1]->Value = 8;

    cerr << check_subtree(*t1[0], *t3[0]) << endl;
}
