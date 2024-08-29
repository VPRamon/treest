#ifndef CUSTOM_NODE_HPP
#define CUSTOM_NODE_HPP

#include "node_interface.hpp"

#include <cassert>

namespace vpr {

template <typename Data, typename Children>
class CustomNode : public NodeInterface<Children, Data> {
    using ParentType = NodeInterface<Children, Data>;

public:
    using ParentType::NodeInterface;
    using Node = ParentType::Node;
};


} // namespace vpr

#endif // CUSTOM_NODE_HPP
