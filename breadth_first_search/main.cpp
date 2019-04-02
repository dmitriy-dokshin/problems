#include <iostream>
#include <queue>
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
void BreadthFirstSearch(const TNode<T>* node) {
    queue<const TNode<T>*> q;
    q.push(node);
    while (!q.empty()) {
        if (q.front()->Left) {
            q.emplace(q.front()->Left);
        }
        if (q.front()->Right) {
            q.emplace(q.front()->Right);
        }
        cerr << q.front()->Value << endl;
        q.pop();
    }
}

int main() {
    vector<TNode<int>> v{{0}, {1}, {2}, {3}, {4}, {5}, {6}};
    v[0].Left = &v[1];
    v[0].Right = &v[2];
    v[1].Left = &v[3];
    v[2].Right = &v[6];
    v[3].Left = &v[4];
    v[3].Right = &v[5];

    BreadthFirstSearch(&v[0]);
}
