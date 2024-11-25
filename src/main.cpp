#include "matrix.hpp"
#include <vector>
#include <iostream>
#include <iomanip>

void is_correct_size(int size) {
    if (size <= 0) {
        throw std::runtime_error("Incorrect size.");
    }
}

void is_correct_matrix(size_t size1, size_t size2) {
    if (size1 > size2) {
        throw std::runtime_error("Incorrect matrix for given size.");
    }
}

void is_cin_good() {
    if (!std::cin.good()) {
        throw std::runtime_error("Input error.");
    }
}

int main() {
    int size;
    double buf;
    std::vector<double> numbers;

    std::cin >> size;

    is_cin_good();
    is_correct_size(size);

    for (int i = 0; i < size * size; i++) {
        std::cin >> buf;
        is_cin_good();
        numbers.push_back(buf);
    }
    
    is_correct_matrix(size * size, numbers.size());

    Matrix::Matrix<double> matrix{size, size, numbers.begin(), numbers.end()};

    std::cout << std::setprecision(25) << matrix.determinant() << std::endl;
}