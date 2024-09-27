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
    using Iterator = TreeIterator<ChildrenType, NodeType, Node*>;
    using ConstIterator = TreeIterator<ChildrenType, NodeType, const Node*>;
    using ChildrenContainer = typename std::pointer_traits<ChildrenType>::element_type;

    friend Iterator;

    NodeInterface() : data_(std::nullopt), children_(nullptr) { }

    NodeInterface(const std::optional<NodeType>& data, ChildrenType children)
        : data_(data), children_(std::move(children)) { }

    NodeInterface(const std::optional<NodeType>& data)
        : data_(data), children_(nullptr) { }

    NodeInterface(ChildrenType children)
        : data_(std::nullopt), children_(std::move(children)) { }

    virtual ~NodeInterface() = default;

    Iterator begin() { return Iterator(this); }
    Iterator end() { return Iterator(nullptr); }

    ConstIterator begin() const { return ConstIterator(this); }
    ConstIterator end() const { return ConstIterator(nullptr); }

    bool isLeaf() const { return !children_; }

    bool hasValue() const { return data_.has_value(); }

    const ChildrenContainer& getChildren() const {
        assert(children_ && "Attempting to access children that are not set.");
        return *children_;
    }

    ChildrenContainer& getChildren() {
        assert(children_ && "Attempting to access children that are not set.");
        return *children_;
    }


    const NodeType& value() const {
        assert(data_.has_value() && "Attempting to access a value that is not set.");
        return data_.value();
    }

    friend std::ostream& operator<<(std::ostream& os, const NodeInterface& node) {
        if (node.hasValue()) {
            os << node.value();
        }

        if (!node.isLeaf()) {
            os << "[";
            bool first = true;
            for (const auto& child : node.getChildren()) {
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
    ChildrenType children_;
};


} // namespace vpr

#endif // TREE_HPP
