#ifndef TREE_CONST_ITERATOR_HPP
#define TREE_CONST_ITERATOR_HPP

#include "tree.hpp"

template <typename T>
class ConstIterator {
private:
    using Leaf = T;
    using TreeType = Tree<T>;
    using SubTree = std::unique_ptr<TreeType>;
    using Node = std::variant<Leaf, SubTree>;
    using IteratorType = ConstIterator<T>;

    typename std::list<Node>::const_iterator it_;
    const TreeType& tree_;
    std::shared_ptr<IteratorType> sub_tree_it_;

public:
    ConstIterator(const TreeType& tree) : tree_(tree), it_(tree.children_.cbegin()), sub_tree_it_(nullptr) {}
    ~ConstIterator() = default;

    static auto begin(const TreeType& tree) { return IteratorType(tree); }
    static auto beginPtr(const TreeType& tree) { return std::make_shared<IteratorType>(tree); }

    const Node& operator*() const { return sub_tree_it_ ? **sub_tree_it_ : *it_; }
    const Node* operator->() const { return sub_tree_it_ ? &(*sub_tree_it_) : &(*it_); }

    bool operator==(const ConstIterator& other) const { return it_ == other.it_; }
    bool operator!=(const ConstIterator& other) const { return it_ != other.it_; }

    static ConstIterator end(const TreeType& tree);

    void incrementIterator();

    static ConstIterator next(const ConstIterator& it) {
        ConstIterator next_it = it;
        next_it++;
        return next_it;
    }

    ConstIterator& operator++() {
        incrementIterator();
        return *this;
    }

    ConstIterator operator++(int) {
        ConstIterator temp = *this;
        ++(*this);
        return temp;
    }

};

#include <const_iterator_impl.hpp>

#endif // TREE_CONST_ITERATOR_HPP
