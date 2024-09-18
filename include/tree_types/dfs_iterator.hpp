#ifndef DFS_ITERATOR_HPP
#define DFS_ITERATOR_HPP

#include <stack>

namespace vpr {

template <typename ChildrenType, typename NodeType> class NodeInterface;

template <typename ChildrenType, typename NodeType>
class TreeIterator {
public:
    using Node = NodeInterface<ChildrenType, NodeType>;

    TreeIterator(Node* root) {
        if (root) {
            stack_.push(root);
        }
    }

    TreeIterator(const Node* root) : TreeIterator(const_cast<Node*>(root)) {}

    TreeIterator& operator++() {
        if (!stack_.empty()) {
            auto* node = stack_.top();
            stack_.pop();
            if (!node->isLeaf()) {
                for (auto it = node->getChildren()->rbegin(); it != node->getChildren()->rend(); ++it) {
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

    Node& operator*() {
        return *stack_.top();
    }

    Node* operator->() {
        return stack_.top();
    }

    const Node& operator*() const {
        return *stack_.top();
    }

    const Node* operator->() const {
        return stack_.top();
    }


    bool operator==(const TreeIterator& other) const {
        return stack_ == other.stack_;
    }

    bool operator!=(const TreeIterator& other) const {
        return !(*this == other);
    }

private:
    std::stack<Node*> stack_;
};

}

#endif
