#ifndef PREORDER_ITERATOR_HPP
#define PREORDER_ITERATOR_HPP

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

// Pre-order push children (leftmost child first)
struct ReversePush {
    template <typename TreeType, typename ContainerType>
    void operator()(const TreeType& tree, ContainerType& container, size_t currentIndex) const {
        const auto& children = tree.nodes.at(currentIndex).childIndices_;
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            container.push(*it);
        }
    }
};

// Reverse Pre-order push children (rightmost child first)
struct StraightPush {
    template <typename TreeType, typename ContainerType>
    void operator()(const TreeType& tree, ContainerType& container, size_t currentIndex) const {
        const auto& children = tree.nodes.at(currentIndex).childIndices_;
        for (const auto& child : children) {
            container.push(child);
        }
    }
};

// *** General Traversal Class Template ***

template <typename TreeType, typename ContainerType, typename PushChildrenFunc>
class GeneralTraversal : public IteratorProperties<TreeType> {

    ContainerType container_;
    PushChildrenFunc pushChildren_;

public:

    GeneralTraversal(TreeType* tree, size_t startIndex)
        : IteratorProperties<TreeType>{tree, static_cast<size_t>(-1)} {
        if (startIndex != static_cast<size_t>(-1)) {
            container_.push(startIndex);
            advance();
        }
    }

    void advance() {
        if (container_.empty()) {
            this->currentIndex_ = static_cast<size_t>(-1);
            return;
        }

        this->currentIndex_ = getNextIndex();

        // Push children onto the container
        pushChildren_(*this->tree_, container_, this->currentIndex_);
    }

private:
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

// Type alias for standard Pre-Order Traversal (leftmost child first)
template <typename TreeType>
using PreOrderTraversal = GeneralTraversal<TreeType, std::stack<size_t>, ReversePush>;

// Type alias for Reverse Pre-Order Traversal (rightmost child first)
template <typename TreeType>
using ReversePreOrderTraversal = GeneralTraversal<TreeType, std::stack<size_t>, StraightPush>;

// Type alias for Level-Order Traversal
template <typename TreeType>
using LevelOrderTraversal = GeneralTraversal<TreeType, std::queue<size_t>, StraightPush>;


} // namespace vpr

#endif // FLAT_TREE_ITERATOR_HPP
