#include <iostream>
#include <algorithm>

template <class T>
bool max_binary_matrix(T* m, size_t n, size_t k) {
    for (size_t i = 0; i < n; i++)
        for (size_t j = i; j < n; j++) {
            size_t val = 0;
            if (i == j) {
                if (k > 0) {
                    val = 1;
                    k--;
                }
                m[i * n + j] = val;
            } else {
                if (k > 1) {
                    val = 1;
                    k -= 2;
                }
                m[i * n + j] = val;
                m[j * n + i] = val;
            }
        }
    return k == 0;
}

int main() {
    size_t n, k;
    while (std::cin >> n >> k) {
        unsigned char m[n * n];
        if (max_binary_matrix(m, n, k)) {
            for (size_t i = 0; i < n; i++)
                for (size_t j = 0; j < n; j++) {
                    std::cout << static_cast<unsigned int>(m[i * n + j]);
                    if (j == n - 1)
                        std::cout << std::endl;
                    else
                        std::cout << ' ';
                }
        } else {
            std::cout << -1 << std::endl;
        }
    }
}
