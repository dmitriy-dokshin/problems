#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

class TUserEventCounter {
public:
    TUserEventCounter(size_t period, size_t target_event_count)
        : Period_(period)
        , TargetEventCount_(target_event_count)
    {
    }


    void AddEvent(const string& user_id, const size_t current_ts) {
        CleanUp(current_ts);
        Events_.emplace(user_id, current_ts);
        ModifyEventCount(user_id, [](size_t& event_count) { event_count++; });
    }

    size_t GetUsersCount(size_t current_ts) {
        CleanUp(current_ts);
        return TargetUsersCount_;
    }

private:
    void CleanUp(const size_t current_ts) {
        while (!Events_.empty() && Events_.back().second < current_ts - Period_) {
            ModifyEventCount(Events_.back().first, [](size_t& event_count) { event_count--; });
        }

    }

    void ModifyEventCount(const string& user_id, function<void(size_t&)> f) {
        size_t& event_count = UserEventCounts_[user_id];
        if (event_count == TargetEventCount_) {
            TargetUsersCount_--;
        }
        f(event_count);
        if (event_count == TargetEventCount_) {
            TargetUsersCount_++;
        }
    }

    size_t Period_;
    size_t TargetEventCount_;
    queue<pair<string, size_t>> Events_;
    unordered_map<string, size_t> UserEventCounts_;
    size_t TargetUsersCount_ = 0;
};

int main() {
    TUserEventCounter event_counter(300, 100);
    for (size_t i = 900; i < 1000; i++) {
        event_counter.AddEvent("user_1", i);
        if (i % 2) {
            event_counter.AddEvent("user_2", i);
        }
    }
    cerr << event_counter.GetUsersCount(1000) << endl;
}
