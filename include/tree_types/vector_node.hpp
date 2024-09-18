#ifndef VECTOR_TREE_HPP
#define VECTOR_TREE_HPP

#include "container_node.hpp"
#include <vector>

namespace vpr {


template <typename ChildType, typename Type>
using VectorNode = vpr::NodeInterface<std::vector<ChildType>, Type>;

template <typename T>
class VectorTree;

template <typename T>
class VectorTree : public vpr::Tree<T, std::vector<VectorTree<T>>> {
    public:
        using vpr::Tree<T, std::vector<VectorTree<T>>>::Tree;
};

}

#endif
