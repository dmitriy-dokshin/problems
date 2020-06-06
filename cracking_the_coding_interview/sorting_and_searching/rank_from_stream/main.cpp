#include <lib/io/io.h>
#include <lib/random/random.h>

#include <iostream>
#include <set>
#include <unordered_map>

using namespace std;

template <class T>
class TRankTracker {
public:
    // O(log(n)) + O(n)
    void track(const T& value) {
        auto x = Values_.emplace(value);
        if (x.second) {
            if (x.first != Values_.begin()) {
                Ranks_[value] = Ranks_[*--x.first];;
            }
        }

        for (auto x = Values_.find(value); x != Values_.end(); x++) {
            Ranks_[*x]++;
        }
    }

    // O(1)
    size_t get_rank(const T& value) {
        if (auto x = Ranks_.find(value); x != Ranks_.end()) {
            return x->second;
        } else if (!Values_.empty()) {
            return Ranks_.at(*--Values_.end());
        } else {
            return 0;
        }
    }

private:
    set<T> Values_;
    unordered_map<T, size_t> Ranks_;
};

template <class T>
void run() {
    random_device rd;
    auto v = TRandom<T>::random_vector(32, 1, 9, rd());
    cerr << v << endl;

    TRankTracker<T> tracker;
    size_t i = 0;
    char mode;
    while (cin.get(mode)) {
        switch (mode) {
            case 't': {
                    size_t n;
                    cin >> n;
                    while (n-- > 0) {
                        if (i < v.size()) {
                            tracker.track(v.at(i++));
                        } else {
                            cerr << "empty" << endl;
                            break;
                        }
                    }
                    break;
                }
            case 'r': {
                    T value;
                    cin >> value;
                    cout << tracker.get_rank(value) << endl;
                    break;
                }
            case 'q':
                return;
        }
        cin.ignore();
    }
}

int main() {
    run<int>();
}
