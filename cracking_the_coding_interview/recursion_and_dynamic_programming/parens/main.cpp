#include <iostream>
#include <string>

using namespace std;

void parens(size_t opened, size_t closed, string result, ostream& out) {
    if (opened == 0 && closed == 0) {
        out << result << endl;
    } else if (closed > opened) {
        if (opened > 0) {
            parens(opened - 1, closed, result + "(", out);
        }
        parens(opened, closed - 1, result + ")", out);
    } else {
        parens(opened - 1, closed, result + "(", out);
    }
}

void parens(size_t n, ostream& out) {
    parens(n, n, {}, out); 
}

int main(int argc, const char* argv[]) {
    size_t n = 3;
    if (argc > 1) {
        n = stoul(argv[1]);
    }

    parens(n, cout);
}
