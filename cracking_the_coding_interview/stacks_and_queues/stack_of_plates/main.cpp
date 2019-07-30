#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
class TSetOfStacks {
public:
    TSetOfStacks(size_t maxStackSize)
        : MaxStackSize_(maxStackSize)
    {
    }

    template <class T_>
    void Push(T_&& val) {
        if (!FreeStacks_.empty()) {
            auto p = FreeStacks_.begin();
            Stacks_.at(p->first).emplace(std::forward<T_>(val));
            if (p->second > 1) {
                p->second--;
            } else {
                FreeStacks_.erase(p);
            }
        } else {
            if (Stacks_.empty() || Stacks_.back().size() == MaxStackSize_) {
                Stacks_.emplace_back();
            }
            Stacks_.back().emplace(std::forward<T_>(val));
        }
    }

    T Pop() {
        if (Stacks_.empty() || Stacks_.back().empty()) {
            throw runtime_error("No stacks available");
        }
        return PopAt(Stacks_.size() - 1);
    }

    T PopAt(size_t i) {
        if (i >= Stacks_.size()) {
            throw runtime_error("Invlid stack index: " + to_string(i));
        }
        if (Stacks_[i].empty()) {
            throw runtime_error("Stack is empty");
        }
        T result = Stacks_[i].top();
        Stacks_[i].pop();
        if (i < Stacks_.size() - 1) {
            FreeStacks_[i]++;
        } else {
            while (!Stacks_.empty() && Stacks_.back().empty()) {
                FreeStacks_.erase(Stacks_.size() - 1);
                Stacks_.erase(Stacks_.end() - 1);
            }
        }
        return result;
    }

    size_t StacksSize() const {
        return Stacks_.size();
    }

    bool Empty() const {
        return Stacks_.empty();
    }

private:
    size_t MaxStackSize_;
    vector<stack<T>> Stacks_;
    map<size_t, size_t> FreeStacks_;
};

int main() {
    TSetOfStacks<int> stack(10);
    for (size_t i = 0; i < 50; i++) {
        stack.Push(i);
    }
    vector<int> result;
    while (!stack.Empty()) {
        for (size_t i = 0; i < 5; i++) {
            result.emplace_back(stack.PopAt(i));
        }
    }
    for (const auto& x : result) {
        cerr << x << endl;
    }
}
