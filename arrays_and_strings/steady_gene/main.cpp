#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

const string LETTERS = "GATC";

bool is_steady_enough(const unordered_map<char, size_t>& counts, const size_t size) {
    for (const auto& x : LETTERS) {
        if (counts.at(x) > size) {
            return false;
        }
    }
    return true;
}

size_t steady_gene(const string& gene) {
    unordered_map<char, size_t> counts;
    for (const auto& x : LETTERS) {
        counts.emplace(x, 0);
    }
    for (const auto& x : gene) {
        counts.at(x)++;
    }

    size_t min_size = gene.size();
    size_t end = 0;
    for (size_t begin = 0; begin < gene.size(); begin++) {
        while (end < gene.size() && !is_steady_enough(counts, gene.size() / 4)) {
            counts.at(gene[end])--;
            end++;
        }

        if (is_steady_enough(counts, gene.size() / 4)) {
            min_size = min(min_size, end - begin);
        }

        counts.at(gene[begin])++;
    }

    return min_size;
}

int main() {
    size_t n;
    cin >> n;
    cin.ignore();

    string gene;
    for (size_t i = 0; i < n; i++) {
        gene += cin.get();
    }

    cout << steady_gene(gene) << endl;
}
