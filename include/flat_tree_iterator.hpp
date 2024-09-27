#ifndef FLAT_TREE_ITERATOR_HPP
#define FLAT_TREE_ITERATOR_HPP

#include <vector>
#include <stack>
#include <optional>
#include <iterator>

namespace vpr {

template <typename T>
class FlatBinaryTree;  // Forward declaration of FlatBinaryTree

template <typename T>
class FlatTreeNode;  // Forward declaration of FlatTreeNode

// Pre-order Iterator class
template <typename T>
class FlatTreeIterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = FlatTreeNode<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = FlatTreeNode<T>*;
    using reference = FlatTreeNode<T>&;

    // Constructor
    FlatTreeIterator(FlatBinaryTree<T>* tree, int index = -1) 
        : tree_(tree), currentIndex_(index) {
        if (currentIndex_ != -1) {
            nodeStack_.push(currentIndex_);
            traverseToNext();  // Set up the iterator at the start
        }
    }

    reference operator*() { return tree_->nodes[currentIndex_]; }
    pointer operator->() { return &tree_->nodes[currentIndex_]; }

    // Pre-increment
    FlatTreeIterator& operator++() {
        traverseToNext();  // Move to the next node
        return *this;
    }

    // Post-increment
    FlatTreeIterator operator++(int) {
        FlatTreeIterator tmp = *this;
        traverseToNext();
        return tmp;
    }

    bool operator==(const FlatTreeIterator& other) const {
        return currentIndex_ == other.currentIndex_;
    }

    bool operator!=(const FlatTreeIterator& other) const {
        return currentIndex_ != other.currentIndex_;
    }

private:
    FlatBinaryTree<T>* tree_;
    int currentIndex_;
    std::stack<int> nodeStack_;

    // Traverse to the next node (pre-order traversal)
    void traverseToNext() {
        if (nodeStack_.empty()) {
            currentIndex_ = -1;  // End of traversal
            return;
        }

        // Get the next node index from the stack
        currentIndex_ = nodeStack_.top();
        nodeStack_.pop();

        // Push children onto the stack in reverse order
        const auto& children = tree_->nodes[currentIndex_].childIndex;
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            nodeStack_.push(*it);
        }
    }
};

} // namespace vpr

#endif // FLAT_TREE_ITERATOR_HPP
