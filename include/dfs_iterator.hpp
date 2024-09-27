#ifndef DFS_ITERATOR_HPP
#define DFS_ITERATOR_HPP

#include <stack>

namespace vpr {

template <typename ChildrenType, typename NodeType> class NodeInterface;

template <typename ChildrenType, typename NodeType, typename NodePtr>
class TreeIterator {
public:
    using Node = NodeInterface<ChildrenType, NodeType>;

    TreeIterator(NodePtr root) {
        if (root) {
            stack_.push(root);
        }
    }

    TreeIterator& operator++() {
        if (!stack_.empty()) {
            NodePtr node = stack_.top();
            stack_.pop();
            if (!node->isLeaf()) {
                auto& children = node->getChildren();
                for (auto it = children.rbegin(); it != children.rend(); ++it) {
                    stack_.push(&*it);
                }
            }
        }
        return *this;
    }

    TreeIterator operator++(int) {
        TreeIterator temp = *this;
        ++(*this);
        return temp;
    }

    decltype(auto) operator*() const {
        return *stack_.top();
    }

    NodePtr operator->() const {
        return stack_.top();
    }

    bool operator==(const TreeIterator& other) const {
        return stack_ == other.stack_;
    }

    bool operator!=(const TreeIterator& other) const {
        return !(*this == other);
    }

private:
    std::stack<NodePtr> stack_;
};


}

#endif
