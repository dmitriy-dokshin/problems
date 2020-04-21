#include "node.h"

#include <iostream>
#include <tuple>
#include <vector>

template <class T>
TNode<T>* Reverse(TNode<T>* node) {
    TNode<T>* prev = nullptr;
    while (node) {
        TNode<T>* next = node->Next;
        node->Next = prev;
        prev = node;
        node = next;
    }
    return prev;
}

int main() {
    using TNode = TNode<int>;

    std::vector<std::tuple<TNode, TNode, bool>> tests;
    tests.emplace_back(TNode{1}, TNode{1}, true);
    tests.emplace_back(TNode{1, 2, 3}, TNode{3, 2, 1}, true);
    tests.emplace_back(TNode{1, 2, 3}, TNode{1, 2, 3}, false);
    
    for (auto& test : tests) {
        const bool ok = (*Reverse(&std::get<0>(test)) == std::get<1>(test)) == std::get<2>(test);
        std::cerr << (ok ? "OK" : "ERROR") << std::endl;
    }
}
