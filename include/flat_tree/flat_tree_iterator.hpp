#ifndef FLAT_TREE_ITERATOR_HPP
#define FLAT_TREE_ITERATOR_HPP

#include "flat_tree.hpp" // Include flat_tree to have access to FlatTree and FlatTreeNode
#include <vector>
#include <stack>
#include <optional>
#include <iterator>

namespace vpr {

// Pre-order Iterator class for FlatTree
template <typename T>
class FlatTreeIterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = FlatTreeNode<T>;
    using difference_type = std::ptrdiff_t;
    using pointer = FlatTreeNode<T>*;
    using reference = FlatTreeNode<T>&;

    // Constructor
    FlatTreeIterator(FlatTree<T>* tree, int index = -1) 
        : tree_(tree), currentIndex_(-1) {
        if (tree && !tree->nodes.empty() && index != -1) {
            nodeStack_.push(index);   // Push root index
            traverseToNext();         // Initialize the first node
        }
    }

    // Dereference operators
    reference operator*() const { return tree_->nodes[currentIndex_]; }
    pointer operator->() const { return &tree_->nodes[currentIndex_]; }

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

    // Equality operators
    bool operator==(const FlatTreeIterator& other) const {
        return currentIndex_ == other.currentIndex_;
    }

    bool operator!=(const FlatTreeIterator& other) const {
        return currentIndex_ != other.currentIndex_;
    }

private:
    FlatTree<T>* tree_;
    int currentIndex_;
    std::stack<int> nodeStack_;

    // Traverse to the next node in pre-order
    void traverseToNext() {
        if (nodeStack_.empty()) {
            currentIndex_ = -1;  // End iterator
            return;
        }

        // Pop the current node
        currentIndex_ = nodeStack_.top();
        nodeStack_.pop();

        // Push children in reverse order to process leftmost child first
        const auto& children = tree_->nodes[currentIndex_].childIndices;
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            nodeStack_.push(*it);
        }
    }
};

} // namespace vpr

#endif // FLAT_TREE_ITERATOR_HPP
