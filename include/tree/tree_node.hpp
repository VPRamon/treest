#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include "node_impl.hpp"

namespace vpr {

template <typename U> class GraphImpl;

namespace tree {

/**
 * @class Node
 * @brief Represents a tree node that inherits from NodeImpl and supports parent-child relationships.
 *
 * This class extends `NodeImpl` to represent a node in a tree structure. 
 * Each node maintains a reference to its parent and manages its children.
 *
 * @tparam T The type of the value stored in the node.
 */
template <typename T>
class Node : public NodeImpl<T> {
    using Base = NodeImpl<T>;
    friend GraphImpl<Node<T>>;

    size_t parent_id_;  ///< Index of the parent node

public:

    /**
     * @brief Constructs a tree node.
     *
     * @param index Index of the node.
     * @param parent_id Index of the parent node.
     * @param v Optional value stored in the node. Defaults to `std::nullopt`.
     */
    Node(size_t index, size_t parent_id, std::optional<T> v = std::nullopt)
        : Base(index, v), parent_id_(parent_id)
    {}

    /**
     * @brief Checks if the node is the root of the tree.
     *
     * @return true If the node is the root (index 0), false otherwise.
     */
    inline bool isRoot() const { return Base::index() == 0; }

    /**
     * @brief Checks if the node is a leaf (i.e., has no children).
     *
     * @return true If the node has no children, false otherwise.
     */
    inline bool isLeaf() const { return Base::isolated(); }

    /**
     * @brief Retrieves the number of children this node has.
     *
     * @return The number of children (degree of the node).
     */
    inline size_t nChildren() const { return Base::degree(); }

    /**
     * @brief Retrieves the index of the parent node.
     *
     * @return The parent node's index.
     */
    inline size_t parentId() const { return parent_id_; }

    /**
     * @brief Gets a constant reference to the list of children.
     *
     * @return const std::vector<size_t>& The vector of child node indices.
     */
    inline const auto& getChildren() const { return Base::edges(); }

    /**
     * @brief Adds a child to this node.
     *
     * @param child_id The index of the child node.
     */
    inline void addChild(size_t child_id) { Base::addEdge(child_id); }

};

} // namespace tree
} // namespace vpr

#endif // TREE_NODE_HPP
