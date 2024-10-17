#pragma once

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
 */
template <typename Node_,
         typename Container = std::vector<Node_>>
class Tree : public Graph<Container> {
public:
    using Node = Node_;

private:
    using Base = Graph<Container>;
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
     */
    explicit Tree(T root, size_t initial_capacity = 16) : Base(initial_capacity) {
        Base::emplace_node(0, std::move(root));
    }

    /**
     * @brief Adds a child node to the specified parent node.
     *
     */
    size_t addChild(size_t parent_index, T value) {
        Base::validateIndex(parent_index);
        size_t id = Base::emplace_node(parent_index, std::move(value));
        Base::addEdge(parent_index, id);
        return id;
    }

    inline const Node& getRoot() const { return Base::getNode(0); }

    // *** Traversal Iterator Methods ***
    inline auto pre_order_begin() { return BeginTraversalIterator<PreOrderTraversalType>(); }
    inline auto pre_order_end()   { return EndTraversalIterator<PreOrderTraversalType>(); }
    inline auto pre_order_begin() const { return BeginTraversalIterator<ConstPreOrderTraversalType>(); }
    inline auto pre_order_end()   const { return EndTraversalIterator<ConstPreOrderTraversalType>(); }

    inline auto post_order_begin() { return BeginTraversalIterator<PostOrderTraversalType>(); }
    inline auto post_order_end()   { return EndTraversalIterator<PostOrderTraversalType>(); }
    inline auto post_order_begin() const { return BeginTraversalIterator<ConstPostOrderTraversalType>(); }
    inline auto post_order_end()   const { return EndTraversalIterator<ConstPostOrderTraversalType>(); }

    inline auto bfs_begin() { return BeginTraversalIterator<BFSTraversalType>(); }
    inline auto bfs_end()   { return EndTraversalIterator<BFSTraversalType>(); }
    inline auto bfs_begin() const { return BeginTraversalIterator<ConstBFSTraversalType>(); }
    inline auto bfs_end()   const { return EndTraversalIterator<ConstBFSTraversalType>(); }

    inline auto bfs_rbegin() { return BeginTraversalIterator<ReverseBFSTraversalType>(); }
    inline auto bfs_rend()   { return EndTraversalIterator<ReverseBFSTraversalType>(); }
    inline auto bfs_rbegin() const { return BeginTraversalIterator<ConstReverseBFSTraversalType>(); }
    inline auto bfs_rend()   const { return EndTraversalIterator<ConstReverseBFSTraversalType>(); }

    inline auto pre_order_rbegin() { return BeginTraversalIterator<ReversePreOrderTraversalType>(); }
    inline auto pre_order_rend()   { return EndTraversalIterator<ReversePreOrderTraversalType>(); }
    inline auto pre_order_rbegin() const { return BeginTraversalIterator<ConstReversePreOrderTraversalType>(); }
    inline auto pre_order_rend()   const { return EndTraversalIterator<ConstReversePreOrderTraversalType>(); }

private:

    /**
     * @brief Helper method to create traversal iterators.
     *
     */
    template <typename Traversal>
    TreeIterator<Node, Tree, Traversal> EndTraversalIterator() {
        return TreeIterator<Node, Tree, Traversal>(this, static_cast<size_t>(-1));
    }

    /**
     * @brief Helper method to create traversal iterators (begin).
     *
     */
    template <typename Traversal>
    TreeIterator<Node, Tree, Traversal> BeginTraversalIterator() {
        return TreeIterator<Node, Tree, Traversal>(
            this, Base::empty() ? static_cast<size_t>(-1) : 0
        );
    }

    /**
     * @brief Helper method to create const traversal iterators.
     *
     */
    template <typename Traversal>
    TreeIterator<const Node, const Tree, Traversal> EndTraversalIterator() const {
        return TreeIterator<const Node, const Tree, Traversal>(this, static_cast<size_t>(-1));
    }

    /**
     * @brief Helper method to create const traversal iterators (begin).
     *
     */
    template <typename Traversal>
    TreeIterator<const Node, const Tree, Traversal> BeginTraversalIterator() const {
        return TreeIterator<const Node, const Tree, Traversal>(
            this, Base::empty() ? static_cast<size_t>(-1) : 0
        );
    }
};

} // namespace templates
} // namespace vpr
