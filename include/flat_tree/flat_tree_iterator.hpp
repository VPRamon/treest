#ifndef FLAT_TREE_ITERATOR_HPP
#define FLAT_TREE_ITERATOR_HPP

#include <iterator>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm> // Added to use std::reverse

namespace vpr {

// Forward declarations
template <typename T>
class FlatTree;

template <typename T>
class FlatTreeNode;

// *** Traversal Policies ***

template <typename TreeType, template <typename...> class Container, bool straight>
struct OrderPolicy {
    static inline void push_children(const TreeType& tree, Container<size_t>& container, size_t currentIndex) {
        const auto& children = tree.nodes.at(currentIndex).childIndices_;
        if constexpr (straight) {
            for (auto it = children.begin(); it != children.end(); ++it) {
                container.push(*it);
            }
        } else {
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                container.push(*it);
            }
        }
    }
};


template <typename TreeType>
struct IteratorProperties {
    TreeType* tree_;
    size_t currentIndex_;

    size_t currentIndex() const {
        return this->currentIndex_;
    }

};

// Pre-order traversal policy
// General PreOrder Traversal with customizable order policy
template <typename NodeType, typename TreeType, bool straight>
class PreOrderTraversalBase : public IteratorProperties<TreeType> {

    std::stack<size_t> nodeStack_;

public:
    PreOrderTraversalBase(TreeType* tree, size_t startIndex) : IteratorProperties<TreeType>(tree, -1)
        {
        if (startIndex != static_cast<size_t>(-1)) {
            this->nodeStack_.push(startIndex);
            advance();
        }
    }

    void advance() {
        if (this->nodeStack_.empty()) {
            this->currentIndex_ = static_cast<size_t>(-1);
            return;
        }

        this->currentIndex_ = this->nodeStack_.top();
        this->nodeStack_.pop();

        OrderPolicy<TreeType, std::stack, straight>::push_children(*this->tree_, this->nodeStack_, this->currentIndex_);
    }

};

// Level-order traversal policy
template <typename NodeType, typename TreeType>
class LevelOrderTraversal : public IteratorProperties<TreeType> {

    std::queue<size_t> nodeQueue_;

public:

    LevelOrderTraversal(TreeType* tree, size_t startIndex) : IteratorProperties<TreeType>(tree, -1) {
        if (startIndex != -1) {
            this->nodeQueue_.push(startIndex);
            advance();
        }
    }

    void advance() {
        if (this->nodeQueue_.empty()) {
            this->currentIndex_ = -1;
            return;
        }

        this->currentIndex_ = nodeQueue_.front();
        this->nodeQueue_.pop();

        OrderPolicy<TreeType, std::queue, true>::push_children(*this->tree_, this->nodeQueue_, this->currentIndex_);
    }
};

// Type alias for standard Pre-Order Traversal (leftmost child first)
template <typename NodeType, typename TreeType>
using PreOrderTraversal = PreOrderTraversalBase<NodeType, TreeType, false>;

// Type alias for Reverse Pre-Order Traversal (rightmost child first)
template <typename NodeType, typename TreeType>
using ReversePreOrderTraversal = PreOrderTraversalBase<NodeType, TreeType, true>;


// Post-order traversal policy
template <typename NodeType, typename TreeType>
class PostOrderTraversal : public IteratorProperties<TreeType> {

    std::stack<size_t> nodeStack_;

public:

    PostOrderTraversal(TreeType* tree, size_t startIndex) : IteratorProperties<TreeType>(tree, -1) {
        if (startIndex != -1) {
            traverseToLeftmostLeaf(startIndex);
            advance();
        }
    }

    void advance() {
        if (this->nodeStack_.empty()) {
            this->currentIndex_ = -1;
            return;
        }

        this->currentIndex_ = this->nodeStack_.top();
        this->nodeStack_.pop();

        if (!this->nodeStack_.empty()) {
            size_t parentIndex = this->nodeStack_.top();
            const auto& siblings = this->tree_->nodes.at(parentIndex).childIndices_;
            auto it = std::find(siblings.begin(), siblings.end(), this->currentIndex_);
            if (it != siblings.end() && ++it != siblings.end()) {
                // There is a next sibling
                traverseToLeftmostLeaf(*it);
            }
        }
    }

private:
    void traverseToLeftmostLeaf(size_t index) {
        while (true) {
            this->nodeStack_.push(index);
            const auto& children = this->tree_->nodes.at(index).childIndices_;
            if (!children.empty()) {
                index = children.front(); // Leftmost child
            } else {
                break;
            }
        }
    }
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
