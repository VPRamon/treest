#ifndef CONTAINER_NODE_HPP
#define CONTAINER_NODE_HPP

#include "node_interface.hpp"

namespace vpr {


template <typename T, typename U>
class Tree : public vpr::NodeInterface<std::unique_ptr<U>, T> {

    using ParentType = vpr::NodeInterface<std::unique_ptr<U>, T>;

public:
    Tree() : ParentType() {}
    Tree(T value) : ParentType(std::move(value)) {}

    Tree(U children)
        : ParentType(std::make_unique<U>(std::move(children))) {}

    Tree(T value, U children)
        : ParentType(std::move(value), std::make_unique<U>(std::move(children))) {}


    Tree(const Tree& other)
        : ParentType(other.data_, other.children_ ? std::make_unique<U>(*other.children_) : nullptr) {}


    Tree& operator=(const Tree& other) {
        if (this != &other) {
            ParentType::data_ = other.data_;
            ParentType::children_ = other.children_ ? std::make_unique<U>(*other.children_) : nullptr;
        }
        return *this;
    }

    // Move constructor
    Tree(Tree&& other) noexcept
        : ParentType(std::move(other.data_), std::move(other.children_)) {}

    // Move assignment operator
    Tree& operator=(Tree&& other) noexcept {
        if (this != &other) {
            ParentType::data_ = std::move(other.data_);
            ParentType::children_ = std::move(other.children_);
        }
        return *this;
    }

};

}

#endif
