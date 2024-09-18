#ifndef LIST_TREE_HPP
#define LIST_TREE_HPP

#include <list>

#include "generic_node.hpp"

namespace vpr {

template <typename T>
using ListNode = GenericNode<T, std::list>;

}

#endif