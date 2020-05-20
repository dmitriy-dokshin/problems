#pragma once

#include <iostream>
#include <random>
#include <string>
#include <vector>

template <class T>
class TMatrix {
public:
    TMatrix(const size_t w, const size_t h)
        : W_(w)
        , H_(h)
        , Data_(w * h)
    {
    }

    const T& at(size_t i, size_t j) const {
        return const_cast<TMatrix*>(this)->at(i, j);
    }

    T& at(size_t i, size_t j) {
        return Data_.at(i * W_ + j);
    }

    size_t width() const {
        return W_;
    }

    size_t height() const {
        return H_;
    }

    bool empty() const {
        return W_ == 0 || H_ == 0;
    }

private:
    size_t W_ = 0;
    size_t H_ = 0;
    std::vector<T> Data_;
};

template <class T>
TMatrix<T> random_matrix(size_t w, size_t h, T min_value, T max_value, std::mt19937_64::result_type seed) {
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<T> dist(min_value, max_value);

    TMatrix<T> matrix(w, h);
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            matrix.at(i, j) = dist(gen);
        }
    }
    return matrix;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const TMatrix<T>& matrix) {
    static const std::string VALUE_SEPARATOR = " ";
    if (!matrix.empty()) {
        out << "\\" << VALUE_SEPARATOR << 0;
        for (size_t j = 1; j < matrix.width(); j++) {
            out << VALUE_SEPARATOR << j;
        }
        out << std::endl;
        for (size_t i = 0; i < matrix.height(); i++) {
            out << i << VALUE_SEPARATOR << matrix.at(i, 0);
            for (size_t j = 1; j < matrix.width(); j++) {
                out << VALUE_SEPARATOR << matrix.at(i, j);
            }
            out << std::endl;
        }
    }
    return out;
}