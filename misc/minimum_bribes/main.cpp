#include <iostream>
#include <vector>

using namespace std;

template <class T>
istream& operator>>(istream& in, vector<T>& v) {
    while (v.size() < v.capacity()) {
        T val;
        cin >> val;
        v.emplace_back(move(val));
    }
    return in;
}

template <class T>
bool minimum_bribes(vector<T>& v, size_t* min_bribes, const size_t max_bribes_per_person = 2) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] > i + 1) {
            size_t bribes = v[i] - (i + 1);
            if (bribes > max_bribes_per_person) {
                return false;
            }
        }
    }

    *min_bribes = 0;
    for (size_t i = v.size(); i > 0; i--) {
        for (size_t j = i - 1; j < v.size() - 1 && v[j] > v[j + 1]; j++) {
            *min_bribes += 1;
            swap(v[j], v[j + 1]);
        }
    }

    return true;
}

int main() {
    size_t t;
    cin >> t;
    while (t-- > 0) {
        size_t n;
        cin >> n;

        vector<unsigned long> v;
        v.reserve(n);
        cin >> v;

        size_t min_bribes;
        if (minimum_bribes(v, &min_bribes)) {
            cout << min_bribes << endl;
        } else {
            cout << "Too chaotic" << endl;
        }
    }
}
