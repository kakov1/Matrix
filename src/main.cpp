#include "matrix.hpp"
#include <vector>
#include <iostream>

int main() {
    int size;
    double buf;
    std::vector<double> numbers;

    std::cin >> size;

    for (int i = 0; i < size * size; i++) {
        std::cin >> buf;
        numbers.push_back(buf);
    }

    Matrix::Matrix<double> matrix{size, size, numbers.begin(), numbers.end()};

    std::cout << matrix.determinant() << std::endl;
}