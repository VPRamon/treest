#ifndef VECTOR_TREE_HPP
#define VECTOR_TREE_HPP

#include "container_node.hpp"
#include <vector>

namespace vpr {


template <typename ChildType, typename Type>
using VectorNode = ContainerNode<ChildType, Type, std::vector>;

template <typename Type>
using SimpleVectorNode = SimpleContainerNode<Type, std::vector>;

}

#endif
