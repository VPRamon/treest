#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <stack>
#include <variant>
#include "tree.hpp"

template <typename T>
class Iterator {
private:
    using Leaf = T;
    using SubTree = std::unique_ptr<TreeImpl<T>>;
    using Node = std::variant<Leaf, SubTree>;

    typename std::list<Node>::iterator it_;
    TreeImpl<T>& tree_;
    std::shared_ptr<Iterator<T>> sub_tree_it_;

public:
    Iterator(TreeImpl<T>& tree)
        : tree_(tree), it_(tree.children_.begin()), sub_tree_it_(nullptr)
    { }

    static auto begin(TreeImpl<T>& tree) {
        return Iterator<T>(tree);
    }

    static auto beginPtr(TreeImpl<T>& tree) {
        return std::make_shared<Iterator<T>>(tree);
    }

    static Iterator<T> end(TreeImpl<T>& tree) {
        Iterator<T> iterator(tree);
        iterator.it_ = tree.children_.end();
        return iterator;
    }

    // Access operators
    Node& operator*() const { return sub_tree_it_ ? **sub_tree_it_ : *it_; }
    Node* operator->() { return sub_tree_it_ ? &(*sub_tree_it_) : &it_; }

    // Prefix increment
    Iterator& operator++() {
        if (sub_tree_it_) {
            (*sub_tree_it_)++;
            if (*sub_tree_it_ == Iterator<T>::end(sub_tree_it_->tree_)) { // Si es l'ultim clean
                ++it_;
                sub_tree_it_ = nullptr;
            }
        }
        else if (auto* sub_tree = std::get_if<SubTree>(&(*it_))) { // I am in a subtree-root
            sub_tree_it_ = Iterator<T>::beginPtr(**sub_tree);      // initialize sub_tree iterator (first child)
        }
        else {  // I am a leaf, visit next node
            ++it_;
        }
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
