#ifndef PREORDER_ITERATOR_HPP
#define PREORDER_ITERATOR_HPP

#include "base_iterator.hpp"

#include <stack>

namespace vpr {

/**
 * @brief Pre-order traversal functor that pushes children onto a container in reverse order.
 * 
 * This struct defines the behavior for pushing the children of a tree node 
 * onto a container in reverse order, meaning the leftmost child is processed first.
 */
struct ReversePush {
    /**
     * @brief Pushes the children of a node onto the container in reverse order.
     * 
     * @tparam TreeType The type of the tree.
     * @tparam ContainerType The type of the container (e.g., stack, queue).
     * @param tree The tree structure containing nodes.
     * @param container The container to which the children will be pushed.
     * @param currentIndex The index of the current node whose children are to be pushed.
     */
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
    /**
     * @brief Pushes the children of a node onto the container in straight order.
     * 
     * @tparam TreeType The type of the tree.
     * @tparam ContainerType The type of the container (e.g., stack, queue).
     * @param tree The tree structure containing nodes.
     * @param container The container to which the children will be pushed.
     * @param currentIndex The index of the current node whose children are to be pushed.
     */
    template <typename TreeType, typename ContainerType>
    void operator()(const TreeType& tree, ContainerType& container, size_t currentIndex) const {
        const auto& children = tree.getNode(currentIndex).edges();
        for (const auto& child : children) {
            container.push(child);
        }
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
     * This function handles whether the container is a stack or a queue and
     * retrieves the next index accordingly.
     * 
     * @return The index of the next node.
     */
    size_t getNextIndex() {
        size_t index;
        if constexpr (std::is_same_v<ContainerType, std::stack<size_t>>) {
            index = container_.top();
        } else if constexpr (std::is_same_v<ContainerType, std::queue<size_t>>) {
            index = container_.front();
        }
        container_.pop();
        return index;
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
