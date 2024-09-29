#ifndef TREE_HPP
#define TREE_HPP

#include "tree_node.hpp"
#include "postorder_iterator.hpp"
#include "preorder_iterator.hpp"
#include "bfs_iterator.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <type_traits>

namespace vpr {

/**
 * @brief Represents a tree structure using a vector to store nodes.
 *
 * The Tree class manages a collection of nodes stored in a vector,
 * allowing efficient traversal and manipulation of the tree structure.
 *
 * @tparam T The type of the value stored in each node.
 */
template <typename T>
class Tree {

    template <typename NodeType, typename TreeType, typename TraversalPolicy>
    friend class TreeIterator;

    template <typename NodeType, typename TreeType>
    friend class PostOrderTraversal;

    friend class ReversePush;
    friend class StraightPush;

    // Type aliases for traversal policies
    using PreOrderTraversalType = PreOrderTraversal<Tree<T>>;
    using ConstPreOrderTraversalType = PreOrderTraversal<const Tree<T>>;

    using PostOrderTraversalType = PostOrderTraversal<TreeNode<T>, Tree<T>>;
    using ConstPostOrderTraversalType = PostOrderTraversal<const TreeNode<T>, const Tree<T>>;

    using BFSTraversalType = BFSTraversal<Tree<T>>;
    using ConstBFSTraversalType = BFSTraversal<const Tree<T>>;
    using ReverseBFSTraversalType = ReverseBFSTraversal<Tree<T>>;
    using ConstReverseBFSTraversalType = ReverseBFSTraversal<const Tree<T>>;

    using ReversePreOrderTraversalType = ReversePreOrderTraversal<Tree<T>>;
    using ConstReversePreOrderTraversalType = ReversePreOrderTraversal<const Tree<T>>;

public:

    /**
     * @brief Constructs a Tree with an optional root value and initial capacity.
     *
     * @param value Optional value for the root node. Defaults to `std::nullopt`.
     * @param initialCapacity Initial capacity for the nodes vector. Defaults to 16.
     */
    explicit Tree(std::optional<T> value = std::nullopt, size_t initialCapacity = 16) {
        nodes.reserve(initialCapacity);
        nodes.emplace_back(std::move(value), static_cast<size_t>(-1), 0, this);  // Root node with no parent
    }

    /**
     * @brief Copy constructor. Performs a deep copy of the tree.
     *
     * @param other The Tree to copy from.
     */
    Tree(const Tree& other) : nodes(other.nodes) {
        for (auto& node : nodes) {
            node.tree_ = this;
        }
    }

    /**
     * @brief Move constructor. Transfers ownership of the tree from another Tree.
     *
     * @param other The Tree to move from.
     */
    Tree(Tree&& other) noexcept : nodes(std::move(other.nodes)) {
        for (auto& node : nodes) {
            node.tree_ = this;
        }
    }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the tree.
     *
     * @param other The Tree to copy from.
     * @return Reference to the assigned Tree.
     */
    Tree& operator=(const Tree& other) {
        if (this != &other) {
            nodes = other.nodes;
            for (auto& node : nodes) {
                node.tree_ = this;
            }
        }
        return *this;
    }

    /**
     * @brief Move assignment operator. Transfers ownership of the tree from another Tree.
     *
     * @param other The Tree to move from.
     * @return Reference to the assigned Tree.
     */
    Tree& operator=(Tree&& other) noexcept {
        if (this != &other) {
            nodes = std::move(other.nodes);
            for (auto& node : nodes) {
                node.tree_ = this;
            }
        }
        return *this;
    }

    /**
     * @brief Adds a child node to the specified parent node.
     *
     * @param parentIndex The index of the parent node.
     * @param value Optional value for the child node. Defaults to `std::nullopt`.
     * @return The index of the newly added child node.
     *
     * @throws std::out_of_range if the parentIndex is invalid.
     */
    size_t addChild(size_t parentIndex, std::optional<T> value = std::nullopt) {
        validateParentIndex(parentIndex);

        size_t childIndex = nodes.size();
        nodes.emplace_back(std::move(value), parentIndex, childIndex, this);  // Create and store child node
        nodes[parentIndex].childIndices_.push_back(childIndex);              // Link parent to child
        return childIndex;
    }

    /**
     * @brief Retrieves a reference to the node at the specified index.
     *
     * @param index The index of the node to retrieve.
     * @return Reference to the node.
     *
     * @throws std::out_of_range if the index is invalid.
     */
    TreeNode<T>& getNode(size_t index) {
        return nodes.at(index);  // Using at() for bounds checking
    }

    /**
     * @brief Retrieves a const reference to the node at the specified index.
     *
     * @param index The index of the node to retrieve.
     * @return Const reference to the node.
     *
     * @throws std::out_of_range if the index is invalid.
     */
    const TreeNode<T>& getNode(size_t index) const {
        return nodes.at(index);  // Using at() for bounds checking
    }

    /**
     * @brief Retrieves a reference to the root node.
     *
     * @return Reference to the root node.
     *
     * @throws std::out_of_range if the tree is empty.
     */
    TreeNode<T>& getRoot() {
        return nodes.at(0);  // Using at() for bounds checking
    }

    /**
     * @brief Retrieves a const reference to the root node.
     *
     * @return Const reference to the root node.
     *
     * @throws std::out_of_range if the tree is empty.
     */
    const TreeNode<T>& getRoot() const {
        return nodes.at(0);  // Using at() for bounds checking
    }

    /**
     * @brief Checks whether the specified node has a value.
     *
     * @param nodeIndex The index of the node to check.
     * @return `true` if the node has a value; otherwise, `false`.
     *
     * @throws std::out_of_range if the nodeIndex is invalid.
     */
    bool hasValue(size_t nodeIndex) const {
        return nodes.at(nodeIndex).value.has_value();
    }

    /**
     * @brief Retrieves the number of nodes in the tree.
     *
     * @return The number of nodes.
     */
    constexpr size_t size() const noexcept {
        return nodes.size();
    }

    // *** Iterator Methods ***
    auto begin() { return nodes.begin(); }
    auto end() { return nodes.end(); }
    auto rbegin() { return nodes.rbegin(); }
    auto rend() { return nodes.rend(); }

    const auto begin() const { return nodes.begin(); }
    const auto end() const { return nodes.end(); }
    const auto rbegin() const { return nodes.rbegin(); }
    const auto rend() const { return nodes.rend(); }

    // *** Traversal Iterator Methods ***
    auto pre_order_begin() { return TraversalIterator<PreOrderTraversalType, false>(); }
    auto pre_order_end()   { return TraversalIterator<PreOrderTraversalType, true>(); }
    auto pre_order_begin() const { return TraversalIterator<ConstPreOrderTraversalType, false>(); }
    auto pre_order_end()   const { return TraversalIterator<ConstPreOrderTraversalType, true>(); }

    auto post_order_begin() { return TraversalIterator<PostOrderTraversalType, false>(); }
    auto post_order_end()   { return TraversalIterator<PostOrderTraversalType, true>(); }
    auto post_order_begin() const { return TraversalIterator<ConstPostOrderTraversalType, false>(); }
    auto post_order_end()   const { return TraversalIterator<ConstPostOrderTraversalType, true>(); }

    auto bfs_begin() { return TraversalIterator<BFSTraversalType, false>(); }
    auto bfs_end()   { return TraversalIterator<BFSTraversalType, true>(); }
    auto bfs_begin() const { return TraversalIterator<ConstBFSTraversalType, false>(); }
    auto bfs_end()   const { return TraversalIterator<ConstBFSTraversalType, true>(); }

    auto bfs_rbegin() { return TraversalIterator<ReverseBFSTraversalType, false>(); }
    auto bfs_rend()   { return TraversalIterator<ReverseBFSTraversalType, true>(); }
    auto bfs_rbegin() const { return TraversalIterator<ConstReverseBFSTraversalType, false>(); }
    auto bfs_rend()   const { return TraversalIterator<ConstReverseBFSTraversalType, true>(); }

    auto pre_order_rbegin() { return TraversalIterator<ReversePreOrderTraversalType, false>(); }
    auto pre_order_rend()   { return TraversalIterator<ReversePreOrderTraversalType, true>(); }
    auto pre_order_rbegin() const { return TraversalIterator<ConstReversePreOrderTraversalType, false>(); }
    auto pre_order_rend()   const { return TraversalIterator<ConstReversePreOrderTraversalType, true>(); }

    /**
     * @brief Overloads the output stream operator to print the tree nodes.
     *
     * @param os The output stream.
     * @param tree The Tree to print.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Tree<T>& tree) {
        for (const auto& node : tree.nodes) {
            os << node << " ";
        }
        return os;
    }

private:
    std::vector<TreeNode<T>> nodes;  ///<  array to store all nodes

    /**
     * @brief Validates that the parent index is within the bounds of the nodes vector.
     *
     * @param parentIndex The index of the parent node to validate.
     *
     * @throws std::out_of_range if the parentIndex is invalid.
     */
    inline void validateParentIndex(size_t parentIndex) const {
        if (parentIndex >= nodes.size()) {
            throw std::out_of_range("Invalid parent index.");
        }
    }

    /**
     * @brief Internal helper function to create traversal iterators.
     *
     * This function consolidates the creation of traversal iterators for both const
     * and non-const instances, reducing code duplication.
     *
     * @tparam Traversal The traversal policy type.
     * @tparam IsEnd `false` to create a begin iterator, `true` to create an end iterator.
     * @tparam NodeType The type of node (`TreeNode<T>` or `const TreeNode<T>`).
     * @tparam TreeType The type of tree (`Tree<T>` or `const Tree<T>`).
     *
     * @return A TreeIterator configured for the specified traversal.
     */
    template <typename Traversal, bool IsEnd, typename NodeType = TreeNode<T>, typename TreeType = Tree<T>>
    TreeIterator<NodeType, TreeType, Traversal> TraversalIterator() {
        if constexpr (IsEnd) {
            return TreeIterator<NodeType, TreeType, Traversal>(this, static_cast<size_t>(-1));
        } else {
            return TreeIterator<NodeType, TreeType, Traversal>(this, nodes.empty() ? static_cast<size_t>(-1) : 0);
        }
    }

    /**
     * @brief Internal helper function to create const traversal iterators.
     *
     * This function consolidates the creation of const traversal iterators, reducing code duplication.
     *
     * @tparam Traversal The traversal policy type.
     * @tparam IsEnd `false` to create a begin iterator, `true` to create an end iterator.
     * @tparam NodeType The type of node (`const TreeNode<T>`).
     * @tparam TreeType The type of tree (`const Tree<T>`).
     *
     * @return A TreeIterator configured for the specified traversal.
     */
    template <typename Traversal, bool IsEnd, typename NodeType = const TreeNode<T>, typename TreeType = const Tree<T>>
    TreeIterator<NodeType, TreeType, Traversal> TraversalIterator() const {
        if constexpr (IsEnd) {
            return TreeIterator<NodeType, TreeType, Traversal>(this, static_cast<size_t>(-1));
        } else {
            return TreeIterator<NodeType, TreeType, Traversal>(this, nodes.empty() ? static_cast<size_t>(-1) : 0);
        }
    }
};

} // namespace vpr

#endif // TREE_HPP
