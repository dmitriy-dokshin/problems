#include <iostream>
#include <optional>
#include <string>
#include <vector>

using namespace std;

using TCache = vector<vector<vector<optional<size_t>>>>;

size_t boolean_evaluation(const string& expr, size_t begin, size_t end, bool result, TCache& cache) {
    if (end - begin > 1) {
        if (cache[begin][end][result]) {
            return *cache[begin][end][result];
        }

        size_t count = 0;
        for (size_t i = begin + 1; i < end - 1; i += 2) {
            switch (expr[i]) {
                case '&':
                    if (result) {
                        count += boolean_evaluation(expr, begin, i, true, cache) * boolean_evaluation(expr, i + 1, end, true, cache);
                    } else {
                        count += boolean_evaluation(expr, begin, i, true, cache) * boolean_evaluation(expr, i + 1, end, false, cache);
                        count += boolean_evaluation(expr, begin, i, false, cache) * boolean_evaluation(expr, i + 1, end, true, cache);
                        count += boolean_evaluation(expr, begin, i, false, cache) * boolean_evaluation(expr, i + 1, end, false, cache);
                    }
                    break;
                case '|':
                    if (result) {
                        count += boolean_evaluation(expr, begin, i, true, cache) * boolean_evaluation(expr, i + 1, end, true, cache);
                        count += boolean_evaluation(expr, begin, i, true, cache) * boolean_evaluation(expr, i + 1, end, false, cache);
                        count += boolean_evaluation(expr, begin, i, false, cache) * boolean_evaluation(expr, i + 1, end, true, cache);
                    } else {
                        count += boolean_evaluation(expr, begin, i, false, cache) * boolean_evaluation(expr, i + 1, end, false, cache);
                    }
                    break;
                case '^':
                    if (result) {
                        count += boolean_evaluation(expr, begin, i, true, cache) * boolean_evaluation(expr, i + 1, end, false, cache);
                        count += boolean_evaluation(expr, begin, i, false, cache) * boolean_evaluation(expr, i + 1, end, true, cache);
                    } else {
                        count += boolean_evaluation(expr, begin, i, true, cache) * boolean_evaluation(expr, i + 1, end, true, cache);
                        count += boolean_evaluation(expr, begin, i, false, cache) * boolean_evaluation(expr, i + 1, end, false, cache);
                    }
                    break;
            }
        }
        cache[begin][end][result] = count;
        return count;
    } else {
        return expr.at(begin) == (result ? '1' : '0');
    }
}

size_t boolean_evaluation(const string& expr, bool result) {
    TCache cache(expr.size() + 1);
    for (auto& x : cache) {
        x.resize(expr.size() + 1);
        for (auto& y : x) {
            y.resize(2);
        }
    }
    return boolean_evaluation(expr, 0, expr.size(), result, cache);
}

int main() {
    const string expr1 = "1^0|0|1";
    cerr << boolean_evaluation(expr1, false) << endl;

    const string expr2 = "0&0&0&1^1|0";
    cerr << boolean_evaluation(expr2, true) << endl;
}
