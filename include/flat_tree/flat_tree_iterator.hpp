#ifndef FLAT_TREE_ITERATOR_HPP
#define FLAT_TREE_ITERATOR_HPP

#include <iterator>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>
#include <type_traits>

namespace vpr {

// Forward declarations
template <typename T>
class FlatTree;

template <typename T>
class FlatTreeNode;

// *** Iterator Properties ***

template <typename TreeType>
struct IteratorProperties {
    TreeType* tree_;
    size_t currentIndex_;

    size_t currentIndex() const {
        return this->currentIndex_;
    }

};

// Post-order traversal policy (remains separate due to different logic)
template <typename NodeType, typename TreeType>
class PostOrderTraversal : public IteratorProperties<TreeType> {

    std::stack<size_t> nodeStack_;

public:

    PostOrderTraversal(TreeType* tree, size_t startIndex) : IteratorProperties<TreeType>{tree, static_cast<size_t>(-1)} {
        if (startIndex != static_cast<size_t>(-1)) {
            traverseToLeftmostLeaf(startIndex);
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

    FlatTreeIterator(TreeType* tree, size_t startIndex = 0)
        : traversalPolicy_(tree, startIndex), tree_(tree) {}

    auto operator*() const {
        return tree_->nodes.at(traversalPolicy_.currentIndex());
    }

    auto operator->() const {
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
