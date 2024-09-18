#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "array_node.hpp"

namespace vpr {

template <typename T, typename U>
using BinaryNode = ArrayNode<T, U, 2>;


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
