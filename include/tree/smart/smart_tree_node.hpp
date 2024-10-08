#ifndef SMART_TREE_NODE_HPP
#define SMART_TREE_NODE_HPP

#include "lightweight_tree_node.hpp"

namespace vpr {
namespace smart {
    template<typename T> class Tree;
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
    friend Tree<T>;

    using Base = lightweight::tree::Node<T>;

    Tree<T>* tree_;

public:

    /**
     * @brief Constructs a tree node.
     *
     * @param index Index of the node.
     * @param parent_id Index of the parent node.
     * @param v Optional value stored in the node. Defaults to `std::nullopt`.
     */
    Node(size_t index, Tree<T>* tree, size_t parent_id, T data)
        : Base(index, parent_id, data), tree_(tree)
    {}

    size_t addChild(T data) {
        return tree_->addChild(Base::index(), data);
    }

    std::vector<std::reference_wrapper<Node>> getChildren() {
        std::vector<std::reference_wrapper<Node>> children;
        children.reserve(Base::nChildren());
        for (size_t id : Base::edges()) {
            children.emplace_back(tree_->getNode(id));
        }
        return children;
    }

    std::vector<const std::reference_wrapper<Node>> getChildren() const {
        std::vector<std::reference_wrapper<Node>> children;
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
