#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <memory>
#include <variant>
#include <list>
#include <type_traits>

template<typename Leaf, typename NodeData> class Tree;

template <typename Leaf, typename NodeData, typename TreeType, typename IteratorType>
class BaseIterator {
protected:
    using SubTree = std::unique_ptr<TreeType>;
    using NodeType = std::variant<Leaf, std::unique_ptr<Tree<Leaf, NodeData>>>;
    using Node = NodeType;

    IteratorType it_;
    TreeType& tree_;
    std::shared_ptr<BaseIterator<Leaf, NodeData, TreeType, IteratorType>> sub_tree_it_;

public:
    BaseIterator(TreeType& tree) : tree_(tree), it_(tree.children_.begin()), sub_tree_it_(nullptr) {}
    ~BaseIterator() = default;

    BaseIterator(const BaseIterator& other)
        : tree_(other.tree_),
        it_(other.it_) {
        if (other.sub_tree_it_) {
            this->sub_tree_it_ = std::make_shared<BaseIterator<Leaf, NodeData, TreeType, IteratorType>>(*other.sub_tree_it_);
        } else {
            this->sub_tree_it_ = nullptr;
        }
    }
    static BaseIterator begin(TreeType& tree) {
        return BaseIterator(tree);
    }

    static std::shared_ptr<BaseIterator> beginPtr(TreeType& tree) {
        using NonConstIteratorType = typename std::list<NodeType>::iterator;
        using ConstIteratorType = typename std::list<NodeType>::const_iterator;

        if constexpr (std::is_const_v<TreeType>) {
            return std::make_shared<BaseIterator<Leaf, NodeData, TreeType, ConstIteratorType>>(tree);
        } else {
            return std::make_shared<BaseIterator<Leaf, NodeData, TreeType, NonConstIteratorType>>(tree);
        }
    }

    Node& operator*() requires(!std::is_const_v<TreeType>) { return sub_tree_it_ ? **sub_tree_it_ : *it_; }
    Node* operator->() requires(!std::is_const_v<TreeType>) { return sub_tree_it_ ? &(**sub_tree_it_) : &(*it_); }

    const Node& operator*() const { return sub_tree_it_ ? **sub_tree_it_ : *it_; }
    const Node* operator->() const { return sub_tree_it_ ? &(**sub_tree_it_) : &(*it_); }


    bool operator==(const BaseIterator& other) const { return it_ == other.it_; }
    bool operator!=(const BaseIterator& other) const { return it_ != other.it_; }

    void incrementIterator() {
        if (sub_tree_it_) {
            ++(*sub_tree_it_);
            if (*sub_tree_it_ == BaseIterator::end(sub_tree_it_->tree_)) {
                sub_tree_it_ = nullptr;
                ++it_;
            }
        } else if (auto* sub_tree = std::get_if<std::unique_ptr<Tree<Leaf, NodeData>>>(&(*it_))) {
            if constexpr (std::is_const_v<TreeType>) {
                sub_tree_it_ = beginPtr(*static_cast<const TreeType*>(sub_tree->get()));
            } else {
                sub_tree_it_ = beginPtr(**sub_tree);
            }
        } else {
            ++it_;
        }
    }

    BaseIterator& operator++() {
        incrementIterator();
        return *this;
    }

    BaseIterator operator++(int) {
        BaseIterator temp = *this;
        ++(*this);
        return temp;
    }

    static BaseIterator end(TreeType& tree) {
        BaseIterator iterator(tree);
        iterator.it_ = tree.children_.end();
        return iterator;
    }
};


#endif // TREE_ITERATOR_HPP
