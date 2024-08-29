#ifndef DEQUE_TREE_HPP
#define DEQUE_TREE_HPP

#include <deque>

#include "generic_node.hpp"

namespace vpr {

template <typename T>
using DequeTree = GenericNode<T, std::deque>;

}

#endif