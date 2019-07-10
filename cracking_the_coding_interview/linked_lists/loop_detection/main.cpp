
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
ostream& operator<<(ostream& out, const TNode<T>* x) {
    if (x) {
        out << x->Value;
        while (x->Next) {
            out << " -> " << x->Next->Value;
            x = x->Next;
        }
    }
    return out;
}

template <class T>
vector<TNode<T>> MakeList(const vector<T>& v) {
    vector<TNode<T>> result;
    result.reserve(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        result.emplace_back(TNode<T>{v[i]});
        if (result.size() > 1) {
            result[result.size() - 2].Next = &result[result.size() - 1];
        }
    }
    return result;
}

template <class T>
const TNode<T>* FindLoop(const TNode<T>* head) {
    const auto* fast = head;
    const auto* slow = head;
    size_t i = 0;
    do {
        fast = fast->Next;
        if (i % 2 == 1) {
            slow = slow->Next;
        }
        i++;
    } while (fast && fast != slow);

    if (fast) {
        fast = head;
        if (i % 2 == 1) {
            // WTF???
            slow = slow->Next;
        }
        while (fast != slow) {
            fast = fast->Next;
            slow = slow->Next;
        }
    }

    return fast;
}

int main() {
    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < v.size(); i++) {
        auto list = MakeList(v);
        list[list.size() - 1].Next = &list[i];
        const auto* loopHead = FindLoop(&list[0]);
        cerr << (loopHead && static_cast<size_t>(loopHead->Value) == i ? "OK" : "ERROR") << endl;
    }
}
