#include "matrix.hpp"
#include <vector>
#include <iostream>

int main() {
    int size, buf;
    std::vector<int> numbers;

    std::cin >> size;

    for (int i = 0; i < size * size; i++) {
        std::cin >> buf;
        numbers.push_back(buf);
    }

    Matrix::Matrix<double> matrix{size, size, numbers.begin(), numbers.end()};

    Matrix::Matrix<double> matrix1 = matrix.triangular_view_gauss();

    std::cout << matrix;
    std::cout << matrix1;
}