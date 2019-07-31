#include <initializer_list>
#include <iostream>
#include <stack>

using namespace std;

template <class T>
class TQueueViaStacks {
public:
    TQueueViaStacks(initializer_list<T> list) {
        for (auto& x : list) {
            Enqueue(move(x));
        }
    }

    template <class T_>
    void Enqueue(T_&& val) {
        while (!Queue_.empty()) {
            Stack_.emplace(Queue_.top());
            Queue_.pop();
        }
        Stack_.emplace(forward<T_>(val));
    }

    T Dequeue() {
        while (!Stack_.empty()) {
            Queue_.emplace(Stack_.top());
            Stack_.pop();
        }
        T result = Queue_.top();
        Queue_.pop();
        return result;
    }

    bool Empty() {
        return Queue_.empty() && Stack_.empty();
    }

private:
    stack<T> Queue_;
    stack<T> Stack_;
};

int main() {
    TQueueViaStacks<int> queue({1, 2, 3, 4, 5});
    for (size_t i = 0; i < 3; i++) {
        cerr << queue.Dequeue() << endl;
    }
    queue.Enqueue(6);
    queue.Enqueue(7);;
    while (!queue.Empty()) {
        cerr << queue.Dequeue() << endl;
    }
}
