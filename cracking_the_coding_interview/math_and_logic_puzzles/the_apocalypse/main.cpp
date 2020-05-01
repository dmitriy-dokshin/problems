#include <iostream>
#include <random>

using namespace std;

double sum(size_t n) {
    double result = 0;
    for (double i = 1; i <= n; i++) {
        result += pow(2, -i);
    }
    return result;
}

int main() {
    random_device rd;

    size_t n = 1000000;
    size_t boys = 0;
    size_t girls = 0;
    for (size_t i = 0; i < n; i++) {
        mt19937_64 gen(rd());
        uniform_real_distribution<float> dist;
        while (dist(gen) < 0.5) {
            boys++;
        }
        girls++;
    }

    float total_pct = static_cast<float>(boys + girls) / 100;
    cout << "boys\t" << (boys / total_pct) << endl;
    cout << "girls\t" << (girls / total_pct) << endl;
    cerr << sum(100) << endl;
}
