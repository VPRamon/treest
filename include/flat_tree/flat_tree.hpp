#ifndef FLAT_TREE_HPP
#define FLAT_TREE_HPP

#include "flat_tree_node.hpp"
#include "flat_tree_iterator.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>

namespace vpr {

template <typename T>
class FlatTree {
public:
    std::vector<FlatTreeNode<T>> nodes;  // Flat array to store all nodes

    // Constructor
    FlatTree(std::optional<T> value = std::nullopt) {
        nodes.reserve(16);  // Pre-allocate space for nodes
        nodes.emplace_back(value, -1, 0, this);  // Create the root node with no parent
    }

    FlatTree(FlatTree& other) : nodes(other.nodes) {
        for (auto node : nodes)
            node.tree = this;
    }

    // Copy Assignment Operator
    FlatTree& operator=(const FlatTree& other) {
        if (this != &other) {
            nodes = other.nodes;
            for (auto& node : nodes) {
                node.tree_ = this;
            }
        }
        return *this;
    }

    // Add child to a node at 'parentIndex' (optional value)
    int addChild(int parentIndex, std::optional<T> value = std::nullopt) {
        int childIndex = static_cast<int>(nodes.size());
        nodes.emplace_back(value, parentIndex, childIndex, this);  // Create and store child node
        nodes[parentIndex].childIndices_.push_back(childIndex);    // Link parent to child
        return childIndex;
    }

    // Get a reference to a node at a specific index (non-const)
    FlatTreeNode<T>& getNode(int index) {
        return nodes.at(index);  // Using at() for bounds checking
    }

    // Get a reference to a node at a specific index (const)
    const FlatTreeNode<T>& getNode(int index) const {
        return nodes.at(index);  // Using at() for bounds checking
    }

    // Get a reference to the root node (non-const)
    FlatTreeNode<T>& getRoot() {
        return nodes.at(0);  // Using at() for bounds checking
    }

    // Get a reference to the root node (const)
    const FlatTreeNode<T>& getRoot() const {
        return nodes.at(0);  // Using at() for bounds checking
    }

    // Check if a node has a value (const)
    bool hasValue(int nodeIndex) const {
        return nodes.at(nodeIndex).value.has_value();
    }

    size_t size() {
        return nodes.size();
    }

    // *** Iterator Methods ***

    // Pre-order traversal iterators
    auto pre_order_begin() {
        using Traversal = PreOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
        return FlatTreeIterator<FlatTreeNode<T>, FlatTree<T>, Traversal>(this, nodes.empty() ? -1 : 0);
    }

    auto pre_order_end() {
        using Traversal = PreOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
        return FlatTreeIterator<FlatTreeNode<T>, FlatTree<T>, Traversal>(this, -1);
    }

    auto pre_order_begin() const {
        using Traversal = PreOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;
        return FlatTreeIterator<const FlatTreeNode<T>, const FlatTree<T>, Traversal>(this, nodes.empty() ? -1 : 0);
    }

    auto pre_order_end() const {
        using Traversal = PreOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;
        return FlatTreeIterator<const FlatTreeNode<T>, const FlatTree<T>, Traversal>(this, -1);
    }

    // Post-order traversal iterators
    auto post_order_begin() {
        using Traversal = PostOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
        return FlatTreeIterator<FlatTreeNode<T>, FlatTree<T>, Traversal>(this, nodes.empty() ? -1 : 0);
    }

    auto post_order_end() {
        using Traversal = PostOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
        return FlatTreeIterator<FlatTreeNode<T>, FlatTree<T>, Traversal>(this, -1);
    }

    auto post_order_begin() const {
        using Traversal = PostOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;
        return FlatTreeIterator<const FlatTreeNode<T>, const FlatTree<T>, Traversal>(this, nodes.empty() ? -1 : 0);
    }

    auto post_order_end() const {
        using Traversal = PostOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;
        return FlatTreeIterator<const FlatTreeNode<T>, const FlatTree<T>, Traversal>(this, -1);
    }

    // Level-order traversal iterators
    auto level_order_begin() {
        using Traversal = LevelOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
        return FlatTreeIterator<FlatTreeNode<T>, FlatTree<T>, Traversal>(this, nodes.empty() ? -1 : 0);
    }

    auto level_order_end() {
        using Traversal = LevelOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
        return FlatTreeIterator<FlatTreeNode<T>, FlatTree<T>, Traversal>(this, -1);
    }

    auto level_order_begin() const {
        using Traversal = LevelOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;
        return FlatTreeIterator<const FlatTreeNode<T>, const FlatTree<T>, Traversal>(this, nodes.empty() ? -1 : 0);
    }

    auto level_order_end() const {
        using Traversal = LevelOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;
        return FlatTreeIterator<const FlatTreeNode<T>, const FlatTree<T>, Traversal>(this, -1);
    }

    // *** Reverse Iterators ***

    // Reverse pre-order traversal iterators
    auto pre_order_rbegin() {
        using Traversal = ReversePreOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
        return FlatTreeIterator<FlatTreeNode<T>, FlatTree<T>, Traversal>(this, nodes.empty() ? -1 : 0);
    }

    auto pre_order_rend() {
        using Traversal = ReversePreOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
        return FlatTreeIterator<FlatTreeNode<T>, FlatTree<T>, Traversal>(this, -1);
    }

    auto pre_order_rbegin() const {
        using Traversal = ReversePreOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;
        return FlatTreeIterator<const FlatTreeNode<T>, const FlatTree<T>, Traversal>(this, nodes.empty() ? -1 : 0);
    }

    auto pre_order_rend() const {
        using Traversal = ReversePreOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;
        return FlatTreeIterator<const FlatTreeNode<T>, const FlatTree<T>, Traversal>(this, -1);
    }

    // Overload operator<< for FlatTree
    friend std::ostream& operator<<(std::ostream& os, const FlatTree<T>& tree) {
        for (const auto& node : tree.nodes) {
            os << node << " ";
        }
        return os;
    }

private:
    // Validate that the parent index is within bounds
    void validateParentIndex(int parentIndex) const {
        if (parentIndex < 0 || parentIndex >= static_cast<int>(nodes.size())) {
            throw std::out_of_range("Invalid parent index.");
        }
    }

};

} // namespace vpr

#endif // FLAT_TREE_HPP
