#ifndef CONTAINER_NODE_HPP
#define CONTAINER_NODE_HPP

#include "node_interface.hpp"

namespace vpr {


template <typename T, typename U>
class Tree : public vpr::NodeInterface<std::unique_ptr<U>, T> {

    using ParentType = vpr::NodeInterface<std::unique_ptr<U>, T>;

public:
    Tree() : ParentType() {}
    Tree(T value) : ParentType(value) {}

    Tree(U children)
        : ParentType(std::make_unique<U>(children)) {}

    Tree(T value, U children) 
        : ParentType(value, std::make_unique<U>(children)) {}

    Tree(const Tree& other)
        : ParentType(other.data_, other.isLeaf() ? std::nullopt
                                                 : std::optional(std::make_unique<U>(*(other.children_.value())))) {}

    Tree& operator=(const Tree& other) {
        if (this != &other) {
            ParentType::data_ = other.data_;
            ParentType::children_ = other.isLeaf() ? std::nullopt
                                                   : std::optional(std::make_unique<U>(*(other.children_.value())));
        }
        return *this;
    }
};

}

#endif
