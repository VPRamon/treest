#ifndef BASE_ITERATOR_HPP
#define BASE_ITERATOR_HPP

#include <stack>
#include <queue>
#include <algorithm>

namespace vpr {

/**
 * @struct IteratorProperties
 * @brief Struct holding the properties of a tree iterator.
 * 
 * This struct stores the tree being iterated over and the current index in the traversal.
 * It provides utility methods for accessing the current state of the traversal.
 * 
 * @tparam TreeType The type of the tree being iterated over.
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
 * @class TreeIterator
 * @brief A class template for iterating over tree-like structures.
 * 
 * This iterator supports different traversal policies (e.g., pre-order, post-order) 
 * for tree structures. The traversal is defined by the policy passed to the template.
 * 
 * @tparam NodeType The type of the nodes in the tree.
 * @tparam TreeType The type of the tree being traversed.
 * @tparam TraversalPolicy The traversal policy (e.g., pre-order, reverse pre-order).
 */
template <typename NodeType, typename TreeType, typename TraversalPolicy>
class TreeIterator {
public:
    using iterator_category = std::forward_iterator_tag; ///< Iterator category for forward traversal.
    using value_type = NodeType; ///< The type of the values (nodes) being iterated over.
    using difference_type = std::ptrdiff_t; ///< Type used for iterator arithmetic.
    using pointer = NodeType*;  ///< Pointer to the type the iterator points to.
    using reference = NodeType&; ///< Reference to the type the iterator points to.

    /**
     * @brief Constructs a tree iterator starting at a specific node.
     * 
     * @param tree Pointer to the tree structure being traversed.
     * @param startIndex The index of the node to start the iteration from (default is 0).
     */
    TreeIterator(TreeType* tree, size_t startIndex = 0)
        : traversalPolicy_(tree, startIndex), tree_(tree) {}

    /**
     * @brief Dereferences the iterator to access the current node.
     * 
     * @return A reference to the current node being iterated over.
     */
    reference operator*() const {
        return tree_->getNode(traversalPolicy_.currentIndex());
    }

    /**
     * @brief Accesses the current node using pointer syntax.
     * 
     * @return A pointer to the current node being iterated over.
     */
    pointer operator->() const {
        return &tree_->getNode(traversalPolicy_.currentIndex());
    }

    /**
     * @brief Advances the iterator to the next node (prefix increment).
     * 
     * @return A reference to the iterator after advancing to the next node.
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
    TraversalPolicy traversalPolicy_; ///< The traversal policy defining the iterator's behavior.
    TreeType* tree_; ///< Pointer to the tree structure being iterated.
};

} // namespace vpr

#endif // BASE_ITERATOR_HPP
