#ifndef LIGHTWEIGHT_TREE_NODE_HPP
#define LIGHTWEIGHT_TREE_NODE_HPP

#include "node_template.hpp"
#include <vector>

namespace vpr {
namespace lightweight {
namespace tree {

/**
 * @brief A specialized Node class with additional parent tracking.
 *
 * This class extends the functionality of the base `templates::Node` class by adding the concept of
 * a parent node. It stores the parent node's index and provides utility functions to check whether
 * the node is a root, a leaf, and retrieve the number of children.
 *
 * @tparam T The type of data stored in the node.
 */
template <typename T>
class Node : public templates::Node<T, std::vector<size_t>> {
    using Base = templates::Node<T, std::vector<size_t>>;

    size_t parent_id_;  ///< Index of the parent node.

public:

    /**
     * @brief Constructs a Node object.
     *
     * This constructor initializes a node with an index, a parent ID, and associated data.
     *
     * @param index The index of the node in the graph.
     * @param parent_id The index of the parent node.
     * @param data The value of type `T` stored in the node.
     */
    Node(size_t index, size_t parent_id, T data)
        : Base(index, data), parent_id_(parent_id)
    {}

    /**
     * @brief Checks if the node is the root node.
     *
     * A node is considered the root if its index is 0.
     *
     * @return `true` if the node is the root, `false` otherwise.
     */
    inline bool isRoot() const { return Base::index() == 0; }

    /**
     * @brief Checks if the node is a leaf node.
     *
     * A node is considered a leaf if it has no children (i.e., it is no outgoing edges).
     *
     * @return `true` if the node is a leaf, `false` otherwise.
     */
    inline bool isLeaf() const { return Base::isolated(); }

    /**
     * @brief Retrieves the number of children of the node.
     *
     * The number of children corresponds to the degree of the node, i.e., the number of outgoing edges.
     *
     * @return The number of children.
     */
    inline size_t nChildren() const { return Base::degree(); }

    /**
     * @brief Gets the parent node's index.
     *
     * This method returns the index of the parent node.
     *
     * @return The index of the parent node.
     */
    inline size_t parentId() const { return parent_id_; }

};


} // namespace tree
} // namespace lightweight
} // namespace vpr

#endif // LIGHTWEIGHT_TREE_NODE_HPP
