#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class TNode {
public:
    size_t Index = 0;
    TNode* Left = nullptr;
    TNode* Right = nullptr;
};

void Traverse(TNode& node, size_t k, vector<size_t>& result, size_t h = 1) {
    if (h % k == 0) {
        swap(node.Left, node.Right);
    }
    if (node.Left) {
        Traverse(*node.Left, k, result, h + 1);
    }
    result.emplace_back(node.Index);
    if (node.Right) {
        Traverse(*node.Right, k, result, h + 1);
    }
}

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << " " << v[i];
        }
    }
    return out;
}

template <class T>
vector<T> ReadVector(size_t n) {
    vector<T> arr;
    arr.reserve(n);
    for (size_t i = 0; i < n; i++) {
        T val;
        cin >> val;
        arr.emplace_back(move(val));
    }
    cin.ignore();
    return arr;
}

vector<TNode> ReadTree() {
    size_t n;
    cin >> n;
    cin.ignore();

    vector<TNode> tree(n);
    for (size_t i = 0; i < n; i++) {
        auto v = ReadVector<long>(2);
        auto& node = tree[i];
        node.Index = i + 1;
        if (v[0] > 0) {
            node.Left = &tree.at(v[0] - 1);
        }
        if (v[1] > 0) {
            node.Right = &tree.at(v[1] - 1);
        }
    }
    return tree;
}

int main() {
    ofstream out(getenv("OUTPUT_PATH"));

    vector<TNode> tree = ReadTree();

    size_t t;
    cin >> t;
    cin.ignore();

    vector<size_t> result;
    result.reserve(tree.size());

    for (size_t i = 0; i < t; i++) {
        size_t k;
        cin >> k;
        cin.ignore();

        Traverse(tree[0], k, result);
        out << result << endl;

        result.clear();
    }
}
