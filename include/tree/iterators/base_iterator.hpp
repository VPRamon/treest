#ifndef BASE_ITERATOR_HPP
#define BASE_ITERATOR_HPP

#include <stack>
#include <queue>
#include <algorithm>

namespace vpr {


/**
 * @brief Struct holding the properties of a tree iterator.
 * 
 * This struct stores the tree being iterated over and the current index in the traversal.
 * 
 * @tparam TreeType The type of the tree.
 */
template <typename TreeType>
struct IteratorProperties {
    TreeType* tree_;  ///< Pointer to the tree structure being traversed.
    size_t currentIndex_; ///< The current index of the traversal.

    /**
     * @brief Returns the current index of the traversal.
     * 
     * @return The index of the current node.
     */
    size_t currentIndex() const {
        return this->currentIndex_;
    }
};


/**
 * @brief A class template for tree iterators.
 * 
 * This class defines an iterator for traversing tree-like structures using 
 * a specified traversal policy, container type, and node type.
 * 
 * @tparam NodeType The type of the nodes in the tree.
 * @tparam TreeType The type of the tree being traversed.
 * @tparam TraversalPolicy The traversal policy used (e.g., pre-order, reverse pre-order).
 */
template <typename NodeType, typename TreeType, typename TraversalPolicy>
class TreeIterator {
public:
    using iterator_category = std::forward_iterator_tag; ///< Iterator category is forward iterator.
    using value_type = NodeType; ///< The type of the values (nodes) being iterated over.
    using difference_type = std::ptrdiff_t; ///< The difference type used for iterator arithmetic.

    /**
     * @brief Constructs a tree iterator.
     * 
     * @param tree Pointer to the tree to iterate over.
     * @param startIndex The index of the node to start the iteration from (default is 0).
     */
    TreeIterator(TreeType* tree, size_t startIndex = 0)
        : traversalPolicy_(tree, startIndex), tree_(tree) {}

    /**
     * @brief Dereferences the iterator to access the current node.
     * 
     * @return A reference to the current node.
     */
    auto operator*() const {
        return tree_->getNode(traversalPolicy_.currentIndex());
    }

    /**
     * @brief Accesses the current node using pointer-like syntax.
     * 
     * @return A pointer to the current node.
     */
    auto operator->() const {
        return &tree_->getNode(traversalPolicy_.currentIndex());
    }

    /**
     * @brief Advances the iterator to the next node (prefix increment).
     * 
     * @return A reference to the iterator after advancing.
     */
    TreeIterator& operator++() {
        traversalPolicy_.advance();
        return *this;
    }

    /**
     * @brief Advances the iterator to the next node (postfix increment).
     * 
     * @return A copy of the iterator before advancing.
     */
    TreeIterator operator++(int) {
        TreeIterator tmp = *this;
        traversalPolicy_.advance();
        return tmp;
    }

    /**
     * @brief Compares two iterators for equality.
     * 
     * @param other The iterator to compare with.
     * @return True if both iterators point to the same node, otherwise false.
     */
    bool operator==(const TreeIterator& other) const {
        return traversalPolicy_.currentIndex() == other.traversalPolicy_.currentIndex();
    }

    /**
     * @brief Compares two iterators for inequality.
     * 
     * @param other The iterator to compare with.
     * @return True if the iterators point to different nodes, otherwise false.
     */
    bool operator!=(const TreeIterator& other) const {
        return !(*this == other);
    }

private:
    TraversalPolicy traversalPolicy_; ///< The traversal policy used by the iterator.
    TreeType* tree_; ///< Pointer to the tree being iterated.
};

} // namespace vpr

#endif // BASE_ITERATOR_HPP
