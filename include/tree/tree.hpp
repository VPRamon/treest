#ifndef TREE_HPP
#define TREE_HPP

#include "tree_node.hpp"
#include "graph_impl.hpp"
#include "postorder_iterator.hpp"
#include "preorder_iterator.hpp"
#include "bfs_iterator.hpp"
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
class Tree : public GraphImpl<tree::Node<T>> {
    using Base = GraphImpl<tree::Node<T>>;

    // Type aliases for traversal policies
    using PreOrderTraversalType = PreOrderTraversal<Tree<T>>;
    using ConstPreOrderTraversalType = PreOrderTraversal<const Tree<T>>;

    using PostOrderTraversalType = PostOrderTraversal<tree::Node<T>, Tree<T>>;
    using ConstPostOrderTraversalType = PostOrderTraversal<const tree::Node<T>, const Tree<T>>;

    using BFSTraversalType = BFSTraversal<Tree<T>>;
    using ConstBFSTraversalType = BFSTraversal<const Tree<T>>;
    using ReverseBFSTraversalType = ReverseBFSTraversal<Tree<T>>;
    using ConstReverseBFSTraversalType = ReverseBFSTraversal<const Tree<T>>;

    using ReversePreOrderTraversalType = ReversePreOrderTraversal<Tree<T>>;
    using ConstReversePreOrderTraversalType = ReversePreOrderTraversal<const Tree<T>>;

public:

    /**
     * @brief Constructs a GraphImpl with an optional initial capacity.
     *
     * @param initialCapacity Initial capacity for the nodes vector. Defaults to 16.
     */
    explicit Tree(std::optional<T> root = std::nullopt, size_t initialCapacity = 16) : Base(initialCapacity) {
        Base::emplace_node(0, std::move(root));
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
        tree::Node<T>& parent = Base::getNode(parentIndex);
        size_t id = Base::emplace_node(parentIndex, std::move(value));
        parent.addChild(id);
        return id;
    }

    const tree::Node<T>& getRoot() const {
        return Base::getNode(0);
    }

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

private:


    /**
     * @brief Internal helper function to create traversal iterators.
     *
     * This function consolidates the creation of traversal iterators for both const
     * and non-const instances, reducing code duplication.
     *
     * @tparam Traversal The traversal policy type.
     * @tparam IsEnd `false` to create a begin iterator, `true` to create an end iterator.
     * @tparam NodeType The type of node (`tree::Node<T>` or `const tree::Node<T>`).
     * @tparam TreeType The type of tree (`Tree<T>` or `const Tree<T>`).
     *
     * @return A TreeIterator configured for the specified traversal.
     */
    template <typename Traversal, bool IsEnd, typename NodeType = tree::Node<T>, typename TreeType = Tree<T>>
    TreeIterator<NodeType, TreeType, Traversal> TraversalIterator() {
        if constexpr (IsEnd) {
            return TreeIterator<NodeType, TreeType, Traversal>(this, static_cast<size_t>(-1));
        } else {
            return TreeIterator<NodeType, TreeType, Traversal>(this, Base::empty() ? static_cast<size_t>(-1) : 0);
        }
    }

    /**
     * @brief Internal helper function to create const traversal iterators.
     *
     * This function consolidates the creation of const traversal iterators, reducing code duplication.
     *
     * @tparam Traversal The traversal policy type.
     * @tparam IsEnd `false` to create a begin iterator, `true` to create an end iterator.
     * @tparam NodeType The type of node (`const tree::Node<T>`).
     * @tparam TreeType The type of tree (`const Tree<T>`).
     *
     * @return A TreeIterator configured for the specified traversal.
     */
    template <typename Traversal, bool IsEnd, typename NodeType = const tree::Node<T>, typename TreeType = const Tree<T>>
    TreeIterator<NodeType, TreeType, Traversal> TraversalIterator() const {
        if constexpr (IsEnd) {
            return TreeIterator<NodeType, TreeType, Traversal>(this, static_cast<size_t>(-1));
        } else {
            return TreeIterator<NodeType, TreeType, Traversal>(this, Base::empty() ? static_cast<size_t>(-1) : 0);
        }
    }
};

} // namespace vpr

#endif // TREE_HPP
