#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "tree.hpp"

template <typename T>
class Iterator {
private:
    using Leaf = T;
    using TreeType = Tree<T>;
    using SubTree = std::unique_ptr<TreeType>;
    using Node = std::variant<Leaf, SubTree>;
    using IteratorType = Iterator<T>;

    typename std::list<Node>::iterator it_;
    TreeType& tree_;
    std::shared_ptr<IteratorType> sub_tree_it_;

public:
    Iterator(TreeType& tree) : tree_(tree), it_(tree.children_.begin()), sub_tree_it_(nullptr) {}
    ~Iterator() = default;

    static auto begin(TreeType& tree) { return IteratorType(tree); }
    static auto beginPtr(TreeType& tree) { return std::make_shared<IteratorType>(tree); }

    Node& operator*() const { return sub_tree_it_ ? **sub_tree_it_ : *it_; }
    Node* operator->() { return sub_tree_it_ ? &(*sub_tree_it_) : &it_; }

    bool operator==(const Iterator& other) const { return it_ == other.it_; }
    bool operator!=(const Iterator& other) const { return it_ != other.it_; }

    static IteratorType end(TreeType& tree);

    void incrementIterator();

    // buggy, whall do a deep copy
    static IteratorType next(const IteratorType& it) {
        IteratorType next_it = it;
        next_it++;
        return next_it;
    }

    Iterator& operator++() {
        incrementIterator();
        return *this;
    }

    Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

};

#include <iterator_impl.hpp>

#endif // TREE_ITERATOR_HPP
