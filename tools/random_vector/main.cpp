#include <lib/io/io.h>
#include <lib/random/random.h>

int main() {
    std::random_device rd;
    const auto v = TRandom<unsigned int>::random_vector_unique(20, 1, 60, rd());
    print(std::cout, v, "\n");
}
