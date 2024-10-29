#include "resource_manager.hpp"
#include <vector>
#include <ostream>
#include <istream>
#include <iostream>
#include <stdexcept>

namespace Matrix {
    template <typename T>
    class Matrix {
        private:
            int rows_ = 0, cols_ = 0, size_ = 0;
            ResourceManager<T> numbers;

            void set_values(int rows, int cols) {
                rows_ = rows;
                cols_ = cols;
                size_ = rows * cols;
                numbers = ResourceManager<T>{size_};
            }

        public:
            Matrix(int rows, int cols, T value) {
                set_values(rows, cols);
                for (int i = 0; i < size_; i++) {
                    numbers[i] = value;
                }
            }

            template <typename It>
            Matrix(int rows, int cols, It start, It final) {
                set_values(rows, cols);
                for (int i = 0; i < size_; i++) {
                    numbers[i] = *start;
                    start++;
                }
            }

            int get_rows() const { return rows_; }

            int get_cols() const { return cols_; }

            int get_size() const { return size_; }

            const ResourceManager<T>& get_numbers() const { return numbers; }

            T trace() const {
                if (rows_ != cols_) {
                    throw std::runtime_error(
                        "Trace is defined only for square matrix.");
                }

                T result = 1;

                for (int i = 0; i < rows_; i++) {
                    result *= numbers[i * rows_ + i];
                }

                return result;
            }

            Matrix triangular_view_gauss() const {
                Matrix copy = *this;

                for (int i = 0; i < rows_; i++) {

                    for (int j = i + 1; j < rows_; j++) {

                        T coeff = copy[i * cols_ + j] / copy[i * cols_ + i];

                        for (int k = 0; k < cols_; k++) {
                            copy[j * cols_ + k] -= copy[i * cols_ + k] * coeff; 
                        }
                    }
                }

                return copy;
            }

            T determinant() const {}

            bool operator==(const Matrix& other) const {
                if (rows_ != other.rows_ || cols_ != other.cols_) {
                    return false;
                }

                for (int i = 0; i < rows_; i++) {
                    for (int j = 0; j < cols_; j++) {
                        if (numbers[i * cols_ + j] !=
                            other.numbers[i * cols_ + j]) {
                            return false;
                        }
                    }
                }

                return true;
            }

            T& operator[](int index) const { return numbers[index]; }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& stream, const Matrix<T>& matrix) {
        for (int i = 0; i < matrix.get_rows(); i++) {
            for (int j = 0; j < matrix.get_cols(); j++) {
                stream << matrix[i * matrix.get_cols() + j] << " ";
            }

            stream << std::endl;
        }

        return stream;
    }
}
