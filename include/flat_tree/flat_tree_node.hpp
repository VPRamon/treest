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
//template <typename NodeType, typename TreeType>
//class PreOrderTraversal;

// Forward declaration of PreOrderTraversal with all template parameters
template <typename NodeType, typename TreeType>
class PostOrderTraversal;

// Forward declaration of LevelOrderTraversal with all template parameters
template <typename NodeType, typename TreeType>
class LevelOrderTraversal;

//template <typename NodeType, typename TreeType>
//class ReversePreOrderTraversal;

template <typename T>
class FlatTreeNode {
    friend FlatTree<T>;

    template <typename TreeType, template <typename...> class Container, bool straight>
    friend struct OrderPolicy;

    // Grant friendship to all instantiations of FlatTreeIterator
    template <typename NodeType, typename TreeType, typename TraversalPolicy>
    friend class FlatTreeIterator;

    template <typename NodeType, typename TreeType>
    friend class PostOrderTraversal;

    template <typename NodeType, typename TreeType>
    friend class LevelOrderTraversal;

    template <typename NodeType, typename TreeType, bool straight>
    friend class PreOrderTraversalBase;

private:
    size_t index_;                         // Index of the self node
    size_t parentIndex_;                   // Index of the parent node (-1 for the root)
    std::vector<size_t> childIndices_;     // Indices of the children nodes
    FlatTree<T>* tree_;

public:
    std::optional<T> value;            // Optional value for the node

    // Default constructor
    FlatTreeNode() 
        : value(std::nullopt), parentIndex_(0), index_(0), tree_(nullptr), childIndices_() {}

    // Constructor accepting std::optional<T> and parent index
    FlatTreeNode(std::optional<T> v, size_t parentIdx = 0, size_t index = 0, FlatTree<T>* tree = nullptr)
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

    bool isRoot() const { return index_ == 0; }
    bool isLeaf() const { return childIndices_.empty(); }

    size_t nChildren() const { return childIndices_.size(); }
    size_t index() const { return index_; }
    size_t parentIndex() const { return parentIndex_; }
    const FlatTree<T>* tree() const { return tree_; }

    // Add child to this node (optional value)
    size_t addChild(std::optional<T> value = std::nullopt) {
        return tree_->addChild(index_, value);
    }

    // Get a reference to a child node at a specific index
    FlatTreeNode<T>& getChild(size_t index) {
        if (index >= childIndices_.size()) {
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
        for (const size_t& childIdx : childIndices_) {
            children.emplace_back(tree_->getNode(childIdx));
        }
        return children;
    }
};

} // namespace vpr

#endif // FLAT_TREE_NODE_HPP
