#ifndef DEQUE_TREE_HPP
#define DEQUE_TREE_HPP

#include "container_node.hpp"
#include <deque>

namespace vpr {


template <typename ChildType, typename Type>
using DequeNode = vpr::NodeInterface<std::deque<ChildType>, Type>;

template <typename T>
class DequeTree;

template <typename T>
class DequeTree : public vpr::Tree<T, std::deque<DequeTree<T>>> {
    public:
        using vpr::Tree<T, std::deque<DequeTree<T>>>::Tree;
};

}

#endif
