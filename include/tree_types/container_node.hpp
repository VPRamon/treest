#ifndef CONTAINER_NODE_HPP
#define CONTAINER_NODE_HPP

#include "node_interface.hpp"
#include <vector>

namespace vpr {


template <typename ChildType, typename Type, template <typename...> class ContainerType = std::vector>
class ContainerNode : public vpr::NodeInterface<std::unique_ptr<ContainerType<ChildType>>, Type> {
    using ChildrenType = ContainerType<ChildType>;
    using ParentType = vpr::NodeInterface<std::unique_ptr<ChildrenType>, Type>;

public:
    ContainerNode() : ParentType() {}

    ContainerNode(ChildrenType children) 
        : ParentType(std::make_unique<ChildrenType>(children)) {}

    ContainerNode(Type value, ChildrenType children) 
        : ParentType(value, std::make_unique<ChildrenType>(children)) {}

    ContainerNode(Type value) 
        : ParentType(value) {}

    ContainerNode(const ContainerNode& other)
        : ParentType(other.data_, 
            other.isLeaf() ? std::nullopt 
                           : std::optional<std::unique_ptr<ChildrenType>>(
                                std::make_unique<ChildrenType>(*other.children_.value())
                           )
        ) {}

    ContainerNode& operator=(const ContainerNode& other) {
        if (this != &other) {
            ParentType::data_ = other.data_;
            if (other.children_) {
                ParentType::children_ = std::make_unique<ChildrenType>(*other.children_.value());
            } else {
                ParentType::children_ = std::nullopt;
            }
        }
        return *this;
    }
};

template <typename Type, template <typename...> class ContainerType>
class SimpleContainerNode;

template <typename Type, template <typename...> class ContainerType>
class SimpleContainerNode : public ContainerNode<SimpleContainerNode<Type, ContainerType>, Type, ContainerType> {
public:
    using ParentType = ContainerNode<SimpleContainerNode<Type, ContainerType>, Type, ContainerType>;
    using ChildrenType = ContainerType<SimpleContainerNode<Type, ContainerType>>;

    SimpleContainerNode() : ParentType() {}

    SimpleContainerNode(Type value, ChildrenType children)
        : ParentType(value, children) {}

    SimpleContainerNode(Type value)
        : ParentType(value) {}

    SimpleContainerNode(const SimpleContainerNode& other)
        : ParentType(other) {}

    SimpleContainerNode(const ChildrenType& other)
        : ParentType(other) {}
};


}

#endif
