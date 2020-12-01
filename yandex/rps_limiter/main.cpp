#include <chrono>
#include <iostream>
#include <list>

using namespace std;
using namespace chrono;

size_t now() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

class TRpsLimiter {
public:
    bool Request() {
        auto ts = now();
        if (!Events_.empty() && Events_.front() < ts - EventsLimitPeriod_) {
            Events_.pop_front();
        }

        if (Events_.size() < EventsLimit_) {
            Events_.push_back(ts);
            return true;
        } else {
            return false;
        }
    }

private:
    list<size_t> Events_;
    size_t EventsLimit_ = 10 * 1000;
    size_t EventsLimitPeriod_ = 1000;
};

int main() {
    TRpsLimiter limiter;
    size_t total_count = static_cast<size_t>(50) * 1000 * 1000;
    size_t processed_count = 0;
    for (size_t i = 0; i < total_count; i++) {
        if (limiter.Request()) {
            processed_count++;
        }
    }
    cerr << "total_count\t" << total_count << endl;
    cerr << "processed_count\t" << processed_count << endl;
}
