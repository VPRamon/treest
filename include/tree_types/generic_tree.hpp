#ifndef GENERIC_TREE_HPP
#define GENERIC_TREE_HPP

#include "node.hpp"

#include <cassert>

namespace vpr {

template <typename T, template <typename, typename> class Container>
class GenericTree : public NodeInterface<
                        Container<GenericTree<T, Container>, std::allocator<GenericTree<T, Container>>>,
                        T> {
    using NodeType = GenericTree<T, Container>;
    using ContainerType = Container<NodeType, std::allocator<NodeType>>;
    using ParentType = NodeInterface<ContainerType, T>;

public:
    using ParentType::NodeInterface;
    using Node = ParentType::Node;

};


} // namespace vpr

#endif // GENERIC_TREE_HPP
