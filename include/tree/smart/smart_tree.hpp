#ifndef SMART_TREE_HPP
#define SMART_TREE_HPP

#include "smart_tree_node.hpp"
#include "tree_template.hpp"

namespace vpr {
namespace smart {

/**
 * @brief Represents a smart tree structure with nodes that can manage their children and interact with the tree.
 * 
 * The `Tree` class manages a collection of `Node` objects and provides methods for adding child nodes, 
 * copying the tree, and moving the tree. It ensures that each node is aware of the tree it belongs to 
 * through a `syncNodes` function.
 *
 * @tparam T The type of data stored in the nodes of the tree.
 */
template <typename T>
class Tree : public templates::Tree<std::vector<tree::Node<T>>> {

    using Base = templates::Tree<std::vector<tree::Node<T>>>;

public:

    /**
     * @brief Constructs a Tree with an initial root node and an optional initial capacity.
     * 
     * This constructor creates a tree with a root node and reserves space for nodes based on 
     * the provided initial capacity.
     *
     * @param root The value of type `T` to be stored in the root node.
     * @param initial_capacity The initial capacity for the tree's node storage. Defaults to 16.
     */
    explicit Tree(T root, size_t initial_capacity = 16) {
        this->nodes_.reserve(initial_capacity);
        Base::emplace_node(this, 0, std::move(root));
    }

    /**
     * @brief Copy constructor for the Tree.
     * 
     * This constructor creates a copy of the given tree and synchronizes the nodes
     * to point to the correct tree instance.
     *
     * @param other The tree to be copied.
     */
    Tree(const Tree& other) : Base(other)
    { syncNodes(); }

    /**
     * @brief Move constructor for the Tree.
     * 
     * This constructor moves the contents of another tree into this one and synchronizes the nodes.
     *
     * @param other The tree to be moved.
     */
    Tree(Tree&& other) noexcept : Base(other)
    { syncNodes(); }

    /**
     * @brief Copy assignment operator for the Tree.
     * 
     * This operator allows assigning the contents of one tree to another. It copies all nodes 
     * and synchronizes them to the new tree instance.
     *
     * @param other The tree to be copied.
     * @return A reference to the current tree after the copy operation.
     */
    Tree& operator=(const Tree& other) {
        if (this != &other) {
            Base::nodes_ = other.nodes_;
            syncNodes();
        }
        return *this;
    }

    /**
     * @brief Adds a child node to a parent node.
     * 
     * This method creates a new node with the given data and adds it as a child 
     * to the node with the specified parent index.
     *
     * @param parent_index The index of the parent node.
     * @param value The value of type `T` to be stored in the child node.
     * @return The index of the newly added child node.
     */
    size_t addChild(size_t parent_index, T value) {
        Base::validateIndex(parent_index);
        size_t id = Base::emplace_node(this, parent_index, std::move(value));
        Base::addEdge(parent_index, id);
        return id;
    }

    inline auto& getRoot() { return Base::getNode(0); }
    inline auto& getRoot() const { return Base::getNode(0); }

private:

    /**
     * @brief Synchronizes the nodes to ensure they reference the correct tree.
     * 
     * This method updates the internal pointer of each node to point to the current tree instance.
     * It is used after copying or moving the tree to maintain proper node-tree relationships.
     */
    void syncNodes() {
        for (auto& node : Base::nodes_) {
            node.tree_ = this;
        }
    }
};

} // namespace smart
} // namespace vpr

#endif // SMART_TREE_HPP
