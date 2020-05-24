#pragma once

#include <iostream>
#include <utility>
#include <vector>

template <class T1, class T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& p) {
    out << "{" << p.first << ", " << p.second << "}";
    return out;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v);

template <class T>
std::ostream& print(std::ostream& out, const std::vector<T>& v, const char* delim = " ") {
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << delim << v.at(i);
        }
    }
    return out;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    return print(out, v);
}
