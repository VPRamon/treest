#ifndef FLAT_TREE_ITERATOR_HPP
#define FLAT_TREE_ITERATOR_HPP

#include <iterator>
#include <stack>
#include <queue>
#include <algorithm> // Added to use std::reverse

namespace vpr {

// Forward declarations
template <typename T>
class FlatTree;

template <typename T>
class FlatTreeNode;

// *** Traversal Policies ***

// Pre-order traversal policy
template <typename NodeType, typename TreeType>
class PreOrderTraversal {
public:
    using IndexType = size_t;

    PreOrderTraversal(TreeType* tree, IndexType startIndex) 
        : tree_(tree), currentIndex_(-1) {
        if (startIndex != -1) {
            nodeStack_.push(startIndex);
            advance();
        }
    }

    void advance() {
        if (nodeStack_.empty()) {
            currentIndex_ = -1;
            return;
        }

        currentIndex_ = nodeStack_.top();
        nodeStack_.pop();

        const auto& children = tree_->nodes.at(currentIndex_).childIndices_;
        // Push children in reverse order to process leftmost child first
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            nodeStack_.push(*it);
        }
    }

    IndexType currentIndex() const {
        return currentIndex_;
    }

private:
    TreeType* tree_;
    std::stack<IndexType> nodeStack_;
    IndexType currentIndex_;
};

// Corrected Reverse pre-order traversal policy
template <typename NodeType, typename TreeType>
class ReversePreOrderTraversal {
public:
    using IndexType = size_t;

    ReversePreOrderTraversal(TreeType* tree, IndexType startIndex) 
        : tree_(tree), currentIndex_(-1) {
        if (startIndex != -1) {
            nodeStack_.push(startIndex);
            advance();
        }
    }

    void advance() {
        if (nodeStack_.empty()) {
            currentIndex_ = -1;
            return;
        }

        currentIndex_ = nodeStack_.top();
        nodeStack_.pop();

        const auto& children = tree_->nodes.at(currentIndex_).childIndices_;
        // Push children in normal order to process rightmost child first
        for (auto it = children.begin(); it != children.end(); ++it) {
            nodeStack_.push(*it);
        }
    }

    IndexType currentIndex() const {
        return currentIndex_;
    }

private:
    TreeType* tree_;
    std::stack<IndexType> nodeStack_;
    IndexType currentIndex_;
};

// Post-order traversal policy
template <typename NodeType, typename TreeType>
class PostOrderTraversal {
public:
    using IndexType = size_t;

    PostOrderTraversal(TreeType* tree, IndexType startIndex)
        : tree_(tree) {
        if (startIndex != -1) {
            traverseToLeftmostLeaf(startIndex);
            advance();
        } else {
            currentIndex_ = -1;
        }
    }

    void advance() {
        if (nodeStack_.empty()) {
            currentIndex_ = -1;
            return;
        }

        currentIndex_ = nodeStack_.top();
        nodeStack_.pop();

        if (!nodeStack_.empty()) {
            IndexType parentIndex = nodeStack_.top();
            const auto& siblings = tree_->nodes.at(parentIndex).childIndices_;
            auto it = std::find(siblings.begin(), siblings.end(), currentIndex_);
            if (it != siblings.end() && ++it != siblings.end()) {
                // There is a next sibling
                traverseToLeftmostLeaf(*it);
            }
        }
    }

    IndexType currentIndex() const {
        return currentIndex_;
    }

private:
    void traverseToLeftmostLeaf(IndexType index) {
        while (true) {
            nodeStack_.push(index);
            const auto& children = tree_->nodes.at(index).childIndices_;
            if (!children.empty()) {
                index = children.front(); // Leftmost child
            } else {
                break;
            }
        }
    }

    TreeType* tree_;
    std::stack<IndexType> nodeStack_;
    IndexType currentIndex_;
};

// Level-order traversal policy
template <typename NodeType, typename TreeType>
class LevelOrderTraversal {
public:
    using IndexType = size_t;

    LevelOrderTraversal(TreeType* tree, IndexType startIndex)
        : tree_(tree) {
        if (startIndex != -1) {
            nodeQueue_.push(startIndex);
            advance();
        } else {
            currentIndex_ = -1;
        }
    }

    void advance() {
        if (nodeQueue_.empty()) {
            currentIndex_ = -1;
            return;
        }

        currentIndex_ = nodeQueue_.front();
        nodeQueue_.pop();

        const auto& children = tree_->nodes.at(currentIndex_).childIndices_;
        for (const auto& childIndex : children) {
            nodeQueue_.push(childIndex);
        }
    }

    IndexType currentIndex() const {
        return currentIndex_;
    }

private:
    TreeType* tree_;
    std::queue<IndexType> nodeQueue_;
    IndexType currentIndex_;
};

// *** Iterator Class Template ***

template <typename NodeType, typename TreeType, typename TraversalPolicy>
class FlatTreeIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = NodeType;
    using difference_type = std::ptrdiff_t;
    using pointer = NodeType*;
    using reference = NodeType&;

    FlatTreeIterator(TreeType* tree, size_t startIndex = 0)
        : traversalPolicy_(tree, startIndex), tree_(tree) {}

    reference operator*() const {
        return tree_->nodes.at(traversalPolicy_.currentIndex());
    }

    pointer operator->() const {
        return &tree_->nodes.at(traversalPolicy_.currentIndex());
    }

    FlatTreeIterator& operator++() {
        traversalPolicy_.advance();
        return *this;
    }

    FlatTreeIterator operator++(int) {
        FlatTreeIterator tmp = *this;
        traversalPolicy_.advance();
        return tmp;
    }

    bool operator==(const FlatTreeIterator& other) const {
        return traversalPolicy_.currentIndex() == other.traversalPolicy_.currentIndex();
    }

    bool operator!=(const FlatTreeIterator& other) const {
        return !(*this == other);
    }

private:
    TraversalPolicy traversalPolicy_;
    TreeType* tree_;
};

} // namespace vpr

#endif // FLAT_TREE_ITERATOR_HPP
