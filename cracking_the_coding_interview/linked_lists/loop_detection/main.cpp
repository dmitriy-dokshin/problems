
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class TNode {
public:
    T Value = {};
    TNode* Next = nullptr;
};

template <class T>
vector<TNode<T>> MakeList(const vector<T>& v) {
    vector<TNode<T>> list;
    list.reserve(v.size());
    if (!v.empty()) {
        list.emplace_back(TNode<T>{v[0]});
        for (size_t i = 1; i < v.size(); i++) {
            list.emplace_back(TNode<T>{v[i]});
            list[i - 1].Next = &list[i];
        }
    }
    return list;
}

template <class T>
const TNode<T>* FindLoop(const TNode<T>* head) {
    const auto* slow = head;
    const auto* fast = head;

    while (fast && fast->Next) {
        slow = slow->Next;
        fast = fast->Next->Next;
        if (slow == fast) {
            break;
        }
    }

    if (!fast || !fast->Next) {
        return nullptr;
    }

    slow = head;
    while (slow != fast) {
        slow = slow->Next;
        fast = fast->Next;
    }

    return fast;

}

int main() {
    vector<size_t> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < v.size(); i++) {
        auto list = MakeList(v);

        list[list.size() - 1].Next = &list[i];

        const auto* loop_head = FindLoop(&list[0]);

        cerr << i << "\t";
        if (!loop_head) {
            cerr << "loop head is null";
        } else if (loop_head->Value != i) {
            cerr << "loop head is wrong: " << loop_head->Value;
        } else {
            cerr << "ok";
        }
        cerr << endl;
    }
}
