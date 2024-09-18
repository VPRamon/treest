#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <utility>
#include <array>

#include "node_interface.hpp"

namespace vpr {


template <typename ChildType, typename Type>
class BinaryTree : public vpr::NodeInterface<std::unique_ptr<std::array<ChildType, 2>>, Type> {
    using ChildrenType = std::array<ChildType, 2>;
    using ParentType = NodeInterface<std::unique_ptr<ChildrenType>, Type>;

public:

    BinaryTree() : ParentType() {};
    BinaryTree(ChildrenType children) : ParentType(std::make_unique<ChildrenType>(children)) {};
    BinaryTree(Type value, ChildrenType children) : ParentType(value, std::make_unique<ChildrenType>(children)) {};
    BinaryTree(Type value) : ParentType(value) {};

    BinaryTree(const BinaryTree& other)
        : ParentType(other.data_, other.isLeaf() ? std::nullopt 
                                                : std::optional<std::unique_ptr<ChildrenType>>(
                                                    std::make_unique<ChildrenType>(*other.children_.value())
                                                )
                ) {};

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

template <typename Type> class SimpleBinaryTree;

template <typename Type>
class SimpleBinaryTree : public BinaryTree<SimpleBinaryTree<Type>, Type> {
public:

    //using BinaryTree<SimpleBinaryTree<Type>, Type>::BinaryTree;
    using ParentType = BinaryTree<SimpleBinaryTree<Type>, Type>;

    SimpleBinaryTree() : ParentType() {};
    //SimpleBinaryTree(SimpleBinaryTree<Type> children) : ParentType(children) {};
    SimpleBinaryTree(Type value, SimpleBinaryTree<Type> children) : ParentType(value, children) {};
    SimpleBinaryTree(Type value) : ParentType(value) {};
    SimpleBinaryTree(const SimpleBinaryTree& other) : ParentType(other) {};
    SimpleBinaryTree(const std::array<SimpleBinaryTree, 2>& other) : ParentType(other) {};

};

} // namespace vpr

#endif // BINARY_TREE_HPP
