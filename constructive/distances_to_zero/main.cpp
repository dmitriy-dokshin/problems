#include <iostream>
#include <algorithm>

int main() {
    size_t n;
    std::cin >> n;
    int a[n];
    int res[n];
    int zero_pos = -1;
    for (size_t i = 0; i < n; i++) {
        int val;
        std::cin >> val;
        a[i] = val;
        if (val == 0)
            zero_pos = i;
        res[i] = zero_pos >= 0 ? i - zero_pos : -1;
    }
    zero_pos = -1;
    size_t i = n - 1;
    do {
        int val = a[i];
        if (val == 0)
            zero_pos = i;
        if (zero_pos >= 0) {
            int x = zero_pos - static_cast<int>(i);
            res[i] = res[i] >= 0 ? std::min(res[i], x) : x;
        }
    } while (i-- > 0);
    for (size_t i = 0; i < n; i++) {
        std::cout << res[i];
        if (i == n - 1) {
            std::cout << std::endl;
        } else {
            std::cout << ' ';
        }
    }
}
