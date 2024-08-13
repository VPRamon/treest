#ifndef TREE_CONST_ITERATOR_IMPL_HPP
#define TREE_CONST_ITERATOR_IMPL_HPP

template <typename T>
void ConstIterator<T>::incrementIterator() {
    if (sub_tree_it_) {
        ++(*sub_tree_it_);
        if (*sub_tree_it_ == ConstIterator::end(sub_tree_it_->tree_)) {
            sub_tree_it_ = nullptr;
            ++it_;
        }
    } else if (auto* sub_tree = std::get_if<SubTree>(&(*it_))) {
        sub_tree_it_ = IteratorType::beginPtr(**sub_tree);
    } else {
        ++it_;
    }
}

template <typename T>
ConstIterator<T> ConstIterator<T>::end(const TreeType& tree) {
    ConstIterator iterator(tree);
    iterator.it_ = tree.children_.cend();
    return iterator;
}

#endif // TREE_ITERATOR_IMPL_HPP
