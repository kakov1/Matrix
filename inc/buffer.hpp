#pragma once

#include <utility>
#include <iostream>

namespace hwm {
    template <typename T>
    class MatrixBuf {
        protected:
            T* ptr_ = nullptr;
            std::size_t size_ = 0;

            void swap(MatrixBuf& other) noexcept {
                std::swap(ptr_, other.ptr_);
                std::swap(size_, other.size_);
            }

            MatrixBuf(std::size_t size = 0)
                : ptr_(size == 0 ? nullptr
                                 : static_cast<T*>(::operator new(
                                       sizeof(T) * size,
                                       std::align_val_t(alignof(T))))),
                  size_(size) {}

            MatrixBuf(const MatrixBuf& other) = delete;

            MatrixBuf(MatrixBuf&& other) noexcept { swap(other); }

            MatrixBuf& operator=(const MatrixBuf& other) = delete;

            MatrixBuf& operator=(MatrixBuf&& other) noexcept {
                swap(other);

                return *this;
            }

            ~MatrixBuf() {
                std::destroy(ptr_, ptr_ + size_);
                delete ptr_;
            }
    };
}