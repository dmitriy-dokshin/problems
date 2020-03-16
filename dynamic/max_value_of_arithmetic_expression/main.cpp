#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using namespace std;

enum EOperationType {
    OT_Add = 0,
    OT_Subtract = 1,
    OT_Multiply = 2
};

ostream& operator<<(ostream& out, const EOperationType op) {
    switch (op) {
        case OT_Add:
            out << '+';
            break;
        case OT_Subtract:
            out << '-';
            break;
        case OT_Multiply:
            out << '*';
            break;
        default:
            throw runtime_error("Unknown operation type");
    }
    return out;
}

bool try_parse_op(const char c, EOperationType& op) {
    switch (c) {
        case '+':
            op = OT_Add;
            break;
        case '-':
            op = OT_Subtract;
            break;
        case '*':
            op = OT_Multiply;
            break;
        default:
            return false;
    }
    return true;
}

template <class T>
class TMinMax {
public:
    T Min = numeric_limits<T>::max();
    T Max = numeric_limits<T>::min();
};

template <class T>
TMinMax<T> calculate_min_max(const TMinMax<T>& x, const TMinMax<T>& y, const EOperationType op) {
    switch (op) {
        case OT_Add:
            return {x.Min + y.Min, x.Max + y.Max};
        case OT_Subtract:
            return {x.Min - y.Max, x.Max - y.Min};
        case OT_Multiply:
            return {
                min({x.Min * y.Min, x.Min * y.Max, x.Max * y.Min, x.Max * y.Max}),
                max({x.Min * y.Min, x.Min * y.Max, x.Max * y.Min, x.Max * y.Max})
            };
        default:
            throw runtime_error("Unknown operation type");
    }
}

template <class T>
class TUpperTriangularMatrix {
public:
    TUpperTriangularMatrix(size_t size)
        : Size_(size)
        , Data_(size*(size + 1)/2)
    {
    }

    T& operator()(size_t i, size_t j) {
        size_t shift = i*(2*Size_ - i + 1)/2; // n*(n + 1)/2 - (n - i)*(n - i + 1)/2
        j -= i;
        return Data_.at(shift + j);
    }

private:
    const size_t Size_;
    vector<T> Data_;
};

template <class T>
T max_value_of_arithmetic_expression(const vector<T>& values, const vector<EOperationType>& ops) {
    TUpperTriangularMatrix<TMinMax<T>> res(values.size());
    for (size_t d = 0; d < values.size(); d++) {
        for (size_t i = 0, j = d; j < values.size(); i++, j++) {
            if (d == 0) {
                res(i, j) = {values[i], values[i]};
            } else if (d == 1) {
                res(i, j) = calculate_min_max(res(i, i), res(j, j), ops[i]);
            } else {
                for (size_t mid = i; mid < j; mid++) {
                    auto x = calculate_min_max(res(i, mid), res(mid + 1, j), ops[mid]);
                    res(i, j).Min = min(res(i, j).Min, x.Min);
                    res(i, j).Max = max(res(i, j).Max, x.Max);
                }
            }
        }
    }
    return res(0, values.size() - 1).Max;
}

void read(istream& in, vector<long>& values, vector<EOperationType>& ops) {
    string s;
    char c;
    while (in.get(c)) {
        EOperationType op;
        if (c >= '0' && c <= '9') {
            s += c;
        } else if (try_parse_op(c, op)) {
            values.emplace_back(stol(s));
            ops.emplace_back(op);
            s.clear();
        } else if (c == '\n') {
            break;
        }
    }
    values.emplace_back(stol(s));
}

void print(ostream& out, const vector<long>& values, const vector<EOperationType>& ops) {
    out << values[0];
    for (size_t i = 1; i < values.size(); i++) {
        out << " " << ops[i - 1] << " " << values[i];
    }
    out << endl;
}

int main() {
    vector<long> values;
    vector<EOperationType> ops;

    read(cin, values, ops);

    print(cerr, values, ops);

    cout << max_value_of_arithmetic_expression(values, ops) << endl;
}
