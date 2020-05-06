#include <iostream>
#include <vector>

using namespace std;

template <class T>
class TGrid {
public:
    TGrid(vector<T> data, size_t r, size_t c)
        : Data_(move(data))
        , R_(r)
        , C_(c)
    {
    }

    typename vector<T>::reference at(size_t i, size_t j) {
        return Data_.at(index(i, j));
    }

    typename vector<T>::const_reference at(size_t i, size_t j) const {
        return Data_.at(index(i, j));
    }

private:
    size_t index(size_t i, size_t j) const {
        return i * C_ + j;
    }

    vector<T> Data_;
    size_t R_ = 0;
    size_t C_ = 0;
};

bool robot_in_a_grid(const TGrid<bool>& grid, const size_t r, const size_t c, TGrid<char>* const route) {
    TGrid<bool> result = grid;

    for (size_t i = 1; i < r; i++) {
        result.at(i, 0) = result.at(i, 0) && result.at(i - 1, 0);
    }

    for (size_t j = 1; j < c; j++) {
        result.at(0, j) = result.at(0, j) && result.at(0, j - 1);
    }

    for (size_t i = 1; i < r; i++) {
        for (size_t j = 1; j < c; j++) {
            result.at(i, j) = result.at(i, j) && (result.at(i - 1, j) || result.at(i, j - 1));
        }
    }

    size_t i = r - 1;
    size_t j = c - 1;
    route->at(i, j) = '*';
    if (result.at(r - 1, c - 1)) {
        while (i > 0 || j > 0) {
            if (i > 0 && result.at(i - 1, j)) {
                route->at(i - 1, j) = '|';
                i--;
            } else {
                route->at(i, j - 1) = '-';
                j--;
            }
        }
    }

    return result.at(r - 1, c - 1);
}

int main() {
    size_t r;
    cin >> r;

    size_t c;
    cin >> c;

    vector<bool> data;
    data.reserve(r * c);
    while (data.size() < r * c) {
        bool x;
        cin >> x;
        data.emplace_back(x);
    }

    TGrid<bool> grid(move(data), r, c);
    TGrid<char> route(vector<char>(r * c, '.'), r, c);
    if (robot_in_a_grid(grid, r, c, &route)) {
        for (size_t i = 0; i < r; i++) {
            for (size_t j = 0; j < c; j++) {
                cout << route.at(i, j);
            }
            cout << endl;
        }
    } else {
        cout << "Route not found" << endl;
    }
}
