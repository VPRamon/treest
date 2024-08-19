#ifndef VECTOR_TREE_HPP
#define VECTOR_TREE_HPP

#include <vector>

#include "generic_tree.hpp"

namespace vpr {

template <typename T>
using VectorTree = GenericTree<T, std::vector>;

}

#endif