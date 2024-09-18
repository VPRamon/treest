#ifndef ARRAY_TREE_HPP
#define ARRAY_TREE_HPP

#include "container_node.hpp"
#include <array>

namespace vpr {


template <typename T, typename U, std::size_t N>
using ArrayNode = vpr::NodeInterface<std::array<U, N>, T>;

template <typename T, std::size_t N>
class ArrayTree;

template <typename T, std::size_t N=2>
class ArrayTree : public vpr::Tree<T, std::array<ArrayTree<T, N>, N>> {
    public:
        using vpr::Tree<T, std::array<ArrayTree<T>, N>>::Tree;
};

}

#endif
