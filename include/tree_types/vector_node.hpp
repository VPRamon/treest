#ifndef VECTOR_TREE_HPP
#define VECTOR_TREE_HPP

#include "node_interface.hpp"
#include <vector>

namespace vpr {


template <typename ChildType, typename Type>
class VectorNode : public vpr::NodeInterface<std::unique_ptr<std::vector<ChildType>>, Type> {
    using ChildrenType = std::vector<ChildType>;
    using ParentType = NodeInterface<std::unique_ptr<ChildrenType>, Type>;

public:

    VectorNode() : ParentType() {};
    VectorNode(ChildrenType children) : ParentType(std::make_unique<ChildrenType>(children)) {};
    VectorNode(Type value, ChildrenType children) : ParentType(value, std::make_unique<ChildrenType>(children)) {};
    VectorNode(Type value) : ParentType(value) {};

    VectorNode(const VectorNode& other)
        : ParentType(other.data_, other.isLeaf() ? std::nullopt 
                                                : std::optional<std::unique_ptr<ChildrenType>>(
                                                    std::make_unique<ChildrenType>(*other.children_.value())
                                                )
                ) {};

    VectorNode& operator=(const VectorNode& other) {
        if (this != &other) {
            ParentType::data_ = other.data_;
            ParentType::children_ = std::make_unique<std::vector<ChildType>>(*other.children_.value());
        }
        return *this;
    }
};

template <typename Type> class SimpleVectorNode;

template <typename Type>
class SimpleVectorNode : public VectorNode<SimpleVectorNode<Type>, Type> {
public:

    using ParentType = VectorNode<SimpleVectorNode<Type>, Type>;

    SimpleVectorNode() : ParentType() {};
    SimpleVectorNode(Type value, SimpleVectorNode<Type> children) : ParentType(value, children) {};
    SimpleVectorNode(Type value) : ParentType(value) {};
    SimpleVectorNode(const SimpleVectorNode& other) : ParentType(other) {};
    SimpleVectorNode(const std::vector<SimpleVectorNode>& other) : ParentType(other) {};

};

}

#endif
