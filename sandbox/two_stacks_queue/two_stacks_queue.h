#include <utility>

template <class TStack_, class T = typename TStack_::value_type>
class TTwoStacksQueue {
public:
    template <class T_>
    void Push(T_&& val) {
        In_.emplace(std::forward<T_>(val));
    }

    void Pop() {
        PrepareOut();
        Out_.pop();
    }

    T& Top() {
        PrepareOut();
        return Out_.top();
    }

    bool Empty() const {
        return In_.empty() && Out_.empty();
    }

    size_t Size() {
        return In_.size() + Out_.size();
    }

private:
    void PrepareOut() {
        if (Out_.empty()) {
            while (!In_.empty()) {
                Out_.emplace(std::move(In_.top()));
                In_.pop();
            }
        }
    }

protected:
    TStack_ In_;
    TStack_ Out_;
};

