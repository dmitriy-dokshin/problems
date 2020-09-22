#include <lib/io/io.h>
#include <lib/random/random.h>
#include <lib/tree/tree.h>

using namespace std;

template <class T>
using TAVLNode = TNode<T, size_t>;

template <class TNode>
class TTree {
public:
    TNode* Root = nullptr;
    vector<TNode> Nodes;
};

template <class T>
size_t left_height(const TAVLNode<T>* node) {
    return node->Left ? node->Left->Value + 1 : 0;
}

template <class T>
size_t right_height(const TAVLNode<T>* node) {
    return node->Right ? node->Right->Value + 1 : 0;
}

template <class T>
TNode<T>* insert(TNode<T>* node, TNode<T>* x) {
    if (x->Key < node->Key) {
        if (node->Left) {
            insert(node->Left, x);
        } else {
            node->Left = x;
        }
    } else {
        if (node->Right) {
            insert(node->Right, x);
        } else {
            node->Right = x;
        }
    }
    return node;
}

template <class TNode>
TNode* rotate_right(TNode* node) {
    auto tmp = node->Left;
    node->Left = tmp->Right;
    tmp->Right = node;
    return tmp;
}

template <class TNode>
TNode* rotate_left(TNode* node) {
    auto tmp = node->Right;
    node->Right = tmp->Left;
    tmp->Left = node;
    return tmp;
}

template <class T>
TAVLNode<T>* insert(TAVLNode<T>* node, TAVLNode<T>* x) {
    if (x->Key < node->Key) {
        if (node->Left) {
            node->Left = insert(node->Left, x);
        } else {
            node->Left = x;
        }
    } else {
        if (node->Right) {
            node->Right = insert(node->Right, x);
        } else {
            node->Right = x;
        }
    }

    size_t lh = left_height(node);
    size_t rh = right_height(node);
    if (rh > lh && rh - lh > 1) {
        if (left_height(node->Right) > right_height(node->Right)) {
            node->Right = rotate_right(node->Right);
        }
        node = rotate_left(node);
    } else if (lh > rh && lh - rh > 1) {
        if (right_height(node->Left) > left_height(node->Left)) {
            node->Left = rotate_left(node->Left);
        }
        node = rotate_right(node);
    }
    node->Value = max(left_height(node), right_height(node));
    return node;
}

template <class TNode>
TTree<TNode> build_tree(const vector<typename TNode::key_type>& v) {
    TTree<TNode> tree;
    tree.Nodes.reserve(v.size());
    for (const auto& x : v) {
        tree.Nodes.emplace_back(x);
        if (tree.Root) {
            tree.Root = insert(tree.Root, &tree.Nodes.back());
        } else {
            tree.Root = &tree.Nodes.back();
        }
    }
    return tree;
}

class TDebugInfo {
public:
    size_t Steps = 0;
};

template <class TNode>
const TNode* find(const TNode* node, const typename TNode::key_type& x, TDebugInfo* debug) {
    if (debug) {
        debug->Steps++;
    }
    if (node->Key == x) {
        return node;
    } else if (x < node->Key) {
        return node->Left ? find(node->Left, x, debug) : nullptr;
    } else {
        return node->Right ? find(node->Right, x, debug) : nullptr;
    }
}

template <class TNode>
size_t height(const TNode* node) {
    size_t lh = node->Left ? height(node->Left) + 1 : 0;
    size_t rh = node->Right ? height(node->Right) + 1 : 0;
    return max(lh, rh);
}

int main() {
    random_device rd;

    auto v = TRandom<int>::random_vector(1024, 0, 99, rd());

    // cerr << v << endl;

    // auto tree = build_tree<TNode<int>>(v);
    auto tree = build_tree<TAVLNode<int>>(v);

    cerr << "height: " << height(tree.Root) << endl;

    while (true) {
        int value;
        cin >> value;
        TDebugInfo debug;
        auto node = find(tree.Root, value, &debug);
        if (node) {
            cout << node->Key << "\t" << debug.Steps << endl;
        } else {
            cout << "Not found" << "\t" << debug.Steps << endl;
        }
    }
}
