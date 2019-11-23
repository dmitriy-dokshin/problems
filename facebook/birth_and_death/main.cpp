#include <iostream>
#include <map>
#include <optional>
#include <random>
#include <vector>
#include <utility>

using namespace std;

// {<birth year>, <death year>}
optional<long> find_year_with_highest_population(const vector<pair<long, long>>& v) {
    map<long, long> population_diff;
    for (const auto& x : v) {
        population_diff[x.first]++;
        population_diff[x.second]--;
    }

    optional<long> result;
    long cur_population = 0;
    long max_population = 0;
    for (const auto& x : population_diff) {
        cur_population += x.second;
        if (cur_population > max_population) {
            max_population = cur_population;
            result = x.first;
        }
    }

    return result;
}

class TInputParams {
public:
    optional<unsigned int> Seed;
    long BirthMin = 1920;
    long BirthMax = 2000;
    long MaxLifeSpan = 100;
    size_t Size = 1000;
};

vector<pair<long, long>> prepare_input(const TInputParams& params) {
    optional<unsigned int> seed = params.Seed;
    if (!seed) {
        random_device rand;
        seed = rand();
    }

    mt19937_64 birth_engine(*seed);
    uniform_int_distribution<long> birth_dist(params.BirthMin, params.BirthMax);

    mt19937_64 life_span_engine(*seed);
    uniform_int_distribution<long> life_span_dist(0, params.MaxLifeSpan);

    vector<pair<long, long>> v;
    v.resize(params.Size);
    for (size_t i = 0; i < v.size(); i++) {
        v[i].first = birth_dist(birth_engine);
        v[i].second = v[i].first + life_span_dist(life_span_engine);
    }

    return v;
}

int main() {
    TInputParams params;
    vector<pair<long, long>> v = prepare_input(params);
    cerr << *find_year_with_highest_population(v) << endl; 
}
