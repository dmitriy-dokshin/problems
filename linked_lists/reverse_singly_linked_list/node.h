#include <stdexcept>
#include <initializer_list>
#include <utility>

template <class T>
class TNode {
public:
    TNode() = default;

    TNode(const TNode&) = delete;

    TNode(TNode&& other) {
        *this = std::move(other);
    }

    TNode(std::initializer_list<T> values) {
        if (values.size() == 0) {
            throw std::runtime_error("values list is empty");
        }

        TNode* node = nullptr;
        for (auto& value : values) {
            if (node) {
                node->Next = new TNode;
                node = node->Next;
            } else {
                node = this;
            }

            node->Value = std::move(value);
        }
    }

    ~TNode() {
        delete Next;
    }

    TNode& operator=(const TNode&) = delete;

    TNode& operator=(TNode&& other) {
        Value = std::move(other.Value);
        Next = other.Next;
        other.Next = nullptr;
        return *this;
    }

    T Value;
    TNode* Next = nullptr;
};

template <class T>
bool operator==(const TNode<T>& x, const TNode<T>& y) {
    return x.Value == y.Value && ((!x.Next && !y.Next) || (x.Next && y.Next && *x.Next == *y.Next)); 
}
