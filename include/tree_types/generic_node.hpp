#ifndef GENERIC_NODE_HPP
#define GENERIC_NODE_HPP

#include "node_interface.hpp"

#include <cassert>

namespace vpr {

template <typename T, template <typename, typename> class Container>
class GenericNode : public NodeInterface<
                        Container<GenericNode<T, Container>, std::allocator<GenericNode<T, Container>>>,
                        T> {
    using NodeType = GenericNode<T, Container>;
    using ContainerType = Container<NodeType, std::allocator<NodeType>>;
    using ParentType = NodeInterface<ContainerType, T>;

public:
    using ParentType::NodeInterface;
    using Node = ParentType::Node;

};


} // namespace vpr

#endif // GENERIC_NODE_HPP
