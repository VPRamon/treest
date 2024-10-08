#ifndef SMART_TREE_HPP
#define SMART_TREE_HPP

#include "smart_tree_node.hpp"
#include "tree_template.hpp"

namespace vpr {
namespace smart {

/**
 * @class Tree
 * @brief A tree structure that extends Tree, providing node management and various traversal methods.
 *
 * This class represents a tree, which is a hierarchical data structure. Each node has a single parent (except the root),
 * and can have multiple children. The tree supports different types of traversal, such as pre-order, post-order, and breadth-first.
 *
 * @tparam T The type of value stored in each node.
 */
template <typename T>
class Tree : public templates::Tree<tree::Node<T>, std::vector> {
    using Base = templates::Tree<tree::Node<T>, std::vector>;
public:
    using Node = tree::Node<T>;

    /**
     * @brief Constructs a tree with an optional root value and an initial node capacity.
     *
     * @param root Optional value for the root node. Defaults to `std::nullopt`.
     * @param initial_capacity Initial capacity for the tree's node vector. Defaults to 16.
     */
    explicit Tree(T root, size_t initial_capacity = 16) {
        this->nodes_.reserve(initial_capacity);
        Base::emplace_node(this, 0, std::move(root));
    }

    /**
     * @brief Copy constructor. Performs a deep copy of the graph.
     *
     * @param other The Tree to copy from.
     */
    Tree(const Tree& other) : Base(other)
    { syncNodes(); }

    /**
     * @brief Move constructor. Transfers ownership of the graph from another Tree.
     *
     * @param other The Tree to move from.
     */
    Tree(Tree&& other) noexcept : Base(other)
    { syncNodes(); }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the graph.
     *
     * @param other The Tree to copy from.
     * @return Reference to the assigned Tree.
     */
    Tree& operator=(const Tree& other) {
        if (this != &other) {
            Base::nodes_ = other.nodes_;
            syncNodes();
        }
        return *this;
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
        size_t id = Base::emplace_node(this, parent_index, std::move(value));
        Base::addEdge(parent_index, id);
        return id;
    }

private:

    void syncNodes() {
        for (Node& node : Base::nodes_) {
            node.tree_ = this;
        }
    }
};

} // namespace smart
} // namespace vpr

#endif // SMART_TREE_HPP
