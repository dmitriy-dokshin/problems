#include <stack>
#include <utility>

template <class T>
class TMinStack {
public:
    using value_type = T;

    template <class T_>
    void emplace(T_&& val) {
        if (Min_.empty() || val <= Min_.top()) {
            Min_.emplace(val);
        }
        Stack_.emplace(std::forward<T_>(val));
    }

    void pop() {
        if (!Min_.empty() && Stack_.top() == Min_.top()) {
            Min_.pop();
        }
        Stack_.pop();
    }

    const T& top() const {
        return Stack_.top();
    }

    const T& min() const {
        return Min_.top();
    }

    bool empty() const {
        return Stack_.empty();
    }

    size_t size() {
        return Stack_.size();
    }

    void clear() {
        Stack_.clear();
        Min_.clear();
    }

private:
    std::stack<T> Stack_;
    std::stack<T> Min_;
};

