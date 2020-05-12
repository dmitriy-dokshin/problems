#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& out, stack<T>& target) {
    stack<T> tmp;
    while (!target.empty()) {
        tmp.push(move(target.top()));
        target.pop();
    }

    if (!tmp.empty()) {
        out << tmp.top();
        target.push(move(tmp.top()));
        tmp.pop();
        while (!tmp.empty()) {
            out << " " << tmp.top();
            target.push(move(tmp.top()));
            tmp.pop();
        }
    }

    return out;
}

template <class T>
ostream& operator<<(ostream& out, vector<stack<T>>& towers) {
    for (size_t i = 0; i < towers.size(); i++) {
        cerr << i << ":\t" << towers[i] << endl;
    }
    return out;
}

template <class T>
void move(vector<stack<T>>& towers, size_t i, size_t j) {
    if (towers[j].empty() || towers[j].top() > towers[i].top()) {
        towers[j].push(move(towers[i].top()));
        towers[i].pop();
        /*
        cerr << towers << endl;
        cin.get();
        */
    } else {
        for (size_t k = 0; k < towers.size(); k++) {
            if (k != i && k != j) {
                move(towers, j, k);
                move(towers, i, j);
                move(towers, k, j);
            }
        }
    }
}

template <class T>
void towers_of_hanoi(vector<stack<T>>& towers) {
    while (!towers[0].empty()) {
        move(towers, 0, towers.size() - 1);
    }
}

int main() {
    size_t n = 3;
    size_t h = 4;

    vector<stack<int>> towers;
    towers.resize(n);
    for (size_t i = 0; i < h; i++) {
        towers[0].push(h - i);
    }

    cerr << towers << endl;
    towers_of_hanoi(towers);
    cerr << towers << endl;
}
