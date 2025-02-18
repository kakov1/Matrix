#include "matrix.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

using hwm::Matrix;

void validate_correct_size(int size) {
  if (size <= 0) {
    throw std::runtime_error("Incorrect size.");
  }
}

void validate_correct_matrix(size_t size1, size_t size2) {
  if (size1 > size2) {
    throw std::runtime_error("Incorrect matrix for given size.");
  }
}

void validate_cin_good() {
  if (!std::cin.good()) {
    throw std::runtime_error("Input error.");
  }
}

int main() {
  int size;
  double buf;
  std::vector<double> numbers;

  std::cin >> size;

  validate_cin_good();
  validate_correct_size(size);

  for (int i = 0; i < size * size; i++) {
    std::cin >> buf;
    validate_cin_good();
    numbers.push_back(buf);
  }

  validate_correct_matrix(size * size, numbers.size());

  Matrix<double> matrix{size, size, numbers.begin(), numbers.end()};

  std::cout << std::setprecision(25) << matrix.determinant() << std::endl;
}