#ifndef VECTOR_TREE_HPP
#define VECTOR_TREE_HPP

#include <vector>

#include "generic_node.hpp"

namespace vpr {

template <typename T>
using VectorTree = GenericNode<T, std::vector>;

}

#endif
