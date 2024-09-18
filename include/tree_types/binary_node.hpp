#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "array_node.hpp"

namespace vpr {

template <typename T, typename U>
using BinaryNode = ArrayNode<T, U, 2>;


template <typename T>
class BinaryTree;

template <typename T>
class BinaryTree : public vpr::Tree<T, std::array<BinaryTree<T>, 2>> {
    public:
        using vpr::Tree<T, std::array<BinaryTree<T>, 2>>::Tree;

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
