#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include "node_impl.hpp"

namespace vpr {

template <typename TreeNode> class GraphImpl;

template <typename T>
class TreeNode : public NodeImpl<T> {
    using Base = NodeImpl<T>;
    friend GraphImpl<TreeNode<T>>;

    size_t parent_id_;

public:

    TreeNode(size_t index, size_t parent_id, std::optional<T> v)
        : Base(index, v), parent_id_(parent_id)
    {}

    bool isRoot() const { return Base::index() == 0; }
    bool isLeaf() const { return Base::isolated(); }

    size_t nChildren() const { return Base::degree(); }
    size_t parentId()  const { return parent_id_; }

    const auto& getChildren() const { return Base::edges(); }

    void addChild(size_t child_id) { Base::addEdge(child_id); }

};

} // namespace vpr

#endif // TREE_NODE_HPP
