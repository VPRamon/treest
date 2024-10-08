#ifndef LIGHTWEIGHT_TREE_NODE_HPP
#define LIGHTWEIGHT_TREE_NODE_HPP

#include "node_template.hpp"

namespace vpr {
namespace lightweight {
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
class Node : public templates::Node<T, std::vector> {
    using Base = templates::Node<T, std::vector>;

    size_t parent_id_;  ///< Index of the parent node

public:

    /**
     * @brief Constructs a tree node.
     *
     * @param index Index of the node.
     * @param parent_id Index of the parent node.
     * @param v Optional value stored in the node. Defaults to `std::nullopt`.
     */
    Node(size_t index, size_t parent_id, T data)
        : Base(index, data), parent_id_(parent_id)
    {}

    /**
     * @brief Checks if the node is the root of the tree.
     *
     * @return true If the node is the root (index 0), false otherwise.
     */
    bool isRoot() const { return Base::index() == 0; }

    /**
     * @brief Checks if the node is a leaf (i.e., has no children).
     *
     * @return true If the node has no children, false otherwise.
     */
    bool isLeaf() const { return Base::isolated(); }

    /**
     * @brief Retrieves the number of children this node has.
     *
     * @return The number of children (degree of the node).
     */
    size_t nChildren() const { return Base::degree(); }

    /**
     * @brief Retrieves the index of the parent node.
     *
     * @return The parent node's index.
     */
    size_t parentId() const { return parent_id_; }

    /**
     * @brief Gets a constant reference to the list of children.
     *
     * @return const std::vector<size_t>& The vector of child node indices.
     */
    //const auto& getChildren() const { return Base::edges(); }

};

} // namespace tree
} // namespace lightweight
} // namespace vpr

#endif // LIGHTWEIGHT_TREE_NODE_HPP
