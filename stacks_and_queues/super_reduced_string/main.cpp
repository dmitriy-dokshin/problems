#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

void super_reduce(string& s) {
    stack<char> st;
    for (const auto& x : s) {
        if (!st.empty() && st.top() == x) {
            st.pop();
        } else {
            st.push(x);
        }
    }

    s.clear();
    while (!st.empty()) {
        s += st.top();
        st.pop();
    }

    reverse(s.begin(), s.end());

}

int main() {
    string s;
    getline(cin, s);

    super_reduce(s);

    if (s.empty()) {
        s = "Empty String";
    }

    cout << s << endl;
}
