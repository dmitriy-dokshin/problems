#include "../two_stacks_queue/two_stacks_queue.h"
#include "../min_stack/min_stack.h"

template <class T>
class TMinQueue: public TTwoStacksQueue<TMinStack<T>> {
private:
    using TBase_ = TTwoStacksQueue<TMinStack<T>>;

public:
    const T& Min() const {
        const T* min = nullptr;
        if (!TBase_::In_.empty()) {
            min = &TBase_::In_.min();
        }

        if (!TBase_::Out_.empty()) {
            min = min ? &std::min(TBase_::Out_.min(), *min) : &TBase_::Out_.min();
        }

        return *min;
    }
};
