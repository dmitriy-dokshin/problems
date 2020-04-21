#include <iostream>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (const auto& x : v) {
        out << x;
    }
    return out;
}

void lool_and_say(const size_t n, ostream& out) {
    vector<int> v{1};
    for (size_t i = 0; i < n; i++) {
        out << v << endl;

        vector<int> next;
        int val = v[0];
        int l = 1;
        for (size_t j = 1; j < v.size(); j++) {
            if (v[j] == val) {
                l++;
            } else {
                next.emplace_back(l);
                next.emplace_back(val);
                val = v[j];
                l = 1;
            }
        }
        next.emplace_back(l);
        next.emplace_back(val);
        v = std::move(next);
    }
}

int main(const int argc, const char* argv[]) {
    size_t n = 10;
    if (argc > 1) {
        n = stoi(argv[1]);
    }

    lool_and_say(n, cout);
}
