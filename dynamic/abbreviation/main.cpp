#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool abbreviation(const string& a, const string& b) {
    vector<vector<bool>> tmp;
    tmp.resize(a.size() + 1);
    for (auto& x : tmp) {
        x.resize(b.size() + 1);
    }

    tmp[0][0] = true;
    for (size_t i = 0; i < a.size() && islower(a[i]); i++) {
        tmp[i + 1][0] = true;
    }

    for (size_t i = 1; i <= a.size(); i++) {
        for (size_t j = 1; j <= b.size(); j++) {
            if (a[i - 1] == b[j - 1]) {
                tmp[i][j] = tmp[i - 1][j - 1];
            } else if (toupper(a[i - 1]) == b[j - 1]) {
                tmp[i][j] = tmp[i - 1][j] || tmp[i - 1][j - 1];
            } else if (islower(a[i - 1])) {
                tmp[i][j] = tmp[i - 1][j];
            } else {
                tmp[i][j] = false;
            }
        }
    }

    return tmp[a.size()][b.size()];
}

int main() {
	size_t n;
	cin >> n;
	cin.ignore();
	for (size_t i = 0; i < n; i++) {
	    string a, b;
	    getline(cin, a);
	    getline(cin, b);
	    cout << (abbreviation(a, b) ? "YES" : "NO") << endl;
    }
}
