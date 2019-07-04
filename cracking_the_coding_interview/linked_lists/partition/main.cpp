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
TNode<T>* Partition(TNode<T>* head, const T& value) {
    TNode<T>* result = nullptr;
    TNode<T>* less = nullptr;
    TNode<T>* prev = nullptr;
    TNode<T>* x = head;
    bool found = false;
    while (x) {
        if (x->Value < value && found) {
            prev->Next = x->Next;
            if (less) {
                less->Next = x;
            } else {
                result = x;
            }
            less = x;
            x = prev->Next;
        } else {
            if (x->Value == value) {
                found = true;
            }
            prev = x;
            x = x->Next;
        }
    }

    if (less) {
        less->Next = head;
        return result;
    } else {
        return head;
    }
}

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
vector<TNode<T>> MakeList(vector<T>&& v) {
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

int main() {
    auto list = MakeList<int>({1, 5, 8, 5, 10, 2, 1});
    auto* head = &list.front();
    cerr << head << endl;
    head = Partition(head, 5);
    cerr << head << endl;
}
