#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

using namespace std;

template <class TKey, class TValue>
class TCacheRecord {
public:
    shared_ptr<TCacheRecord> Prev;
    shared_ptr<TCacheRecord> Next;
    TKey Key;
    TValue Value;
};

template <class TKey, class TValue>
using TCacheRecordPtr = shared_ptr<TCacheRecord<TKey, TValue>>;

template <class TKey, class TValue>
class TCache {
public:
    TCache(size_t capacity)
        : Capacity_(capacity)
    {
    }

    optional<TValue> Get(const TKey& key) {
        auto record = GetRecord(key);
        return record ? make_optional(record->Value) : nullopt;
    }

    template <class TKey_, class TValue_>
    void Set(TKey_&& key, TValue_&& value) {
        auto record = GetRecord(key);
        if (record) {
            record->Value = forward<TValue_>(value);
        } else {
            if (Cache_.size() == Capacity_) {
                Pop();
            }

            record = make_shared<TCacheRecord>();
            record->Key = key;
            record->Value = forward<TValue_>(value);
            Push(record);
            Cache_.emplace(forward<TKey_>(key), move(record));
        }
    }

private:
    using TCacheRecord = TCacheRecord<TKey, TValue>;
    using TCacheRecordPtr = TCacheRecordPtr<TKey, TValue>;

    TCacheRecordPtr GetRecord(const TKey& key) {
        auto x = Cache_.find(key);
        if (x != Cache_.end()) {
            auto record = x->second;
            Remove(record);
            Push(record);
            return record;
        } else {
            return {};
        }
    }

    void Remove(TCacheRecordPtr record) {
        if (record->Prev) {
            record->Prev->Next = record->Next;
        }
        if (record->Next) {
            record->Next->Prev = record->Prev;
        }
        if (Head_ == record) {
            Head_ = record->Next;
        }
        if (Tail_ == record) {
            Tail_ = record->Prev;
        }
        record->Prev = nullptr;
        record->Next = nullptr;
    }

    void Push(TCacheRecordPtr record) {
        if (Head_) {
            Head_->Prev = record;
            record->Next = Head_;
        }
        Head_ = record;
        if (!Tail_) {
            Tail_ = record;
        }
    }

    void Pop() {
        auto tail = Tail_;
        if (tail) {
            Remove(tail);
            Cache_.erase(tail->Key);
        }
    }

    unordered_map<TKey, TCacheRecordPtr> Cache_;
    TCacheRecordPtr Head_;
    TCacheRecordPtr Tail_;
    size_t Capacity_;
};

template <class TKey, class TValue>
TValue get(TCache<TKey, TValue>& cache, const TKey& key) {
    auto x = cache.Get(key);
    return x ? *x : -1;
}

int main() {
    size_t n;
    cin >> n;
    size_t capacity;
    cin >> capacity;
    TCache<int, int> cache(capacity);
    while (n > 0) {
        n--;
        char command;
        cin >> command;
        switch (command) {
            case 'G': {
                int value;
                cin >> value;
                cout << get(cache, value) << endl;
            } break;
            case 'S': {
                int key;
                cin >> key;
                int value;
                cin >> value;
                cache.Set(key, value);
            } break;
        }
    }
}
