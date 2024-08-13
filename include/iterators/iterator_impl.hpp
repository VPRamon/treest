#ifndef TREE_ITERATOR_IMPL_HPP
#define TREE_ITERATOR_IMPL_HPP

template <typename T>
Iterator<T> Iterator<T>::end(TreeType& tree) {
    Iterator<T> iterator(tree);
    iterator.it_ = tree.children_.end();
    return iterator;
}

template <typename T>
void Iterator<T>::incrementIterator() {
    if (sub_tree_it_) {
        ++(*sub_tree_it_);
        if (*sub_tree_it_ == IteratorType::end(sub_tree_it_->tree_)) {
            sub_tree_it_ = nullptr;
            ++it_;
        }
    } else if (auto* sub_tree = std::get_if<SubTree>(&(*it_))) {
        sub_tree_it_ = IteratorType::beginPtr(**sub_tree);
    } else {
        ++it_;
    }
};


#endif // TREE_ITERATOR_IMPL_HPP
