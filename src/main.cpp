#include "matrix.hpp"
#include <vector>
#include <iostream>
#include <iomanip>

int main() {
    int size;
    long double buf;
    std::vector<long double> numbers;

    std::cin >> size;

    for (int i = 0; i < size * size; i++) {
        std::cin >> buf;
        numbers.push_back(buf);
    }

    Matrix::Matrix<long double> matrix{size, size, numbers.begin(), numbers.end()};

    std::cout << std::setprecision(25) << matrix.determinant() << std::endl;
}