#ifndef TREE_IMPLEMENTATION_HPP
#define TREE_IMPLEMENTATION_HPP

#include "lightweight_tree_node.hpp"
#include "graph_template.hpp"
#include "postorder_iterator.hpp"
#include "preorder_iterator.hpp"
#include "bfs_iterator.hpp"

namespace vpr {
namespace templates {

/**
 * @class Tree
 * @brief A tree structure that extends GraphImpl, providing node management and various traversal methods.
 *
 * This class represents a tree, which is a hierarchical data structure. Each node has a single parent (except the root),
 * and can have multiple children. The tree supports different types of traversal, such as pre-order, post-order, and breadth-first.
 *
 * @tparam T The type of value stored in each node.
 */
template <typename Node_,
         template <typename, typename> class Container = std::vector,
         typename Allocator = std::allocator<typename Node_::DataType>>
class TreeImpl : public GraphTemplate<Node_, Container, Allocator> {
public:
    using Node = Node_;

private:
    using Base = GraphTemplate<Node, Container, Allocator>;
    using T = typename Node::DataType;
    // Type aliases for traversal policies
    using PreOrderTraversalType = PreOrderTraversal<TreeImpl>;
    using ConstPreOrderTraversalType = PreOrderTraversal<const TreeImpl>;

    using PostOrderTraversalType = PostOrderTraversal<Node, TreeImpl>;
    using ConstPostOrderTraversalType = PostOrderTraversal<const Node, const TreeImpl>;

    using BFSTraversalType = BFSTraversal<TreeImpl>;
    using ConstBFSTraversalType = BFSTraversal<const TreeImpl>;
    using ReverseBFSTraversalType = ReverseBFSTraversal<TreeImpl>;
    using ConstReverseBFSTraversalType = ReverseBFSTraversal<const TreeImpl>;

    using ReversePreOrderTraversalType = ReversePreOrderTraversal<TreeImpl>;
    using ConstReversePreOrderTraversalType = ReversePreOrderTraversal<const TreeImpl>;

protected:

    TreeImpl() = default;

public:

    /**
     * @brief Constructs a tree with an optional root value and an initial node capacity.
     *
     * @param root Optional value for the root node. Defaults to `std::nullopt`.
     * @param initial_capacity Initial capacity for the tree's node vector. Defaults to 16.
     */
    explicit TreeImpl(T root, size_t initial_capacity = 16) : Base(initial_capacity) {
        Base::emplace_node(0, std::move(root));
    }

    /**
     * @brief Adds a child node to the specified parent node.
     *
     * @param parent_index The index of the parent node.
     * @param value Optional value for the child node. Defaults to `std::nullopt`.
     * @return The index of the newly added child node.
     *
     * @throws std::out_of_range if the parentIndex is invalid.
     */
    size_t addChild(size_t parent_index, T value) {
        Base::validateIndex(parent_index);
        size_t id = Base::emplace_node(parent_index, std::move(value));
        Base::addEdge(parent_index, id);
        return id;
    }

    /**
     * @brief Retrieves the root node of the tree.
     *
     * @return A constant reference to the root node.
     */
    inline const Node& getRoot() const { return Base::getNode(0); }

    // *** Traversal Iterator Methods ***
    inline auto pre_order_begin() { return TraversalIterator<PreOrderTraversalType, false>(); }
    inline auto pre_order_end()   { return TraversalIterator<PreOrderTraversalType, true>(); }
    inline auto pre_order_begin() const { return TraversalIterator<ConstPreOrderTraversalType, false>(); }
    inline auto pre_order_end()   const { return TraversalIterator<ConstPreOrderTraversalType, true>(); }

    inline auto post_order_begin() { return TraversalIterator<PostOrderTraversalType, false>(); }
    inline auto post_order_end()   { return TraversalIterator<PostOrderTraversalType, true>(); }
    inline auto post_order_begin() const { return TraversalIterator<ConstPostOrderTraversalType, false>(); }
    inline auto post_order_end()   const { return TraversalIterator<ConstPostOrderTraversalType, true>(); }

    inline auto bfs_begin() { return TraversalIterator<BFSTraversalType, false>(); }
    inline auto bfs_end()   { return TraversalIterator<BFSTraversalType, true>(); }
    inline auto bfs_begin() const { return TraversalIterator<ConstBFSTraversalType, false>(); }
    inline auto bfs_end()   const { return TraversalIterator<ConstBFSTraversalType, true>(); }

    inline auto bfs_rbegin() { return TraversalIterator<ReverseBFSTraversalType, false>(); }
    inline auto bfs_rend()   { return TraversalIterator<ReverseBFSTraversalType, true>(); }
    inline auto bfs_rbegin() const { return TraversalIterator<ConstReverseBFSTraversalType, false>(); }
    inline auto bfs_rend()   const { return TraversalIterator<ConstReverseBFSTraversalType, true>(); }

    inline auto pre_order_rbegin() { return TraversalIterator<ReversePreOrderTraversalType, false>(); }
    inline auto pre_order_rend()   { return TraversalIterator<ReversePreOrderTraversalType, true>(); }
    inline auto pre_order_rbegin() const { return TraversalIterator<ConstReversePreOrderTraversalType, false>(); }
    inline auto pre_order_rend()   const { return TraversalIterator<ConstReversePreOrderTraversalType, true>(); }

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
    template <typename Traversal, bool IsEnd, typename NodeType = Node, typename TreeType = TreeImpl>
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
    template <typename Traversal, bool IsEnd, typename NodeType = const Node, typename TreeType = const TreeImpl>
    TreeIterator<NodeType, TreeType, Traversal> TraversalIterator() const {
        if constexpr (IsEnd) {
            return TreeIterator<NodeType, TreeType, Traversal>(this, static_cast<size_t>(-1));
        } else {
            return TreeIterator<NodeType, TreeType, Traversal>(this, Base::empty() ? static_cast<size_t>(-1) : 0);
        }
    }
};

} // namespace lightweight
} // namespace vpr

#endif // TREE_HPP
