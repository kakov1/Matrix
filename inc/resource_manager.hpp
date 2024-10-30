#pragma once

#include <utility>
#include <iostream>

namespace Matrix {
    template <typename T>
    class ResourceManager {
        private:
            T* ptr_ = nullptr;
            int size_ = 0;

            void copy_data(const ResourceManager& other) {
                ptr_ = new T[other.size_];
                size_ = other.size_;

                for (int i = 0; i < size_; i++) {
                    ptr_[i] = other.ptr_[i];
                }
            }

        public:
            ResourceManager() = default;

            ResourceManager(int size) : size_(size) { ptr_ = new T[size_]; }

            ResourceManager(const ResourceManager& other) {
                copy_data(other);
            }

            ResourceManager(ResourceManager&& other) noexcept {
                std::swap(ptr_, other.ptr_);
                std::swap(size_, other.size_);
            }

            ResourceManager& operator=(const ResourceManager& other) {
                if (this == &other) {
                    return *this;
                }

                copy_data(other);

                return *this;
            }

            ResourceManager& operator=(ResourceManager&& other) noexcept {
                if (this == &other) {
                    return *this;
                }

                std::swap(ptr_, other.ptr_);
                std::swap(size_, other.size_);

                return *this;
            }

            ~ResourceManager() { delete[] ptr_; }

            T& operator[](int index) const { return ptr_[index]; }
    };
}