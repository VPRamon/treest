#ifndef DEQUE_TREE_HPP
#define DEQUE_TREE_HPP

#include <deque>

#include "generic_tree.hpp"

namespace vpr {

template <typename T>
using DequeTree = GenericTree<T, std::deque>;

}

#endif