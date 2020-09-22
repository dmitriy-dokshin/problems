#include <lib/utility/utility.h>

#include <utility>

template <class TKey, class TValue = TNothing>
class TNode {
public:
    using key_type = TKey;
    using value_type = TValue;

    template <class TKey_>
    TNode(TKey_&& key)
        : Key(std::forward<TKey_>(key))
    {
    }

    template <class TKey_, class TValue_>
    TNode(TKey_&& key, TValue_&& value)
        : Key(std::forward<TKey_>(key))
        , Value(std::forward<TValue_>(value))
    {
    }

    TKey Key = {};
    TValue Value = {};
    TNode<TKey, TValue>* Left = nullptr;
    TNode<TKey, TValue>* Right = nullptr;
};
