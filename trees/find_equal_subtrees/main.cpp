#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class TNode {
public:
    size_t Index = 0;
    TNode* Left = nullptr;
    TNode* Right = nullptr;
    char Value = 0;
};

ostream& operator<<(ostream& out, const TNode* node) {
    out << node->Index;
    return out;
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

int FindEqualSubtrees(const TNode* node, unordered_map<int, vector<const TNode*>>& map) {
    int set = 0;
    if (node->Left || node->Right) {
        if (node->Left) {
            set |= FindEqualSubtrees(node->Left, map);
        }
        if (node->Right) {
            set |= FindEqualSubtrees(node->Right, map);
        }
        map[set].emplace_back(node);
    }
    set |= 1 << (node->Value - 'A');
    return set;
}

pair<const TNode*, const TNode*> FindEqualSubtrees(const TNode* node) {
    unordered_map<int, vector<const TNode*>> map;
    FindEqualSubtrees(node, map);
    for (const auto& x : map) {
        if (x.second.size() > 1) {
            return {x.second[0], x.second[1]};
        }
    }
    return {nullptr, nullptr};
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

        cin >> node.Value;
        cin.ignore();
    }
    return tree;
}

int main() {
    auto tree = ReadTree();
    auto result = FindEqualSubtrees(&tree[0]);
    if (result.first && result.second) {
        cout << result.first->Index << " " << result.second->Index << endl;
    } else {
        cout << "-1" << endl;
    }
}
