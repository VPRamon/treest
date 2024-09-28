#ifndef FLAT_TREE_NODE_HPP
#define FLAT_TREE_NODE_HPP

#include <optional>
#include <vector>
#include <iostream>
#include <variant>
#include "type_traits.hpp"

namespace vpr {

// Forward declaration of FlatTree
template <typename T>
class FlatTree;

// Forward declaration of FlatTreeIterator with all template parameters
template <typename NodeType, typename TreeType, typename TraversalPolicy>
class FlatTreeIterator;

// Forward declaration of PreOrderTraversal with all template parameters
template <typename NodeType, typename TreeType>
class PreOrderTraversal;

// Forward declaration of PreOrderTraversal with all template parameters
template <typename NodeType, typename TreeType>
class PostOrderTraversal;

// Forward declaration of LevelOrderTraversal with all template parameters
template <typename NodeType, typename TreeType>
class LevelOrderTraversal;

template <typename NodeType, typename TreeType>
class ReversePreOrderTraversal;

template <typename T>
class FlatTreeNode {
    friend FlatTree<T>;

    // Grant friendship to all instantiations of FlatTreeIterator
    template <typename NodeType, typename TreeType, typename TraversalPolicy>
    friend class FlatTreeIterator;

    template <typename NodeType, typename TreeType>
    friend class PreOrderTraversal;

    template <typename NodeType, typename TreeType>
    friend class PostOrderTraversal;

    template <typename NodeType, typename TreeType>
    friend class LevelOrderTraversal;

    template <typename NodeType, typename TreeType>
    friend class ReversePreOrderTraversal;

private:
    int index_;                         // Index of the self node
    int parentIndex_;                   // Index of the parent node (-1 for the root)
    std::vector<int> childIndices_;     // Indices of the children nodes
    FlatTree<T>* tree_;

public:
    std::optional<T> value;            // Optional value for the node

    // Default constructor
    FlatTreeNode() 
        : value(std::nullopt), parentIndex_(-1), index_(0), tree_(nullptr), childIndices_() {}

    // Constructor accepting std::optional<T> and parent index
    FlatTreeNode(std::optional<T> v, int parentIdx = -1, int index = 0, FlatTree<T>* tree = nullptr)
        : value(v), parentIndex_(parentIdx), index_(index), tree_(tree), childIndices_() {}

    // Overload operator<< for FlatTreeNode
    friend std::ostream& operator<<(std::ostream& os, const FlatTreeNode<T>& node) {
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

    bool isRoot() const { return parentIndex_ == -1; }
    bool isLeaf() const { return childIndices_.empty(); }

    int nChildren() const { return static_cast<int>(childIndices_.size()); }
    int index() const { return index_; }
    int parentIndex() const { return parentIndex_; }
    const FlatTree<T>* tree() const { return tree_; }

    // Add child to this node (optional value)
    int addChild(std::optional<T> value = std::nullopt) {
        return tree_->addChild(index_, value);
    }

    // Get a reference to a child node at a specific index
    FlatTreeNode<T>& getChild(int index) {
        if (index < 0 || index >= static_cast<int>(childIndices_.size())) {
            throw std::out_of_range("Invalid child index.");
        }
        return tree_->getNode(childIndices_.at(index));
    }

    // Non-const version
    std::vector<std::reference_wrapper<FlatTreeNode<T>>> getChildren() {
        return getChildrenImpl<FlatTreeNode<T>>();
    }

    // Const version
    std::vector<std::reference_wrapper<const FlatTreeNode<T>>> getChildren() const {
        return getChildrenImpl<const FlatTreeNode<T>>();
    }

private:
    template <typename NodeType>
    std::vector<std::reference_wrapper<NodeType>> getChildrenImpl() const {
        std::vector<std::reference_wrapper<NodeType>> children;
        children.reserve(childIndices_.size()); // Optimize memory allocation
        for (const int& childIdx : childIndices_) {
            children.emplace_back(tree_->getNode(childIdx));
        }
        return children;
    }
};

} // namespace vpr

#endif // FLAT_TREE_NODE_HPP
