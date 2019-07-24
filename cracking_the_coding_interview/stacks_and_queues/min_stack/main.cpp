#include <initializer_list>
#include <iostream>
#include <stack>

using namespace std;

template <class T>
class TMinStack {
public:
    TMinStack() = default;

    template <class T_>
    TMinStack (initializer_list<T_> l) {
        for (auto& x : l) {
            Push(move(x));
        }
    }

    template <class T_>
    void Push(T_&& val) {
        Values_.emplace(move(val));
        if (Min_.empty() || Values_.top() <= Min_.top()) {
            Min_.emplace(Values_.top());
        }
    }

    T Pop() {
        T val = Values_.top();
        Values_.pop();
        if (val == Min_.top()) {
            Min_.pop();
        }
        return val;
    }

    bool Empty() const {
        return Values_.empty();
    }

    const T& Top() const {
        return Values_.top();
    }

    const T& Min() const {
        return Min_.top();
    }

private:
    stack<T> Values_;
    stack<T> Min_;
};

int main() {
    TMinStack<int> stack{7, 8, 9, 5, 5, 5, 2, 3, 4, 5};
    while (!stack.Empty()) {
        cerr << stack.Top() << "\t" << stack.Min() << endl;
        stack.Pop();
    }
}
