#ifndef FLAT_TREE_HPP
#define FLAT_TREE_HPP

#include "flat_tree_node.hpp"
#include "flat_tree_iterator.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <type_traits>

namespace vpr {

/**
 * @brief Represents a flat tree structure using a vector to store nodes.
 *
 * The FlatTree class manages a collection of nodes stored in a flat vector,
 * allowing efficient traversal and manipulation of the tree structure.
 *
 * @tparam T The type of the value stored in each node.
 */
template <typename T>
class FlatTree {

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

public:
    // Type aliases for traversal policies
    using PreOrderTraversalType = PreOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
    using ConstPreOrderTraversalType = PreOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;

    using PostOrderTraversalType = PostOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
    using ConstPostOrderTraversalType = PostOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;

    using LevelOrderTraversalType = LevelOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
    using ConstLevelOrderTraversalType = LevelOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;

    using ReversePreOrderTraversalType = ReversePreOrderTraversal<FlatTreeNode<T>, FlatTree<T>>;
    using ConstReversePreOrderTraversalType = ReversePreOrderTraversal<const FlatTreeNode<T>, const FlatTree<T>>;

    /**
     * @brief Constructs a FlatTree with an optional root value and initial capacity.
     *
     * @param value Optional value for the root node. Defaults to `std::nullopt`.
     * @param initialCapacity Initial capacity for the nodes vector. Defaults to 16.
     */
    explicit FlatTree(std::optional<T> value = std::nullopt, size_t initialCapacity = 16) {
        nodes.reserve(initialCapacity);
        nodes.emplace_back(std::move(value), static_cast<size_t>(-1), 0, this);  // Root node with no parent
    }

    /**
     * @brief Copy constructor. Performs a deep copy of the tree.
     *
     * @param other The FlatTree to copy from.
     */
    FlatTree(const FlatTree& other) : nodes(other.nodes) {
        for (auto& node : nodes) {
            node.tree_ = this;
        }
    }

    /**
     * @brief Move constructor. Transfers ownership of the tree from another FlatTree.
     *
     * @param other The FlatTree to move from.
     */
    FlatTree(FlatTree&& other) noexcept : nodes(std::move(other.nodes)) {
        for (auto& node : nodes) {
            node.tree_ = this;
        }
    }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the tree.
     *
     * @param other The FlatTree to copy from.
     * @return Reference to the assigned FlatTree.
     */
    FlatTree& operator=(const FlatTree& other) {
        if (this != &other) {
            nodes = other.nodes;
            for (auto& node : nodes) {
                node.tree_ = this;
            }
        }
        return *this;
    }

    /**
     * @brief Move assignment operator. Transfers ownership of the tree from another FlatTree.
     *
     * @param other The FlatTree to move from.
     * @return Reference to the assigned FlatTree.
     */
    FlatTree& operator=(FlatTree&& other) noexcept {
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
    FlatTreeNode<T>& getNode(size_t index) {
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
    const FlatTreeNode<T>& getNode(size_t index) const {
        return nodes.at(index);  // Using at() for bounds checking
    }

    /**
     * @brief Retrieves a reference to the root node.
     *
     * @return Reference to the root node.
     *
     * @throws std::out_of_range if the tree is empty.
     */
    FlatTreeNode<T>& getRoot() {
        return nodes.at(0);  // Using at() for bounds checking
    }

    /**
     * @brief Retrieves a const reference to the root node.
     *
     * @return Const reference to the root node.
     *
     * @throws std::out_of_range if the tree is empty.
     */
    const FlatTreeNode<T>& getRoot() const {
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

    auto bfs_begin() { return TraversalIterator<LevelOrderTraversalType, false>(); }
    auto bfs_end()   { return TraversalIterator<LevelOrderTraversalType, true>(); }
    auto bfs_begin() const { return TraversalIterator<ConstLevelOrderTraversalType, false>(); }
    auto bfs_end()   const { return TraversalIterator<ConstLevelOrderTraversalType, true>(); }

    auto pre_order_rbegin() { return TraversalIterator<ReversePreOrderTraversalType, false>(); }
    auto pre_order_rend()   { return TraversalIterator<ReversePreOrderTraversalType, true>(); }
    auto pre_order_rbegin() const { return TraversalIterator<ConstReversePreOrderTraversalType, false>(); }
    auto pre_order_rend()   const { return TraversalIterator<ConstReversePreOrderTraversalType, true>(); }

    /**
     * @brief Overloads the output stream operator to print the tree nodes.
     *
     * @param os The output stream.
     * @param tree The FlatTree to print.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const FlatTree<T>& tree) {
        for (const auto& node : tree.nodes) {
            os << node << " ";
        }
        return os;
    }

private:
    std::vector<FlatTreeNode<T>> nodes;  ///< Flat array to store all nodes

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
     * @tparam NodeType The type of node (`FlatTreeNode<T>` or `const FlatTreeNode<T>`).
     * @tparam TreeType The type of tree (`FlatTree<T>` or `const FlatTree<T>`).
     *
     * @return A FlatTreeIterator configured for the specified traversal.
     */
    template <typename Traversal, bool IsEnd, typename NodeType = FlatTreeNode<T>, typename TreeType = FlatTree<T>>
    FlatTreeIterator<NodeType, TreeType, Traversal> TraversalIterator() {
        if constexpr (IsEnd) {
            return FlatTreeIterator<NodeType, TreeType, Traversal>(this, static_cast<size_t>(-1));
        } else {
            return FlatTreeIterator<NodeType, TreeType, Traversal>(this, nodes.empty() ? static_cast<size_t>(-1) : 0);
        }
    }

    /**
     * @brief Internal helper function to create const traversal iterators.
     *
     * This function consolidates the creation of const traversal iterators, reducing code duplication.
     *
     * @tparam Traversal The traversal policy type.
     * @tparam IsEnd `false` to create a begin iterator, `true` to create an end iterator.
     * @tparam NodeType The type of node (`const FlatTreeNode<T>`).
     * @tparam TreeType The type of tree (`const FlatTree<T>`).
     *
     * @return A FlatTreeIterator configured for the specified traversal.
     */
    template <typename Traversal, bool IsEnd, typename NodeType = const FlatTreeNode<T>, typename TreeType = const FlatTree<T>>
    FlatTreeIterator<NodeType, TreeType, Traversal> TraversalIterator() const {
        if constexpr (IsEnd) {
            return FlatTreeIterator<NodeType, TreeType, Traversal>(this, static_cast<size_t>(-1));
        } else {
            return FlatTreeIterator<NodeType, TreeType, Traversal>(this, nodes.empty() ? static_cast<size_t>(-1) : 0);
        }
    }
};

} // namespace vpr

#endif // FLAT_TREE_HPP
