#ifndef DEQUE_TREE_HPP
#define DEQUE_TREE_HPP

#include "container_node.hpp"
#include <deque>

namespace vpr {


template <typename ChildType, typename Type>
using DequeNode = ContainerNode<ChildType, Type, std::deque>;

template <typename Type>
using SimpleDequeNode = SimpleContainerNode<Type, std::deque>;

}

#endif
