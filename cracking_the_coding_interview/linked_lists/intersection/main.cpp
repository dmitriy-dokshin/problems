#include <iostream>
#include <vector>
#include <utility>

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

template <class T>
pair<const TNode<T>*, size_t> Iterate(const TNode<T>* head) {
    size_t l = 0;
    const TNode<T>* prev = nullptr;
    const TNode<T>* x = head;
    while (x) {
        l++;
        prev = x;
        x = x->Next;
    }
    return {prev, l};
}

template <class T>
const TNode<T>* Intersection(const TNode<T>* h1, const TNode<T>* h2) {
    auto t1 = Iterate(h1);
    auto t2 = Iterate(h2);
    if (t1.first == t2.first) {
        const auto* x1 = h1;
        const auto* x2 = h2;
        const size_t l1 = t1.second;
        const size_t l2 = t2.second;
        if (l1 < l2) {
            for (size_t i = 0; i < l2 - l1; i++) {
                x2 = x2->Next;
            }
        } else {
            for (size_t i = 0; i < l1 - l2; i++) {
                x1 = x1->Next;
            }
        }

        while (x1 != x2) {
            x1 = x1->Next;
            x2 = x2->Next;
        }

        return x1;
    }

    return nullptr;
}

int main() {
    auto l1 = MakeList<int>({1, 2, 3, 4, 5});
    auto l2 = MakeList<int>({6, 7, 8});
    l1[4].Next = &l2[0];
    //l2[2].Next = &l1[4];
    const auto* x = Intersection(&l1[0], &l2[0]);
    if (x) {
        cerr << x->Value << endl;
    } else {
        cerr << "No intersection" << endl;
    }
}
