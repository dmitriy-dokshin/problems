#include <algorithm>
#include <iostream>
#include <random>
#include <type_traits>
#include <vector>

template <class T, class TGen, class TDist>
std::vector<T> random_vector_impl(
    const size_t size, const T min_val, const T max_val, const std::mt19937_64::result_type seed) {
    TGen gen(seed);
    TDist dist(min_val, max_val);
    std::vector<T> result;
    result.reserve(size);
    while (result.size() < size) {
        result.emplace_back(dist(gen));
    }
    return result;
}

template <class T, class = void>
class TRandom {
};

template <class T>
class TRandom<T, std::enable_if_t<std::is_integral_v<T>>> {
public:
    static std::vector<T> random_vector(const size_t size, const T min_val, const T max_val, const std::mt19937_64::result_type seed) {
        return ::random_vector_impl<T, std::mt19937_64, std::uniform_int_distribution<T>>(size, min_val, max_val, seed);
    }

    static std::vector<T> random_vector_unique(const size_t size, const T min_val, const T max_val, const std::mt19937_64::result_type seed) {
        std::vector<T> result;
        result.reserve(max_val - min_val + 1);
        for (T x = min_val; x <= max_val; x++) {
            result.emplace_back(x);
        }
        std::mt19937_64 shuffle_gen(seed);
        std::shuffle(result.begin(), result.end(), shuffle_gen);
        result.resize(size);
        return result;
    }
};

template <class T>
class TRandom<T, std::enable_if_t<std::is_floating_point_v<T>>> {
public:
    static std::vector<T> random_vector(const size_t size, const T min_val, const T max_val, const std::mt19937_64::result_type seed) {
        return ::random_vector_impl<T, std::mt19937_64, std::uniform_real_distribution<T>>(size, min_val, max_val, seed);
    }
};
