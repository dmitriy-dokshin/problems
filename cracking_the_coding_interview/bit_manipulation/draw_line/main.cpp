#include <climits>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& print(ostream& out, const T& value) {
    for (size_t i = sizeof(value) * CHAR_BIT; i > 0; i--) {
        T mask = 1;
        mask <<= (i - 1);
        bool bit = value & mask;
        out << bit;
    }
    return out;
}

template <class T>
vector<T> random_screen(size_t width, size_t height, typename mt19937_64::result_type seed) {
    mt19937_64 gen(seed);
    uniform_int_distribution<T> dist;

    size_t size = width / (sizeof(T) * CHAR_BIT) * height;
    vector<T> result;
    result.reserve(size);
    for (size_t i = 0; i < size; i++) {
        result.emplace_back(dist(gen));
    }
    return result;
}

template <class T>
bool get(const vector<T>& screen, size_t width, size_t x, size_t y) {
    size_t size = sizeof(T) * CHAR_BIT;
    if (width % size != 0) {
        throw runtime_error("Invalid width");
    }
    size_t w = width / size;
    if (screen.size() % w != 0) {
        throw runtime_error("Invalid screen size");
    }
    size_t h = screen.size() / w;

    if (x >= width) {
        throw runtime_error("Invalid x: " + to_string(x));
    }
    if (y >= h) {
        throw runtime_error("Invalid y: " + to_string(y));
    }

    size_t i = y * w + x / size;
    T mask = 1 << (size - 1 - x % size);
    bool bit = screen.at(i) & mask;
    return bit;
}

template <class T>
ostream& draw_line(const vector<T>& screen, size_t width, size_t x1, size_t x2, size_t y, ostream& out) {
    for (size_t x = x1; x <= x2; x++) {
        out << get(screen, width, x, y);
    }
    return out;
}

int main(int argc, const char* argv[]) {
    typename mt19937_64::result_type seed;
    if (argc > 1) {
        seed = stoul(argv[1]);
    } else {
        random_device r;
        seed = r();
    }

    size_t width = 16;
    size_t height = 4;
    auto screen = random_screen<unsigned char>(width, height, seed);
    auto w = width / (sizeof(typename decltype(screen)::value_type) * CHAR_BIT);
    for (size_t j = 0; j < height; j++) {
        for (size_t i = 0; i < w; i++) {
            print(cerr, screen.at(j * w + i));
        }
        cerr << endl;
    }

    size_t x1 = 3;
    size_t x2 = 11;
    size_t y = 2;
    draw_line(screen, width, x1, x2, y, cout) << endl;
}
