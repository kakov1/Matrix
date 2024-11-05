#pragma once

#include "real_numbers.hpp"
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
            ResourceManager<T> numbers_;

            void set_values(int rows, int cols) {
                rows_ = rows;
                cols_ = cols;
                size_ = rows * cols;
            }

            void is_quadratic() const {
                if (rows_ != cols_) {
                    throw std::runtime_error(
                        "Determinant is defined only for square matrix.");
                }
            }

        public:
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

            Matrix(const Matrix& other) {
                numbers_ = other.numbers_;
                set_values(other.rows_, other.cols_);
            }

            Matrix(Matrix&& other) {
                std::swap(numbers_, other.numbers_);
                std::swap(rows_, other.rows_);
                std::swap(cols_, other.cols_);
                std::swap(size_, other.size_);
            }

            Matrix& operator=(const Matrix& other) {
                if (this == &other) {
                    return *this;
                }

                numbers_ = other.numbers_;
                set_values(other.rows_, other.cols_);

                return *this;
            }

            Matrix& operator=(Matrix&& other) {
                if (this == &other) {
                    return *this;
                }

                std::swap(numbers_, other.numbers_);
                std::swap(rows_, other.rows_);
                std::swap(cols_, other.cols_);
                std::swap(size_, other.size_);

                return *this;
            }

            ~Matrix() = default;

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
                for (int i = 0; i < cols_; i++) {
                    numbers_[string * cols_ + i] *= number;
                }
            }

            Matrix<T> triangular_view_gauss() const {
                is_quadratic();

                Matrix<T> copy(*this);

                for (int i = 0; i < rows_; i++) {

                    for (int j = i + 1; j < rows_; j++) {

                        if (is_zero(copy[i * cols_ + i])) {

                            int swap_num = i + 1;
                            while (copy[swap_num * cols_ + i] == 0) {
                                if (swap_num == rows_) {
                                    return Matrix<T>(rows_, cols_, 0);
                                }

                                swap_num++;
                            }

                            copy.swap_strings(i, swap_num);
                            copy.mul_row(swap_num, -1);
                        }

                        T coeff = copy[j * cols_ + i] / copy[i * cols_ + i];

                        for (int k = 0; k < cols_; k++) {
                            copy[j * cols_ + k] -= copy[i * cols_ + k] * coeff;
                        }
                    }
                }

                return copy;
            }

            T determinant() const {
                is_quadratic();

                Matrix<T> triangle_view = triangular_view_gauss();

                T result = triangle_view.trace();

                if (is_int(result)) {
                    return std::round(result);
                }

                return result;
            }

            bool operator==(const Matrix& other) const {
                if (rows_ != other.rows_ || cols_ != other.cols_) {
                    return false;
                }

                for (int i = 0; i < rows_; i++) {
                    for (int j = 0; j < cols_; j++) {
                        if (!equal_floats(numbers_[i * cols_ + j],
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
}
