#pragma once

#include "real_numbers.hpp"
#include "buffer.hpp"
#include <ostream>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <memory>

namespace hwm {
    template <typename T>
    class Matrix final : private MatrixBuf<T> {
        private:
            using MatrixBuf<T>::ptr_;
            using MatrixBuf<T>::size_;

            class ProxyRow final {
                private:
                    T* str_ptr_;

                public:
                    ProxyRow(T* str_ptr) : str_ptr_(str_ptr) {}

                    T& operator[](std::size_t idx) { return str_ptr_[idx]; }

                    const T& operator[](std::size_t idx) const {
                        return str_ptr_[idx];
                    }
            };

        private:
            std::size_t rows_ = 0, cols_ = 0;

            void set_values(std::size_t rows, std::size_t cols) {
                rows_ = rows;
                cols_ = cols;
            }

            void validate_quadratic() const {
                if (rows_ != cols_) {
                    throw std::runtime_error(
                        "Determinant is defined only for square matrix.");
                }
            }

            void validate_string_in_matrix(int string) const {
                if (string < 0 || string >= rows_) {
                    throw std::out_of_range("String index out of range.");
                }
            }

            void validate_correct_size(int rows, int cols) const {
                if (rows <= 0 || cols <= 0) {
                    throw std::invalid_argument("Incorrect size.");
                }
            }

            template <typename It>
            void validate_correct_it(const It& it, const It& fin) {
                if (it == fin) {
                    throw std::invalid_argument(
                        "Incorrect size for given matrix.");
                }
            }

        public:
            Matrix() = default;

            Matrix(int rows, int cols, T value) : MatrixBuf<T>(rows * cols) {
                validate_correct_size(rows, cols);

                set_values(rows, cols);

                for (std::size_t i = 0; i < rows_; ++i) {
                    for (std::size_t j = 0; j < cols_; ++j) {
                        (*this)[i][j] = value;
                    }
                }
            }

            template <typename It>
            Matrix(int rows, int cols, It start, It fin)
                : MatrixBuf<T>(rows * cols) {

                validate_correct_size(rows, cols);

                set_values(rows, cols);

                for (std::size_t i = 0; i < rows_; i++) {
                    for (std::size_t j = 0; j < cols_; j++) {

                        validate_correct_it(start, fin);

                        (*this)[i][j] = *start;
                        start++;
                    }
                }
            }

            Matrix(const Matrix& other) : MatrixBuf<T>(other.size_) {
                std::uninitialized_copy(other.ptr_, other.ptr_ + other.size_,
                                        ptr_);

                set_values(other.rows_, other.cols_);
            }

            Matrix(Matrix&& other) = default;

            Matrix& operator=(const Matrix& other) {
                Matrix tmp{other};
                std::swap(*this, tmp);

                return *this;
            }

            Matrix& operator=(Matrix&& other) = default;

            static Matrix<T> eye(int size) {
                validate_correct_size(size, size);

                Matrix<T> result{size, size, 0};

                for (std::size_t i = 0; i < size; ++i) {
                    for (std::size_t j = 0; j < size; ++j) {
                        result[i][j] = 1;
                    }
                }

                return result;
            }

            std::size_t get_rows() const { return rows_; }

            std::size_t get_cols() const { return cols_; }

            T trace() const {
                validate_quadratic();

                T result = 1;

                for (std::size_t i = 0; i < rows_; i++) {
                    result *= (*this)[i][i];
                }

                return result;
            }

            void swap_strings(int string1, int string2) {
                validate_string_in_matrix(string1);
                validate_string_in_matrix(string2);

                if (string1 == string2)
                    return;

                for (std::size_t i = 0; i < cols_; ++i) {
                    std::swap((*this)[string1][i], (*this)[string2][i]);
                }
            }

            void mul_row(int string, T number) {
                validate_string_in_matrix(string);

                for (std::size_t i = 0; i < cols_; ++i) {
                    (*this)[string][i] *= number;
                }
            }

            void div_row(int string, T number) {
                validate_string_in_matrix(string);

                for (std::size_t i = 0; i < cols_; ++i) {
                    (*this)[string][i] /= number;
                }
            }

            T determinant() const {
                validate_quadratic();

                if constexpr (std::is_integral_v<T>) {
                    return triangular_view_bareiss(*this);
                }

                return triangular_view_gauss(*this);
            }

            bool is_equal(const Matrix& other) const {
                if (rows_ != other.rows_ || cols_ != other.cols_) {
                    return false;
                }

                for (std::size_t i = 0; i < rows_; ++i) {
                    for (std::size_t j = 0; j < cols_; ++j) {
                        if ((*this)[i][j] != other[i][j]) {
                            return false;
                        }
                    }
                }

                return true;
            }

            ProxyRow operator[](std::size_t idx) const {
                return ProxyRow(ptr_ + idx * cols_);
            }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& stream, const Matrix<T>& matrix) {
        for (std::size_t i = 0, rows = matrix.get_rows(); i < rows; ++i) {
            for (std::size_t j = 0, cols = matrix.get_cols(); j < cols; ++j) {
                stream << matrix[i][j] << " ";
            }

            stream << std::endl;
        }

        return stream;
    }

    template <typename T>
    bool operator==(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
        return matrix1.is_equal(matrix2);
    }

    template <typename T>
    int partial_pivoting(Matrix<T>& mtrx, int col) {
        int pivot = col;

        auto rows = mtrx.get_rows();
        auto cols = mtrx.get_cols();

        for (int i = col + 1; i < rows; ++i) {
            if (is_less(std::fabs(mtrx[pivot][col]),
                        std::fabs(mtrx[i][col]))) {
                pivot = i;
            }
        }

        mtrx.swap_strings(pivot, col);

        if (pivot != col) {
            return -1;
        }

        return 1;
    }

    template <typename T>
    T triangular_view_bareiss(Matrix<T> mtrx) {
        int sign = 1;
        T prev = 1;

        auto rows = mtrx.get_rows();
        auto cols = mtrx.get_cols();

        for (int i = 0; i < rows - 1; ++i) {

            if (mtrx[i][i] == 0) {
                sign *= partial_pivoting(mtrx, i);
                if (mtrx[i][i] == 0) {
                    return 0;
                }
            }

            for (int j = i + 1; j < rows; ++j) {

                for (int k = i + 1; k < rows; ++k) {
                    T numerator = (mtrx[j][k]) * (mtrx[i][i]) -
                                  (mtrx[j][i]) * (mtrx[i][k]);

                    mtrx[j][k] = numerator / prev;
                }

                mtrx[j][i] = 0;
            }

            prev = mtrx[i][i];
        }

        return sign * mtrx[rows - 1][cols - 1];
    }

    template <typename T>
    T triangular_view_gauss(Matrix<T> mtrx) {
        int sign = 1;

        auto rows = mtrx.get_rows();
        auto cols = mtrx.get_cols();

        for (int i = 0; i < rows; i++) {

            sign *= partial_pivoting(mtrx, i);

            if (is_zero(mtrx[i][i])) {
                return 0;
            }

            for (int j = i + 1; j < rows; j++) {

                T coeff = mtrx[j][i] / mtrx[i][i];

                for (int k = 0; k < cols; k++) {
                    mtrx[j][k] -= mtrx[i][k] * coeff;
                }
            }
        }

        return sign * mtrx.trace();
    }
}
