#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

bool IsSteady(const unordered_map<char, size_t>& counter, const size_t size) {
    const static string ALPHABET = "ACTG";
    for (const auto& letter : ALPHABET) {
        const auto x = counter.find(letter);
        if (x != counter.end() && x->second > size) {
            return false;
        }
    }
    return true;
    
}

size_t SteadyGene(const string& gene) {
    if (gene.size() % 4 != 0) {
        throw runtime_error("Invalid gene size");
    }

    unordered_map<char, size_t> counter;
    for (const auto& x : gene) {
        counter[x]++;
    }

    size_t result = gene.size();
    size_t j = 0;
    for (size_t i = 0; i < gene.size(); i++) {
        while (!IsSteady(counter, gene.size() / 4) && j < gene.size()) {
            counter[gene[j]]--;
            j++;
        }
        if (IsSteady(counter, gene.size() / 4)) {
            result = min(result, j - i);
        }
        counter[gene[i]]++;
    }
    return result;
}

int main() {
    vector<pair<string, size_t>> tests {
        {"GAAATAAA", 5},
        {"TGATGCCGTCCCCTCAACTTGAGTGCTCCTAATGCGTTGC", 5}
    };
    for (const auto& x : tests) {
        const size_t result = SteadyGene(x.first);
        if (result == x.second) {
            cerr << "OK" << endl;
        } else {
            cerr << "ERROR\t" << result << " != " << x.second << endl;
        }
    }
}
