#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "array_node.hpp"

namespace vpr {

template <typename T, typename U>
class BinaryNode : public ArrayNode<T, U, 2> {
public:
    using ArrayNode<T, U, 2>::ArrayNode;

    // Non-const version
    template <std::size_t Index>
    U& child() {
        static_assert(Index < 2, "Index out of bounds");
        return ArrayNode<T, U, 2>::getChildren()[Index];
    }

    // Const version
    template <std::size_t Index>
    const U& child() const {
        static_assert(Index < 2, "Index out of bounds");
        return ArrayNode<T, U, 2>::getChildren()[Index];
    }

    U& left() { return child<0>(); }
    U& right() { return child<1>(); }

    const U& left() const { return child<0>(); }
    const U& right() const { return child<1>(); }
};



template <typename T>
class BinaryTree;

template <typename T>
class BinaryTree : public ArrayTree<T, 2> {
public:
    using ArrayTree<T, 2>::ArrayTree;

    template <std::size_t Index>
    BinaryTree& child() {
        static_assert(Index < 2, "Index out of bounds");
        return static_cast<BinaryTree&>(ArrayTree<T, 2>::template child<Index>());
    }

    BinaryTree& left() { return child<0>(); }
    BinaryTree& right() { return child<1>(); }

    const BinaryTree& left() const { return child<0>(); }
    const BinaryTree& right() const { return child<1>(); }
};


} // namespace vpr

#endif // BINARY_TREE_HPP
