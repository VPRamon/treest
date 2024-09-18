#ifndef GENERIC_NODE_HPP
#define GENERIC_NODE_HPP

#include "node_interface.hpp"

#include <memory>

namespace vpr {

template <typename T, template <typename, typename> class Container>
class GenericNode : public NodeInterface<
                        std::unique_ptr<Container<GenericNode<T, Container>, std::allocator<GenericNode<T, Container>>>>,
                        T> {
    using NodeType = GenericNode<T, Container>;
    using ContainerType = Container<NodeType, std::allocator<NodeType>>;
    using ParentType = NodeInterface<std::unique_ptr<ContainerType>, T>;

public:
//    using ParentType::NodeInterface;
    using Node = ParentType::Node;

    GenericNode() : ParentType() {};
    GenericNode(ContainerType children) : ParentType(std::make_unique<ContainerType>(children)) {};
    GenericNode(T value) : ParentType(value) {};

    GenericNode(const GenericNode& other)
        : ParentType(other.data_, other.isLeaf() ? std::nullopt : std::optional<std::unique_ptr<ContainerType>>(std::make_unique<ContainerType>(*other.children_.value()))) {};

    GenericNode& operator=(const GenericNode& other) {
        if (this != &other) {
            ParentType::data_ = other.data_;
            ParentType::children_ = std::make_unique<ContainerType>(*other.children_.value());
        }
        return *this;
    }

    void pushChildren(T child) {
        if (ParentType::isLeaf()) ParentType::children_ = std::make_unique<ContainerType>();
        ParentType::children_.value()->push_back(NodeType(child));
    }

};


} // namespace vpr

#endif // GENERIC_NODE_HPP
