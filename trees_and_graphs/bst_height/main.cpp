#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <class T>
class TNode {
public:
    T Value = {};
    TNode* Left = nullptr;
    TNode* Right = nullptr;
};

template <class T>
size_t GetHeight(const TNode<T>* node) {
    size_t left = node->Left ? GetHeight(node->Left) + 1 : 0;
    size_t right = node->Right ? GetHeight(node->Right) + 1 : 0;
    return max(left, right);
}

int main() {
    vector<TNode<int>> v{{0}, {1}, {2}, {3}, {4}, {5}, {6}};
    v[0].Left = &v[1];
    v[0].Right = &v[2];
    v[1].Left = &v[3];
    v[2].Right = &v[6];
    v[3].Left = &v[4];
    v[3].Right = &v[5];

    const bool ok = GetHeight(&v[0]) == 3;
    cerr << (ok ? "OK" : "ERROR") << endl;
}
