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
                std::swap(rows_, other.rows);
                std::swap(cols_, other.cols);
                std::swap(size_, other.size_);

                return *this;
            }

            int get_rows() const { return rows_; }

            int get_cols() const { return cols_; }

            int get_size() const { return size_; }

            const ResourceManager<T>& get_numbers() const { return numbers_; }

            T trace() const {
                if (rows_ != cols_) {
                    throw std::runtime_error(
                        "Trace is defined only for square matrix.");
                }

                T result = 1;

                for (int i = 0; i < rows_; i++) {
                    result *= numbers_[i * rows_ + i];
                }

                return result;
            }

            void multiple_number_string(T number, int string_number) {
                for (int i = 0; i < cols_; i++) {
                    numbers_[string_number * cols_ + i] *= number;
                }
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

            Matrix triangular_view_gauss() const {
                Matrix copy = *this;

                for (int i = 0; i < rows_; i++) {

                    for (int j = i + 1; j < rows_; j++) {

                        while (copy[i * cols_ + i] == 0) {
                            if (i != rows_)
                                copy.swap_strings(i, i + 1);
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
                if (rows_ != cols_) {
                    throw std::runtime_error(
                        "Trace is defined only for square matrix.");
                }

                Matrix triangle_view = triangular_view_gauss();

                return triangle_view.trace();
            }

            bool operator==(const Matrix& other) const {
                if (rows_ != other.rows_ || cols_ != other.cols_) {
                    return false;
                }

                for (int i = 0; i < rows_; i++) {
                    for (int j = 0; j < cols_; j++) {
                        if (numbers_[i * cols_ + j] !=
                            other.numbers_[i * cols_ + j]) {
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
