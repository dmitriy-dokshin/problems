#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <class T>
class TNode {
public:
    TNode() = default;

    template <class T_>
    TNode(T_&& value, size_t index)
        : Value(forward<T_>(value))
        , Index(index)
    {
    }

    shared_ptr<TNode> Parent;
    shared_ptr<TNode> Left;
    shared_ptr<TNode> Right;
    T Value = {};
    size_t Index = 0;
};

template <class T>
class TTree {
public:
    template <class T_>
    void insert(T_&& value) {
        auto new_node = make_shared<TNode<T>>(forward<T_>(value), Nodes_.size());
        Nodes_.emplace_back(new_node);
        insert(Root_, move(new_node));
    }

    shared_ptr<TNode<T>> find(const T& value) {
        shared_ptr<TNode<T>> node = Root_;
        while (node) {
            if (node->Value == value) {
                break;
            } else if (value < node->Value) {
                node = node->Left;
            } else {
                node = node->Right;
            }
        }

        return node;
    }

    void erase(shared_ptr<TNode<T>>& node) {
        if (node->Parent) {
            if (node->Parent->Left == node) {
                node->Parent->Left = move(node->Left);
                insert(node->Parent->Left, move(node->Right));
            } else {
                node->Parent->Right = move(node->Left);
                insert(node->Parent->Right, move(node->Right));
            }
        } else {
            Root_ = move(node->Left);
            insert(Root_, move(node->Right));
        }

        if (node->Index != Nodes_.size() - 1) {
            Nodes_.at(node->Index) = move(Nodes_.at(Nodes_.size() - 1));
        }
        Nodes_.resize(Nodes_.size() - 1);
    }

    shared_ptr<TNode<T>> random(function<size_t()> g) {
        if (!Nodes_.empty()) {
            return Nodes_.at(g() % Nodes_.size());
        } else {
            return {};
        }
    }


private:
    static void insert(shared_ptr<TNode<T>>& root, shared_ptr<TNode<T>> new_node) {
        if (root) {
            auto node = root;
            while (true) {
                if (new_node->Value < node->Value) {
                    if (node->Left) {
                        node = node->Left;
                    } else {
                        new_node->Parent = node;
                        node->Left = move(new_node);
                        break;
                    }
                } else {
                    if (node->Right) {
                        node = node->Right;
                    } else {
                        new_node->Parent = node;
                        node->Right = move(new_node);
                        break;
                    }
                }
            }
        } else {
            root = move(new_node);
        }

    }

    shared_ptr<TNode<T>> Root_;
    vector<shared_ptr<TNode<T>>> Nodes_;

};

template <class T>
TTree<T> build_tree(vector<T> v) {
    random_device rd;
    mt19937_64 g(rd());
    shuffle(v.begin(), v.end(), g);

    TTree<T> tree;
    for (const auto& x : v) {
        tree.insert(x);
    }

    return tree;
}

int main() {
    TTree<int> tree = build_tree<int>({1, 2, 3, 4, 5});


    while (true) {
        string s;
        cin >> s;
        if (s == "r") {
            size_t n;
            cin >> n;
            random_device rd;
            mt19937_64 g(rd());
            map<int, size_t> result;
            for (size_t i = 0; i < n; i++) {
                auto node = tree.random([&g]() { return g(); });
                if (node) {
                    result[node->Value]++;
                }
            }

            for (const auto& x : result) {
                cerr << x.first << "\t" << x.second << endl;
            }
        } else if (s == "i") {
            int value;
            cin >> value;
            tree.insert(value);
            cerr << "inserted" << endl;
        } else if (s == "f") {
            int value;
            cin >> value;
            auto node = tree.find(value);
            cerr << (node ? "found" : "not found") << endl;
        } else if (s == "d") {
            int value;
            cin >> value;
            auto node = tree.find(value);
            if (node) {
                tree.erase(node);
                cerr << "deleted" << endl;
            } else {
                cerr << "not found" << endl;
            }
        }
    }
}
