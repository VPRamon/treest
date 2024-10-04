#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include "node.hpp"

namespace vpr {

template <typename T>
class TreeNode : public Node<T> {
    using Base = Node<T>;

private:
    size_t parent_id_;                   // Index of the parent node (-1 for the root)

public:

    TreeNode(size_t index, size_t parent_id, std::optional<T> v)
        : Base(index, v), parent_id_(parent_id)
    {}

    bool isRoot() const { return Base::index() == 0; }
    bool isLeaf() const { return Base::isolated(); }

    size_t nChildren() const { return Base::degree(); }
    size_t index() const { return Base::index(); }
    size_t parentId() const { return parent_id_; }

    const auto& getChildren() const {
        return Base::edges();
    }

    void addChild(size_t child_id) {
        Base::addEdge(child_id);
    }

};

} // namespace vpr

#endif // TREE_NODE_HPP
