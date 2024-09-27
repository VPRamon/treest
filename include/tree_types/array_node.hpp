#ifndef ARRAY_TREE_HPP
#define ARRAY_TREE_HPP

#include "container_node.hpp"
#include <array>

namespace vpr {


template <typename T, typename U, std::size_t N>
using ArrayNode = vpr::NodeInterface<std::array<U, N>, T>;

template <typename T, std::size_t N>
class ArrayTree;

template <typename T, std::size_t N = 2>
class ArrayTree : public vpr::Tree<T, std::array<ArrayTree<T, N>, N>> {
public:
    using vpr::Tree<T, std::array<ArrayTree<T, N>, N>>::Tree;

    static_assert(N > 0, "ArrayTree must have at least one child");

    template <std::size_t Index>
    ArrayTree& child() {
        static_assert(Index < N, "Index out of bounds");
        assert(this->children_ && "Attempting to access child of a leaf node.");
        return (*this->children_)[Index];
    }

    template <std::size_t Index>
    const ArrayTree& child() const {
        static_assert(Index < N, "Index out of bounds");
        assert(this->children_ && "Attempting to access child of a leaf node.");
        return (*this->children_)[Index];
    }
};

}

#endif
