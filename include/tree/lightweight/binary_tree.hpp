#pragma once

#include "binary_tree_node.hpp"
#include "tree_template.hpp"

#include <array>
#include <initializer_list>

template <typename T, size_t MaxSize>
class DynamicArray {
    std::array<T, MaxSize> data_;  // Fixed-size array to hold the elements
    size_t size_ = 0;         // Tracks the current number of elements

public:

    using value_type = T;

    DynamicArray() = default;

    template <typename... Args>
    DynamicArray(Args&&... args) {
        static_assert(sizeof...(args) <= MaxSize, "Number of elements exceeds FixedVector's maximum size");

        // Add each argument to the array
        size_ = sizeof...(args);
        data_ = {std::forward<Args>(args)...};
    }

    template <typename... Args>
    void emplace_back(const Args&&... args) {
        if (size_ >= MaxSize) {
            throw std::out_of_range("Exceeded maximum size");
        }
        data_[size_] = {std::forward<Args>(args)...};
        ++size_;
    }

    void emplace_back(const T& value) {
        if (size_ >= MaxSize) {
            throw std::out_of_range("Exceeded maximum size");
        }
        data_[size_] = value;
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
        if (index >= MaxSize) {
            throw std::out_of_range("Attempt to access an element out of array bounds");
        }
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= MaxSize) {
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
