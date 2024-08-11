#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <stack>
#include <variant>
#include "tree.hpp"

template <typename T>
class Iterator {
private:
    using Leaf = T;
    using SubTree = std::unique_ptr<Tree<T>>;
    using Node = std::variant<Leaf, SubTree>;

    typename std::list<Node>::iterator it_;
    Tree<T>* tree_;

public:
    Iterator(Tree<T>& tree) : tree_(&tree), it_(tree.children_.begin()) {}

    // Access operators
    Node& operator*() const { return *it_; }
    Node* operator->() { return &(*it_); }

    // Prefix increment
    Iterator& operator++() {
        ++it_;
        return *this;
    }

    // Postfix increment
    Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    // Equality/Inequality operators
    bool operator==(const Iterator& other) const { return it_ == other.it_; }
    bool operator!=(const Iterator& other) const { return it_ != other.it_; }
};

#endif // TREE_ITERATOR_HPP
