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
 * @brief A Tree data structure template class.
 *
 * This class represents a tree structure where each node stores a value of type `T`.
 * It provides methods to manipulate the tree, including adding child nodes, retrieving
 * the root node, and performing various traversals (pre-order, post-order, breadth-first search).
 *
 * @tparam Node_ Type of the node in the tree, which should have a nested DataType.
 * @tparam Container The container type used to store edges, defaulting to std::vector.
 * @tparam Allocator The allocator type used for managing memory, defaulting to std::allocator.
 */
template <typename Node_,
         template <typename, typename> class Container = std::vector,
         typename Allocator = std::allocator<Node_>>
class Tree : public Graph<Node_, Container, Allocator> {
public:
    using Node = Node_;

private:
    using Base = Graph<Node, Container, Allocator>;
    using T = typename Node::DataType;
    // Type aliases for traversal policies
    using PreOrderTraversalType = PreOrderTraversal<Tree>;
    using ConstPreOrderTraversalType = PreOrderTraversal<const Tree>;

    using PostOrderTraversalType = PostOrderTraversal<Node, Tree>;
    using ConstPostOrderTraversalType = PostOrderTraversal<const Node, const Tree>;

    using BFSTraversalType = BFSTraversal<Tree>;
    using ConstBFSTraversalType = BFSTraversal<const Tree>;
    using ReverseBFSTraversalType = ReverseBFSTraversal<Tree>;
    using ConstReverseBFSTraversalType = ReverseBFSTraversal<const Tree>;

    using ReversePreOrderTraversalType = ReversePreOrderTraversal<Tree>;
    using ConstReversePreOrderTraversalType = ReversePreOrderTraversal<const Tree>;

protected:

    Tree() = default;

public:

    /**
     * @brief Constructs a tree with a root value and an initial capacity for nodes.
     *
     * Creates a tree and initializes it with a root node containing the specified value.
     * Optionally, the initial capacity of the underlying container can be specified to
     * avoid reallocation overhead.
     *
     * @param root The value to be stored in the root node.
     * @param initial_capacity The initial capacity for the tree's container. Defaults to 16.
     */
    explicit Tree(T root, size_t initial_capacity = 16) : Base(initial_capacity) {
        Base::emplace_node(0, std::move(root));
    }

    /**
     * @brief Adds a child node to the specified parent node.
     *
     * This method adds a new node with the specified value as a child of the parent node
     * identified by `parent_index`. The new node is connected to the parent node via an edge.
     *
     * @param parent_index The index of the parent node.
     * @param value The value to be stored in the child node.
     * @return The index of the newly created child node.
     */
    size_t addChild(size_t parent_index, T value) {
        Base::validateIndex(parent_index);
        size_t id = Base::emplace_node(parent_index, std::move(value));
        Base::addEdge(parent_index, id);
        return id;
    }


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
     * @brief Helper method to create traversal iterators.
     *
     * Creates an iterator for a specific traversal type. It is a helper function used
     * internally to generate both begin and end iterators for different traversal strategies.
     *
     * @tparam Traversal The type of traversal strategy (pre-order, post-order, BFS, etc.).
     * @tparam IsEnd Boolean flag indicating whether this is the end iterator.
     * @return A `TreeIterator` for the specified traversal.
     */
    template <typename Traversal, bool IsEnd>
    typename std::enable_if<IsEnd, TreeIterator<Node, Tree, Traversal>>::type
    TraversalIterator() {
        return TreeIterator<Node, Tree, Traversal>(this, static_cast<size_t>(-1));
    }

    /**
     * @brief Helper method to create traversal iterators (begin).
     *
     * This method creates a non-end traversal iterator. It is specialized based on
     * the traversal strategy.
     *
     * @tparam Traversal The type of traversal strategy.
     * @tparam IsEnd Whether this is an end iterator.
     * @return A traversal iterator that starts at the beginning.
     */
    template <typename Traversal, bool IsEnd>
    typename std::enable_if<!IsEnd, TreeIterator<Node, Tree, Traversal>>::type
    TraversalIterator() {
        return TreeIterator<Node, Tree, Traversal>(
            this, Base::empty() ? static_cast<size_t>(-1) : 0
        );
    }

    /**
     * @brief Helper method to create const traversal iterators.
     *
     * Creates a constant traversal iterator for a specific traversal type.
     * It is used internally to handle both begin and end traversal cases.
     *
     * @tparam Traversal The type of traversal strategy (pre-order, post-order, BFS, etc.).
     * @tparam IsEnd Boolean flag indicating whether this is the end iterator.
     * @return A constant `TreeIterator` for the specified traversal.
     */
    template <typename Traversal, bool IsEnd>
    typename std::enable_if<IsEnd, TreeIterator<const Node, const Tree, Traversal>>::type
    TraversalIterator() const {
        return TreeIterator<const Node, const Tree, Traversal>(this, static_cast<size_t>(-1));
    }

    /**
     * @brief Helper method to create const traversal iterators (begin).
     *
     * This method creates a constant, non-end traversal iterator. It is specialized based
     * on the traversal strategy.
     *
     * @tparam Traversal The type of traversal strategy.
     * @tparam IsEnd Whether this is an end iterator.
     * @return A constant traversal iterator that starts at the beginning.
     */
    template <typename Traversal, bool IsEnd>
    typename std::enable_if<!IsEnd, TreeIterator<const Node, const Tree, Traversal>>::type
    TraversalIterator() const {
        return TreeIterator<const Node, const Tree, Traversal>(
            this, Base::empty() ? static_cast<size_t>(-1) : 0
        );
    }
};

} // namespace lightweight
} // namespace vpr

#endif // TREE_HPP
