#pragma once

#include "real_numbers.hpp"
#include "resource_manager.hpp"
#include <vector>
#include <ostream>
#include <istream>
#include <iostream>
#include <stdexcept>
#include <cassert>

namespace Matrix {
    template <typename T>
    class Matrix {
        private:
            int rows_ = 0, cols_ = 0, size_ = 0;
            ResourceManager<T> numbers_;

            void set_values(int rows, int cols) {
                rows_ = rows;
                cols_ = cols;
                size_ = rows * cols;
            }

            int partial_pivoting(Matrix<T>& copy, int col) const {
                int pivot = col;

                for (int i = col + 1; i < rows_; ++i) {
                    if (is_less(std::fabs(copy[pivot * rows_ + col]),
                                std::fabs(copy[i * rows_ + col]))) {
                        pivot = i;
                    }
                }

                copy.swap_strings(pivot, col);

                if (pivot != col) {
                    return -1;
                }

                return 1;
            }

            T triangular_view_bareiss() const {
                Matrix<T> copy{*this};
                int sign = 1;
                T prev = 1;

                for (int i = 0; i < rows_ - 1; ++i) {

                    if (is_zero(copy[i * cols_ + i])) {
                        sign *= partial_pivoting(copy, i);
                        if (is_zero(copy[i * cols_ + i])) {
                            return 0;
                        }
                    }

                    for (int j = i + 1; j < rows_; ++j) {

                        for (int k = i + 1; k < rows_; ++k) {
                            T numerator =
                                (copy[j * cols_ + k]) * (copy[i * cols_ + i]) -
                                (copy[j * cols_ + i]) * (copy[i * cols_ + k]);

                            copy[j * cols_ + k] = numerator / prev;
                        }

                        copy[j * cols_ + i] = 0;
                    }

                    prev = copy[i * cols_ + i];
                }

                return sign * copy[rows_ * rows_ - 1];
            }

            T triangular_view_gauss() const {
                Matrix<T> copy{*this};
                int sign = 1;

                for (int i = 0; i < rows_; i++) {

                    sign *= partial_pivoting(copy, i);

                    if (is_zero(copy[i * rows_ + i])) {
                        return 0;
                    }

                    for (int j = i + 1; j < rows_; j++) {

                        T coeff = copy[j * cols_ + i] / copy[i * cols_ + i];

                        for (int k = 0; k < cols_; k++) {
                            copy[j * cols_ + k] -= copy[i * cols_ + k] * coeff;
                        }
                    }
                }

                return sign * copy.trace();
            }

            void is_quadratic() const {
                if (rows_ != cols_) {
                    throw std::runtime_error(
                        "Determinant is defined only for square matrix.");
                }
            }

            void is_string_in_matrix(int string) const {
                if (string < 0 || string >= rows_) {
                    throw std::out_of_range("String index out of range.");
                }
            }

        public:
            Matrix() = default;

            Matrix(int rows, int cols, T value) {
                set_values(rows, cols);
                numbers_ = ResourceManager<T>{size_};

                for (int i = 0; i < size_; i++) {
                    numbers_[i] = value;
                }
            }

            template <typename It>
            Matrix(int rows, int cols, It start, It final) {
                set_values(rows, cols);
                numbers_ = ResourceManager<T>{size_};

                for (int i = 0; i < size_; i++) {
                    numbers_[i] = *start;
                    start++;
                }
            }

            template <typename U>
            Matrix(const Matrix<U>& other) {
                numbers_ = other.get_numbers();
                set_values(other.get_rows(), other.get_cols());
            }

            static Matrix<T> eye(int size) {
                Matrix<T> result{size, size, 0};

                for (int i = 0; i < size * size; i += (size + 1)) {
                    result[i] = 1;
                }

                return result;
            }

            int get_rows() const { return rows_; }

            int get_cols() const { return cols_; }

            int get_size() const { return size_; }

            const ResourceManager<T>& get_numbers() const { return numbers_; }

            T trace() const {
                is_quadratic();

                T result = 1;

                for (int i = 0; i < rows_; i++) {
                    result *= numbers_[i * rows_ + i];
                }

                return result;
            }

            void swap_strings(int string1, int string2) {
                is_string_in_matrix(string1);
                is_string_in_matrix(string2);

                if (string1 == string2)
                    return;

                T copy[cols_];

                for (int i = 0; i < cols_; i++) {
                    copy[i] = numbers_[string1 * rows_ + i];
                    numbers_[string1 * rows_ + i] =
                        numbers_[string2 * rows_ + i];
                }

                for (int i = 0; i < cols_; i++) {
                    numbers_[string2 * rows_ + i] = copy[i];
                }
            }

            void mul_row(int string, T number) {
                is_string_in_matrix(string);

                for (int i = 0; i < cols_; i++) {
                    numbers_[string * cols_ + i] *= number;
                }
            }

            void div_row(int string, T number) {
                is_string_in_matrix(string);

                for (int i = 0; i < cols_; i++) {
                    numbers_[string * cols_ + i] /= number;
                }
            }

            T determinant() const {
                is_quadratic();

                if (std::is_integral_v<T>) {
                    return triangular_view_bareiss();
                }

                return triangular_view_gauss();
            }

            bool is_equal(const Matrix& other) const {
                if (rows_ != other.rows_ || cols_ != other.cols_) {
                    return false;
                }

                for (int i = 0; i < rows_; i++) {
                    for (int j = 0; j < cols_; j++) {
                        if (!is_equal_floats(numbers_[i * cols_ + j],
                                             other.numbers_[i * cols_ + j])) {
                            return false;
                        }
                    }
                }

                return true;
            }

            T& operator[](int index) const { return numbers_[index]; }
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

    template <typename T>
    bool operator==(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
        return matrix1.is_equal(matrix2);
    }
}
