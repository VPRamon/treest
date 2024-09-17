#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <utility>
#include <array>

#include "node_interface.hpp"

namespace vpr {

template <typename T>
class BinaryTree : public NodeInterface<
                        std::unique_ptr<std::array<BinaryTree<T>, 2>>, T> {
    using ChildType = std::array<BinaryTree<T>, 2>;
    using ParentType = NodeInterface<std::unique_ptr<ChildType>, T>;

public:

    BinaryTree() : ParentType() {};
    BinaryTree(ChildType children) : ParentType(std::make_unique<ChildType>(children)) {};
    BinaryTree(T value) : ParentType(value) {};

    BinaryTree(const BinaryTree& other)
        : ParentType(other.data_, other.isLeaf() ? std::nullopt : std::optional<std::unique_ptr<ChildType>>(std::make_unique<ChildType>(*other.children_.value()))) {};

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            ParentType::data_ = other.data_;
            ParentType::children_ = std::make_unique<ChildType>(*other.children_.value());
        }
        return *this;
    }


    const BinaryTree& left() const {
        assert(this->children_.has_value() && "Attempting to access left child of a leaf node.");
        return (*this->children_.value())[0];
    }

    BinaryTree& left() {
        assert(this->children_.has_value() && "Attempting to access left child of a leaf node.");
        return (*this->children_.value())[0];
    }

    const BinaryTree& right() const {
        assert(this->children_.has_value() && "Attempting to access right child of a leaf node.");
        return (*this->children_.value())[1];
    }

    BinaryTree& right() {
        assert(this->children_.has_value() && "Attempting to access right child of a leaf node.");
        return (*this->children_.value())[1];
    }
};


} // namespace vpr

#endif // BINARY_TREE_HPP
