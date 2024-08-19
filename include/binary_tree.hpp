#ifndef TREE_HPP
#define TREE_HPP

#include <utility>

#include "node.hpp"

namespace rvp {

template <typename NodeType>
class BinaryTree : public NodeInterface<
                       std::pair<
                           BinaryTree<NodeType>,
                           BinaryTree<NodeType>>,
                       NodeType> {
    using ChildType = std::pair<BinaryTree<NodeType>, BinaryTree<NodeType>>;
    using ParentType = NodeInterface<ChildType, NodeType>;

public:
    using ParentType::NodeInterface;

    const BinaryTree& left() const {
        assert(this->children_ && "Attempting to access left child of a leaf node.");
        return this->children_->first;
    }

    BinaryTree& left() {
        assert(this->children_ && "Attempting to access left child of a leaf node.");
        return this->children_->first;
    }

    const BinaryTree& right() const {
        assert(this->children_ && "Attempting to access right child of a leaf node.");
        return this->children_->second;
    }

    BinaryTree& right() {
        assert(this->children_ && "Attempting to access right child of a leaf node.");
        return this->children_->second;
    }
};


} // namespace rvp

#endif // TREE_HPP
