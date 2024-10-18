#pragma once

#include "binary_tree_node.hpp"
#include "tree_template.hpp"

#include <array>
#include <initializer_list>

template <typename T, size_t MaxSize>
class DynamicArray {
    std::array<T, MaxSize> data_;  // Fixed-size array to hold the elements
    size_t size_ = 0;              // Tracks the current number of elements

public:

    using value_type = T;
    using iterator = typename std::array<T, MaxSize>::iterator;
    using const_iterator = typename std::array<T, MaxSize>::const_iterator;
    using reverse_iterator = typename std::array<T, MaxSize>::reverse_iterator;
    using const_reverse_iterator = typename std::array<T, MaxSize>::const_reverse_iterator;

    DynamicArray() = default;

    template <typename... Args>
    DynamicArray(Args&&... args) {
        static_assert(sizeof...(args) <= MaxSize, "Number of elements exceeds FixedVector's maximum size");
        size_ = sizeof...(args);
        data_ = {std::forward<Args>(args)...};
    }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ >= MaxSize) {
            throw std::out_of_range("Exceeded maximum size");
        }
        data_[size_] = T(std::forward<Args>(args)...);
        ++size_;
    }

    void push_back(const T& value) {
        if (size_ >= MaxSize) {
            throw std::out_of_range("Exceeded maximum size");
        }
        data_[size_] = value;
        ++size_;
    }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Attempt to access an element out of array bounds");
        }
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Attempt to access an element out of array bounds");
        }
        return data_[index];
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Get the current size
    size_t size() const { return size_; }

    // Get the maximum capacity
    constexpr size_t capacity() const { return MaxSize; }

    // Clear the container
    void clear() { size_ = 0; }

    // Check if array contains any element
    bool empty() const { return size_ == 0; }

    T& front() { return at(0); }
    const T& front() const { return at(0); }
    T& back() { return at(size_-1); }
    const T& back() const { return at(size_-1); }

    // Corrected iterator functions
    iterator begin() noexcept { return data_.begin(); }
    iterator end() noexcept { return data_.begin() + size_; }
    const_iterator begin() const noexcept { return data_.begin(); }
    const_iterator end() const noexcept { return data_.begin() + size_; }
    const_iterator cbegin() const noexcept { return data_.cbegin(); }
    const_iterator cend() const noexcept { return data_.cbegin() + size_; }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }
};



namespace vpr {
namespace lightweight {

template <typename Data>
using BinaryTree = templates::Tree<
    std::vector<                    //< Tree Container Type
        binary_tree::Node<                 //< Node Type
            Data,                   //< Node Data
            DynamicArray<size_t, 2> //< Edges
        >
    >
>;


} // namespace lightweight
} // namespace vpr
