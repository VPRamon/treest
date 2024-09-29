#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <optional>
#include <vector>
#include <iostream>
#include <variant>
#include "type_traits.hpp"

namespace vpr {

template <typename T>
class Tree;

template <typename NodeType, typename TreeType>
class PostOrderTraversal;

template <typename NodeType, typename TreeType, typename TraversalPolicy>
class TreeIterator;

template <typename T>
class TreeNode {

    template <typename NodeType, typename TreeType>
    friend class PostOrderTraversal;

    friend class ReversePush;
    friend class StraightPush;

    friend Tree<T>;

private:
    size_t index_;                         // Index of the self node
    size_t parentIndex_;                   // Index of the parent node (-1 for the root)
    std::vector<size_t> childIndices_;     // Indices of the children nodes
    Tree<T>* tree_;

public:
    std::optional<T> value;                // Optional value for the node

    TreeNode(std::optional<T> v, size_t parentIdx = 0, size_t index = 0, Tree<T>* tree = nullptr)
        : value(v), parentIndex_(parentIdx), index_(index), tree_(tree), childIndices_()
    {}

    friend std::ostream& operator<<(std::ostream& os, const TreeNode<T>& node) {
        if (node.value.has_value()) {
            if constexpr (is_variant<T>::value) {
                // Handle std::variant by visiting the current value
                std::visit([&os](const auto& val) {
                    os << val;
                }, node.value.value());
            } else {
                // Handle non-variant types directly
                os << node.value.value();
            }
        } else {
            os << "None";
        }
        return os;
    }

    bool isRoot() const { return index_ == 0; }
    bool isLeaf() const { return childIndices_.empty(); }

    size_t nChildren() const { return childIndices_.size(); }
    size_t index() const { return index_; }
    size_t parentIndex() const { return parentIndex_; }

    const Tree<T>* tree() const { return tree_; }

    size_t addChild(std::optional<T> value = std::nullopt) {
        return tree_->addChild(index_, value);
    }

    TreeNode<T>& getChild(size_t index) {
        if (index >= childIndices_.size()) {
            throw std::out_of_range("Invalid child index.");
        }
        return tree_->getNode(childIndices_.at(index));
    }

    std::vector<std::reference_wrapper<TreeNode<T>>> getChildren() {
        return getChildrenImpl<TreeNode<T>>();
    }

    std::vector<std::reference_wrapper<const TreeNode<T>>> getChildren() const {
        return getChildrenImpl<const TreeNode<T>>();
    }

private:
    template <typename NodeType>
    std::vector<std::reference_wrapper<NodeType>> getChildrenImpl() const {
        std::vector<std::reference_wrapper<NodeType>> children;
        children.reserve(childIndices_.size());
        for (const size_t& childIdx : childIndices_) {
            children.emplace_back(tree_->getNode(childIdx));
        }
        return children;
    }
};

} // namespace vpr

#endif // TREE_NODE_HPP
