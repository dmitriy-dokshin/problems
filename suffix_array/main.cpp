#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class TSuffix {
public:
    TSuffix(size_t index, pair<size_t, size_t> rank)
        : Index(index)
        , Rank(rank)
    {
    }

    size_t Index = 0;
    pair<size_t, size_t> Rank;
};

bool operator<(const TSuffix& x, const TSuffix& y) {
    return x.Rank < y.Rank;
}

vector<size_t> SuffixArray(const string& s) {
    vector<TSuffix> suffixes;
    suffixes.reserve(s.size());
    for (size_t i = 0; i < s.size(); i++) {
        suffixes.emplace_back(i, pair<size_t, size_t>(s[i], 0));
    }

    vector<size_t> indexes(s.size());
    for (size_t k = 1; k < s.size() * 2; k *= 2) {
        sort(suffixes.begin(), suffixes.end());

        auto prevRank = suffixes[0].Rank;
        suffixes[0].Rank = {1, 0};
        indexes[suffixes[0].Index] = 0;
        for (size_t i = 1; i < suffixes.size(); i++) {
            auto rank = suffixes[i].Rank;
            suffixes[i].Rank = suffixes[i - 1].Rank;
            if (rank != prevRank) {
                suffixes[i].Rank.first++;
            }
            prevRank = rank;
            indexes[suffixes[i].Index] = i;
        }

        for (size_t i = 0; i < suffixes.size(); i++) {
            suffixes[i].Rank.second = i + k < indexes.size() ? suffixes[indexes[i + k]].Rank.first : 0; 
        }
    }

    vector<size_t> result;
    result.reserve(suffixes.size());
    for (const auto& x : suffixes) {
        result.emplace_back(x.Index);
    }

    return result;
}

int main() {
    string s = "banana";

    vector<size_t> arr = SuffixArray(s);

    for (const auto& x : arr) {
        cerr << &s[x] << endl;
    }
}
