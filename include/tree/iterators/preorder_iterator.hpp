#ifndef PREORDER_ITERATOR_HPP
#define PREORDER_ITERATOR_HPP

#include "base_iterator.hpp"

#include <stack>
#include <queue>
#include <type_traits>  // For std::is_same

namespace vpr {

/**
 * @brief Pre-order traversal functor that pushes children onto a container in reverse order.
 * 
 * This struct defines the behavior for pushing the children of a tree node 
 * onto a container in reverse order, meaning the leftmost child is processed first.
 */
struct ReversePush {
    template <typename TreeType, typename ContainerType>
    void operator()(const TreeType& tree, ContainerType& container, size_t currentIndex) const {
        const auto& children = tree.getNode(currentIndex).edges();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            container.push(*it);
        }
    }
};

/**
 * @brief Reverse Pre-order traversal functor that pushes children onto a container in straight order.
 * 
 * This struct defines the behavior for pushing the children of a tree node 
 * onto a container in straight order, meaning the rightmost child is processed first.
 */
struct StraightPush {
    template <typename TreeType, typename ContainerType>
    void operator()(const TreeType& tree, ContainerType& container, size_t currentIndex) const {
        const auto& children = tree.getNode(currentIndex).edges();
        for (const auto& child : children) {
            container.push(child);
        }
    }
};

/**
 * @brief Traits class to abstract container operations.
 * 
 * This class provides a uniform interface to access elements from different container types.
 */
template <typename ContainerType>
struct ContainerTraits;

// Specialization for std::stack<size_t>
template <>
struct ContainerTraits<std::stack<size_t>> {
    static size_t getNextIndex(std::stack<size_t>& container) {
        size_t index = container.top();
        container.pop();
        return index;
    }
};

// Specialization for std::queue<size_t>
template <>
struct ContainerTraits<std::queue<size_t>> {
    static size_t getNextIndex(std::queue<size_t>& container) {
        size_t index = container.front();
        container.pop();
        return index;
    }
};

/**
 * @brief Generalized traversal class template for tree traversal algorithms.
 * 
 * This class defines a general tree traversal mechanism that works with a custom
 * container (e.g., stack, queue) and a custom push children function (e.g., Pre-order, Reverse Pre-order).
 * 
 * @tparam TreeType The type of the tree.
 * @tparam ContainerType The type of the container used to store node indices during traversal.
 * @tparam PushChildrenFunc The function used to push children onto the container.
 */
template <typename TreeType, typename ContainerType, typename PushChildrenFunc>
class GeneralTraversal : public IteratorProperties<TreeType> {

    ContainerType container_; ///< Container used to store node indices for traversal.
    PushChildrenFunc pushChildren_; ///< Functor used to push children onto the container.

public:
    /**
     * @brief Constructs a traversal object.
     * 
     * @param tree The tree structure to traverse.
     * @param startIndex The index of the node where the traversal should start.
     */
    GeneralTraversal(TreeType* tree, size_t startIndex)
        : IteratorProperties<TreeType>{tree, static_cast<size_t>(-1)} {
        // Ensure that the container type is supported
        static_assert(std::is_same<ContainerType, std::stack<size_t>>::value ||
                      std::is_same<ContainerType, std::queue<size_t>>::value,
                      "Unsupported container type");

        if (startIndex != static_cast<size_t>(-1)) {
            container_.push(startIndex);
            advance();
        }
    }

    /**
     * @brief Advances the traversal to the next node.
     * 
     * Moves the traversal to the next node by popping the next node index
     * from the container and pushing its children onto the container.
     */
    void advance() {
        if (container_.empty()) {
            this->currentIndex_ = static_cast<size_t>(-1);
            return;
        }

        this->currentIndex_ = getNextIndex();

        pushChildren_(*this->tree_, container_, this->currentIndex_);
    }

private:
    /**
     * @brief Retrieves the next node index from the container.
     * 
     * This function uses the ContainerTraits class to abstract away the differences
     * between different container types.
     * 
     * @return The index of the next node.
     */
    size_t getNextIndex() {
        return ContainerTraits<ContainerType>::getNextIndex(container_);
    }
};

/**
 * @brief Type alias for Pre-Order Traversal (leftmost child first).
 * 
 * This type alias simplifies the use of the `GeneralTraversal` class for pre-order traversal,
 * where children are processed left to right (reverse push).
 * 
 * @tparam TreeType The type of the tree being traversed.
 */
template <typename TreeType>
using PreOrderTraversal = GeneralTraversal<TreeType, std::stack<size_t>, ReversePush>;

/**
 * @brief Type alias for Reverse Pre-Order Traversal (rightmost child first).
 * 
 * This type alias simplifies the use of the `GeneralTraversal` class for reverse pre-order traversal,
 * where children are processed right to left (straight push).
 * 
 * @tparam TreeType The type of the tree being traversed.
 */
template <typename TreeType>
using ReversePreOrderTraversal = GeneralTraversal<TreeType, std::stack<size_t>, StraightPush>;

} // namespace vpr

#endif // PREORDER_ITERATOR_HPP
