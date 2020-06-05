#include <lib/random/random.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

#include <string.h>

using namespace std;

const char DELIM = '\n';

void save_random_strings(size_t n, size_t min_len, size_t max_len, char min_val, char max_val, ostream& out) {
    random_device rd;
    mt19937_64 len_gen(rd());
    uniform_int_distribution<size_t> len_dist(min_len, max_len);
    for (size_t i = 0; i < n; i++) {
        size_t len = len_dist(len_gen);
        auto s = TRandom<char>::random_vector(len, min_val, max_val, rd());
        for (const auto& x : s) {
            out << x;
        }
        out << DELIM;;
    }
}

class TBlock {
public:
    TBlock(const filesystem::path& in_path)
        : In_(in_path)
    {
    }

    const string& get() const {
        return Value_;
    }

    bool reset() {
        Value_.clear();
        char c;
        while (In_.get(c) && c != DELIM) {
            Value_ += c;
        }
        return !Value_.empty();
    }

private:
    ifstream In_;
    string Value_;
};

template <class TComp = less<string>>
void sort_blocks(const filesystem::path& tmp_dir, TComp comp = {}) {
    static const size_t MEMORY_LIMIT = 1024;

    size_t memory_usage = 0;
    vector<string> v;
    string s;
    char c;
    size_t i = 0;
    
    auto flush = [&] {
        sort(v.begin(), v.end(), comp);
        filesystem::path out_path = tmp_dir / to_string(i++);
        ofstream out(out_path);
        for (const auto& x : v) {
            out << x << endl;
        }
    };

    while (cin.get(c)) {
        memory_usage++;
        if (c == DELIM) {
            v.emplace_back(move(s));
        } else {
            s += c;
        }

        if (!v.empty() && memory_usage > MEMORY_LIMIT) {
            memory_usage = s.size();
            flush();
            v.clear();
        }
    }

    if (!v.empty()) {
        flush();
    }
}

template <class TComp = greater<string>>
void merge_blocks(const filesystem::path& tmp_dir, ostream& out, TComp comp = {}) {
    vector<TBlock> blocks;
    for (const auto& x : filesystem::directory_iterator(tmp_dir)) {
        blocks.emplace_back(x.path());
    }

    auto block_comp = [&comp](const TBlock* b1, const TBlock* b2) { return comp(b1->get(), b2->get()); };
    priority_queue<TBlock*, vector<TBlock*>, decltype(block_comp)> q(block_comp);
    for (auto& x : blocks) {
        if (x.reset()) {
            q.push(&x);
        }
    }

    while (!q.empty()) {
        TBlock* x = q.top();
        out << x->get() << DELIM;
        q.pop();
        if (x->reset()) {
            q.push(x);
        }
    }
}

int main(int argc, const char* argv[]) {
    if (argc > 1) {
        const char* mode = argv[1];
        if (strcmp(mode, "gen") == 0) {
            save_random_strings(1024, 1, 32, 'a', 'z', cout);
        } else if (strcmp(mode, "sort") == 0) {
            if (argc > 2) {
                const char* tmp_dir = argv[2];
                sort_blocks(tmp_dir);
                merge_blocks(tmp_dir, cout);
            }
        }
    }
}
