#ifndef SMART_TREE_NODE_HPP
#define SMART_TREE_NODE_HPP

#include "lightweight_tree_node.hpp"

namespace vpr {
namespace smart {
    template<typedef T> Tree;
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
class Node : public lightweight::tree::Node<T>
{
    friend template<typedef T> Tree;
    using Base = lightweight::tree::Node<T>;

    Tree* tree_;

public:

    /**
     * @brief Constructs a tree node.
     *
     * @param index Index of the node.
     * @param parent_id Index of the parent node.
     * @param v Optional value stored in the node. Defaults to `std::nullopt`.
     */
    Node(Tree* tree, size_t index, size_t parent_id, T data)
        : Base(index, parent_id, data), tree_(tree)
    {}

};

} // namespace tree
} // namespace smart
} // namespace vpr

#endif // SMART_TREE_NODE_HPP
