#include "matrix.h"

template <class T>
void paint_fill(TMatrix<T>& matrix, size_t i, size_t j, T original_value, T target_value) {
    if (matrix.at(i, j) == original_value) {
        matrix.at(i, j) = target_value;
        if (i > 0) {
            paint_fill(matrix, i - 1, j, original_value, target_value);
        }
        if (i + 1 < matrix.height()) {
            paint_fill(matrix, i + 1, j, original_value, target_value);
        }
        if (j > 0) {
            paint_fill(matrix, i, j - 1, original_value, target_value);
        }
        if (j + 1 < matrix.width()) {
            paint_fill(matrix, i, j + 1, original_value, target_value);
        }
    } 
}

template <class T>
void paint_fill(TMatrix<T>& matrix, size_t i, size_t j, T target_value) {
    paint_fill(matrix, i, j, matrix.at(i, j), target_value);
}

int main(int argc, const char* argv[]) {
    std::mt19937_64::result_type seed;
    std::random_device rd;
    if (argc > 1) {
        seed = std::stoul(argv[1]);
    }

    TMatrix<int> matrix = random_matrix<int>(10, 5, 0, 1, seed);
    std::cerr << matrix;

    size_t i;
    std::cin >> i;
    size_t j;
    std::cin >> j;
    int target_value;
    std::cin >> target_value;

    paint_fill(matrix, i, j, target_value);
    std::cerr << matrix;
}
