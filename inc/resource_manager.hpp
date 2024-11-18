#pragma once

#include <utility>
#include <iostream>

namespace Matrix {
    template <typename T>
    class ResourceManager {
        private:
            T* ptr_ = nullptr;
            int size_ = 0;

            template <typename U>
            void copy_data(const ResourceManager<U>& other) {
                size_ = other.get_size();
                ptr_ = new T[size_];
                U* other_ptr = other.get_ptr();

                for (int i = 0; i < size_; i++) {
                    ptr_[i] = static_cast<T>(other_ptr[i]);
                }
            }

            void swap(ResourceManager& other) noexcept {
                std::swap(ptr_, other.ptr_);
                std::swap(size_, other.size_);
            }

        public:
            ResourceManager() = default;

            ResourceManager(int size) : size_(size) { ptr_ = new T[size_]; }

            ResourceManager(const ResourceManager& other) {
                copy_data<T>(other);
            }

            template <typename U>
            ResourceManager(const ResourceManager<U>& other) {
                copy_data<U>(other);
            }

            ResourceManager(ResourceManager&& other) noexcept {
                std::swap(ptr_, other.ptr_);
                std::swap(size_, other.size_);
            }

            ResourceManager& operator=(const ResourceManager& other) {
                if (this != &other) {
                    ResourceManager<T> tmp{other};
                    tmp.swap(*this);
                }

                return *this;
            }

            template <typename U>
            ResourceManager& operator=(const ResourceManager<U>& other) {
                ResourceManager<T> tmp{other};
                tmp.swap(*this);

                return *this;
            }

            ResourceManager& operator=(ResourceManager&& other) noexcept {
                swap(other);

                return *this;
            }

            ~ResourceManager() { delete[] ptr_; }

            T& operator[](int index) const { return ptr_[index]; }

            int get_size() const { return size_; }

            T* get_ptr() const { return ptr_; }
    };
}