#ifndef LIST_TREE_HPP
#define LIST_TREE_HPP

#include "container_node.hpp"
#include <list>

namespace vpr {


template <typename ChildType, typename Type>
using ListNode = ContainerNode<ChildType, Type, std::list>;

template <typename Type>
using SimpleListNode = SimpleContainerNode<Type, std::list>;

}

#endif
