#ifndef SMART_TREE_NODE_HPP
#define SMART_TREE_NODE_HPP

#include "lightweight_tree_node.hpp"

namespace vpr {
namespace smart {
    template<typename T> class Tree;
namespace tree {

/**
 * @brief Represents a node in the smart tree, which extends the lightweight tree node.
 * 
 * The `Node` class is responsible for managing node-specific operations, such as adding 
 * child nodes and retrieving child nodes. It maintains a pointer to its parent tree and 
 * uses this pointer to add children or access other nodes in the tree.
 *
 * @tparam T The type of data stored in the node.
 */
template <typename T>
class Node : public lightweight::tree::Node<T>
{
    // Allows the Tree class to access private/protected members of Node.
    friend Tree<T>;

    using Base = lightweight::tree::Node<T>;

    Tree<T>* tree_;  ///< Pointer to the tree that the node belongs to.

public:

    /**
     * @brief Constructs a Node object.
     * 
     * This constructor initializes a node with a given index, parent ID, and data.
     * It also associates the node with the tree it belongs to.
     *
     * @param index The index of the node in the tree.
     * @param tree Pointer to the tree that the node belongs to.
     * @param parent_id The index of the parent node.
     * @param data The value of type `T` stored in the node.
     */
    Node(size_t index, Tree<T>* tree, size_t parent_id, T data)
        : Base(index, parent_id, data), tree_(tree)
    {}

    /**
     * @brief Adds a child node to this node.
     * 
     * This method creates a new child node with the given data and adds it as a child 
     * of this node. It uses the tree's `addChild` method to create the new node.
     *
     * @param data The value of type `T` to be stored in the child node.
     * @return The index of the newly added child node.
     */
    size_t addChild(T data) {
        return tree_->addChild(Base::index(), std::move(data));
    }

    /**
     * @brief Retrieves the children of this node.
     * 
     * This method returns a vector of references to the child nodes of this node.
     *
     * @return A vector of references to the children of this node.
     */
    std::vector<std::reference_wrapper<Node>> getChildren() {
        std::vector<std::reference_wrapper<Node>> children;
        children.reserve(Base::nChildren());
        for (size_t id : Base::edges()) {
            children.emplace_back(tree_->getNode(id));
        }
        return children;
    }

    /**
     * @brief Retrieves the children of this node (const version).
     * 
     * This method returns a vector of const references to the child nodes of this node.
     *
     * @return A vector of const references to the children of this node.
     */
    std::vector<std::reference_wrapper<const Node>> getChildren() const {
        std::vector<std::reference_wrapper<const Node>> children;
        children.reserve(Base::nChildren());
        for (size_t id : Base::edges()) {
            children.emplace_back(tree_->getNode(id));
        }
        return children;
    }
};

} // namespace tree
} // namespace smart
} // namespace vpr

#endif // SMART_TREE_NODE_HPP

