#ifndef LIST_TREE_HPP
#define LIST_TREE_HPP

#include <list>

#include "generic_tree.hpp"

namespace vpr {

template <typename T>
using ListTree = GenericTree<T, std::list>;

}

#endif