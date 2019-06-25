#include <iostream>
#include <stdexcept>
#include <stack>

using namespace std;

template <class T>
class TQueue {
public:
    void Push(const T& val) {
        Tail_.push(val);
    }

    void Pop() {
        FillUp();
        Head_.pop();
    }

    const T& Top() {
        FillUp();
        if (Head_.empty()) {
            throw runtime_error("Queue is empty");
        }
        return Head_.top();
    }

private:
    void FillUp() {
        if (Head_.empty()) {
            while (!Tail_.empty()) {
                Head_.emplace(Tail_.top());
                Tail_.pop();
            }
        }
    }

    stack<T> Tail_;
    stack<T> Head_;
};

enum EQueryType {
    QT_Push = 1,
    QT_Pop = 2,
    QT_Top = 3
};

int main() {
    size_t n;
    cin >> n;
    cin.ignore();

    TQueue<int> queue;
    int type;
    int val;
    for (size_t i = 0; i < n; i++) {
        cin >> type;
        switch (type) {
            case QT_Push:
                cin >> val;
                queue.Push(val);
                break;
            case QT_Pop:
                queue.Pop();
                break;
            case QT_Top:
                cout << queue.Top() << endl;
                break;
            default:
                throw runtime_error("Unknown query type");
        }
        cin.ignore();
    }
}
