#include <utility>

namespace Matrix {
    template <typename T>
    class ResourceManager {
        private:
            T* ptr_ = nullptr;
            int size_ = 0;

        public:
            ResourceManager() = default;

            ResourceManager(int size) : size_(size) { ptr_ = new T[size_]; }

            ResourceManager(const ResourceManager& other) {
                ptr_ = new T[other.size_];
                size_ = other.size_;
            }

            ResourceManager(ResourceManager&& other) noexcept {
                std::swap(ptr_, other.ptr_);
                std::swap(size_, other.size_);
            }

            ResourceManager& operator=(const ResourceManager& other) {
                if (this == &other) {
                    return *this;
                }

                ptr_ = new T[other.size_];
                size_ = other.size_;

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

            ~ResourceManager() { delete [] ptr_; }

            T& operator[](int index) const { return ptr_[index]; }
    };
}