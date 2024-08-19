#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <optional>
#include <cassert>

namespace rvp {

template <typename ChildrenType, typename NodeType>
class NodeInterface {
public:
    NodeInterface() = default;

    NodeInterface(const NodeType& data, const ChildrenType& children)
        : data_(data), children_(std::make_unique<ChildrenType>(children)) { }

    NodeInterface(const NodeType& data)
        : data_(data), children_(nullptr) { }

    NodeInterface(const ChildrenType& children)
        : data_(std::nullopt), children_(std::make_unique<ChildrenType>(children)) { }

    NodeInterface(const NodeInterface& other)
        : data_(other.data_),
          children_(other.children_ ? std::make_unique<ChildrenType>(*other.children_) : nullptr) { }

    NodeInterface& operator=(const NodeInterface& other) {
        if (this != &other) {
            data_ = other.data_;
            children_ = other.children_ ? std::make_unique<ChildrenType>(*other.children_) : nullptr;
        }
        return *this;
    }

    NodeInterface(NodeInterface&& other) noexcept = default;
    NodeInterface& operator=(NodeInterface&& other) noexcept = default;

    virtual ~NodeInterface() = default;

    bool isLeaf() const { return !children_; }
    bool hasValue() const { return data_.has_value(); }

    const NodeType& value() const {
        assert(data_.has_value() && "Attempting to access a value that is not set.");
        return data_.value();
    }

protected:
    std::optional<NodeType> data_;
    std::unique_ptr<ChildrenType> children_;
};


// OTHER CONTAINERS ??

//template <typename... NodeTypes> // Binary tree
//class Node : NodeInterface<std::pair, NodeTypes> {};

//template <typename... NodeTypes> // Ternary/N- tree
//class Node : NodeInterface<std::array, NodeTypes> {};

//template <typename... NodeTypes> // Ordered Tree
//class Node : NodeInterface<std::set, NodeTypes> {};

//template <typename... NodeTypes> // CustomTree
//class Node : NodeInterface<std::list, NodeTypes> {};

//template <typename... NodeTypes>
//class Node : NodeInterface<std::vector, NodeTypes> {};


} // namespace rvp

#endif // TREE_HPP
