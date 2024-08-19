#ifndef COMMON_TREE_HPP
#define COMMON_TREE_HPP

#include "node.hpp"

#include <list>
#include <vector>
#include <cassert>

namespace rvp {

template <typename T, template <typename, typename> class Container>
class GenericTree : public NodeInterface<
                        Container<GenericTree<T, Container>, std::allocator<GenericTree<T, Container>>>,
                        T> {
    using ChildrenType = Container<GenericTree<T, Container>, std::allocator<GenericTree<T, Container>>>;
    using ParentType = NodeInterface<ChildrenType, T>;

public:
    using ParentType::NodeInterface;

    auto begin() {
        assert(this->children_ && "Attempting to access begin child of a leaf node.");
        return this->children_->begin();
    }

    auto end() {
        assert(this->children_ && "Attempting to access end child of a leaf node.");
        return this->children_->end();
    }
};

// Example aliases for the original ListTree and VectorTree
template <typename T>
using ListTree = GenericTree<T, std::list>;

template <typename T>
using VectorTree = GenericTree<T, std::vector>;

} // namespace rvp

#endif // COMMON_TREE_HPP
