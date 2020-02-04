#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "{";
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << ", " << v[i];
        }
    }
    out << "}";
    return out;
}

int main() {
    /* Always go to the farthest possible point.
     * Let's prove that it's a save move.
     * A safe move is a move that is a part of an optimal solution.
     * Suppose there's an optimal solution with stops g0, g1, ...
     * Suppose also that g is currently the fartherst possible point.
     * There are 3 possible cases:
     * 1. g < g0 - actually that's impossible by definition of g as the farthest possible point.
     * 2. g0 < g < g1 - in that case we can replace g0 with g without changing stops count, so g can be a part of the optiomal solution.
     * 3. g1 < g - in that case g0 and g1 could be skipped, that's impossible cause g0 and g1 belong to the optimal solution.
     * Consequently selecting at each step the farthest possible point we can find an optimal solution.
     */

    vector<bool> map {0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0};
    vector<size_t> stops;
    size_t l = 3;
    size_t i = 0;
    while (i + l < map.size()) {
        size_t j = i + l;
        while (j > i && !map[j]) {
            j--;
        }

        if (i == j) {
            throw runtime_error("Unable to build route");
        }

        i = j;
        stops.emplace_back(i);
    }

    vector<bool> route;
    route.resize(map.size());
    for (const auto& stop : stops) {
        route[stop] = true;
    }

    cerr << map << endl;
    cerr << route << endl;
}
