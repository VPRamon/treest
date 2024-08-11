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
    Tree<T>& tree_;
    std::shared_ptr<Iterator<T>> sub_tree_it_;

public:
    Iterator(Tree<T>& tree)
        : tree_(tree), it_(tree.children_.begin()), sub_tree_it_(nullptr)
    { }

    static auto begin(Tree<T>& tree) {
        return Iterator<T>(tree);
    }

    static auto beginPtr(Tree<T>& tree) {
        return std::make_shared<Iterator<T>>(tree);
    }

    static Iterator<T> end(Tree<T>& tree) {
        Iterator<T> iterator(tree);
        auto it = tree.children_.end();
        while (auto* sub_tree = std::get_if<SubTree>(&(*it))) {
            it = (*sub_tree)->children_.end();
            if ((*sub_tree)->children_.empty()) {
                break;
            }
            it--;
        }
        iterator.it_ = it;
        return iterator;
    }

    // Access operators
    Node& operator*() const { return sub_tree_it_ ? **sub_tree_it_ : *it_; }
    Node* operator->() { return sub_tree_it_ ? &(*sub_tree_it_) : &it_; }

    // Prefix increment
    Iterator& operator++() {
        if (sub_tree_it_) {
            (*sub_tree_it_)++;
            if (*sub_tree_it_ == std::get<SubTree>(*it_)->end()) { // Si es l'ultim clean
                sub_tree_it_ = nullptr;
                it_++;
            }
        }
        else if (auto* sub_tree = std::get_if<SubTree>(&(*it_))) {
            sub_tree_it_ = Iterator<T>::beginPtr(**sub_tree);
        }
        else {
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
