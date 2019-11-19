#include <iostream>
#include <queue>
#include <random>
#include <vector>

bool route_exists(const std::vector<std::vector<bool>>& m, size_t source, size_t target) {
    std::vector<bool> visited;
    visited.resize(m.size());
    std::queue<size_t> to_visit;
    to_visit.push(source);
    while (!to_visit.empty() && !visited[target]) {
        size_t cur = to_visit.front();
        visited[cur] = true;
        for (size_t i = 0; i < m.size(); i++) {
            if (m[cur][i] && !visited[i]) {
                to_visit.push(i);
            }
        }
        to_visit.pop();
    }
    return visited[target];
}

std::vector<std::vector<bool>> prepare_input(size_t n) {
    std::random_device device;
    std::default_random_engine engine(device());
    std::uniform_int_distribution<short> rand(0, 1);
    std::vector<std::vector<bool>> m;
    m.resize(n);
    for (size_t i = 0; i < n; i++) {
        m[i].resize(n);
        for (size_t j = 0; j < n; j++) {
            m[i][j] = rand(engine);
        }
    }
    return m;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    if (!v.empty()) {
        out << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            out << " " << v[i];
        }
    }
    return out;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>>& m) {
    if (!m.empty()) {
        out << m[0];
        for (size_t i = 1; i < m.size(); i++) {
            out << std::endl << m[i];
        }
    }
    return out;
}

int main() {
    size_t n = 5;
    size_t source = 0;
    size_t target = n - 1;
    auto m = prepare_input(n);
    std::cerr << m << std::endl;
    bool exists = route_exists(m, source, target);
    std::cerr << "Route between " << source << " and " << target << (exists ? " exists" : " does not exist") << std::endl;
}
