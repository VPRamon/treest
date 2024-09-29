#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "base_iterator.hpp"
#include <stack>

namespace vpr {

/**
 * @brief Post-order traversal policy for tree traversal.
 * 
 * This class implements a post-order traversal algorithm. Post-order traversal
 * processes the children of a node before the node itself, requiring a different
 * traversal logic compared to pre-order or breadth-first search.
 * 
 * @tparam NodeType The type of the nodes in the tree.
 * @tparam TreeType The type of the tree being traversed.
 */
template <typename NodeType, typename TreeType>
class PostOrderTraversal : public IteratorProperties<TreeType> {

    std::stack<size_t> nodeStack_; ///< Stack to store node indices during traversal.

public:

    /**
     * @brief Constructs a post-order traversal object.
     * 
     * Starts the post-order traversal at the specified node index. The traversal
     * will descend to the leftmost leaf of the tree, as required by post-order.
     * 
     * @param tree Pointer to the tree structure.
     * @param startIndex The index of the node where the traversal should start.
     */
    PostOrderTraversal(TreeType* tree, size_t startIndex) 
        : IteratorProperties<TreeType>{tree, static_cast<size_t>(-1)} {
        if (startIndex != static_cast<size_t>(-1)) {
            traverseToLeftmostLeaf(startIndex);
            advance();
        }
    }

    /**
     * @brief Advances the traversal to the next node in post-order.
     * 
     * This method moves the traversal to the next node in post-order, ensuring
     * that all children are processed before the current node. It handles advancing
     * through siblings and parents as required by post-order traversal.
     */
    void advance() {
        if (this->nodeStack_.empty()) {
            this->currentIndex_ = static_cast<size_t>(-1);
            return;
        }

        this->currentIndex_ = this->nodeStack_.top();
        this->nodeStack_.pop();

        if (!this->nodeStack_.empty()) {
            size_t parentIndex = this->nodeStack_.top();
            const auto& siblings = this->tree_->nodes.at(parentIndex).childIndices_;
            auto it = std::find(siblings.begin(), siblings.end(), this->currentIndex_);
            if (it != siblings.end() && ++it != siblings.end()) {
                traverseToLeftmostLeaf(*it);
            }
        }
    }

private:
    /**
     * @brief Traverses to the leftmost leaf node starting from a given node.
     * 
     * This helper function pushes nodes onto the stack, following the leftmost
     * child path until a leaf node is reached. This ensures that post-order
     * traversal can proceed by visiting leaf nodes before their parents.
     * 
     * @param index The index of the node to start the traversal from.
     */
    void traverseToLeftmostLeaf(size_t index) {
        while (true) {
            this->nodeStack_.push(index);
            const auto& children = this->tree_->nodes.at(index).childIndices_;
            if (!children.empty()) {
                index = children.front();
            } else {
                break;
            }
        }
    }
};

} // namespace vpr

#endif // TREE_ITERATOR_HPP
