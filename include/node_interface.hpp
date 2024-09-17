#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <optional>
#include <cassert>
#include <iostream>
#include <variant>

#include "dfs_iterator.hpp"

namespace vpr {

template <typename... Types>
std::ostream& operator<<(std::ostream& os, const std::variant<Types...>& var) {
    std::visit([&os](const auto& value) {
        os << value;
    }, var);
    return os;
}

template <typename ChildrenType, typename NodeType>
class NodeInterface {
public:
    using Node = NodeInterface<ChildrenType, NodeType>;
    using Iterator = TreeIterator<ChildrenType, NodeType>;
    friend Iterator;

    NodeInterface() : data_(std::nullopt), children_(std::nullopt) { }

    NodeInterface(const std::optional<NodeType>& data, std::optional<ChildrenType> children)
        : data_(data), children_(std::move(children)) { }

    NodeInterface(const std::optional<NodeType>& data)
        : data_(data), children_(std::nullopt) { }

    NodeInterface(std::optional<ChildrenType> children)
        : data_(std::nullopt), children_(std::move(children)) { }

    //NodeInterface(NodeInterface&& other) noexcept = default;
    //NodeInterface& operator=(NodeInterface&& other) noexcept = default;

    virtual ~NodeInterface() = default;

    auto begin() { return Iterator(this); }
    auto end() { return Iterator(static_cast<Node*>(nullptr)); }

    auto begin() const { return Iterator(this); }
    auto end() const { return Iterator(static_cast<const Node*>(nullptr)); }

    bool isLeaf() const { return !children_.has_value(); }
    bool hasValue() const { return data_.has_value(); }

    const ChildrenType& getChildren() const {
        assert(children_.has_value() && "Attempting to access a value that is not set.");
        return children_.value();
    }

    ChildrenType& getChildren() {
        assert(children_.has_value() && "Attempting to access a value that is not set.");
        return children_.value();
    }

    const NodeType& value() const {
        assert(data_.has_value() && "Attempting to access a value that is not set.");
        return data_.value();
    }

    friend std::ostream& operator<<(std::ostream& os, const NodeInterface& node) {
        if (node.hasValue()) {
            os << node.value();
        }

        if (node.children_) {
            os << "[";
            bool first = true;
            for (const auto& child : *node.getChildren()) {
                if (!first) {
                    os << ", ";
                }
                os << child;
                first = false;
            }
            os << "]";
        }

        return os;
    }

protected:
    std::optional<NodeType> data_;
    std::optional<ChildrenType> children_;
};


} // namespace vpr

#endif // TREE_HPP
