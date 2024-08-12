#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <list>
#include <memory>
#include <variant>

template <typename T> class Iterator;

template <typename T>
class Tree {
    friend Iterator<T>;
public:
    using Leaf = T;
    using SubTree = std::unique_ptr<Tree<T>>;
    using Node = std::variant<Leaf, SubTree>;

    Tree() = default;
    virtual ~Tree() = default;

    void addChild(Node node) { children_.emplace_back(std::move(node)); }
    const std::list<Node>& getChildren() const { return children_; }

    std::ostream& stream(std::ostream &out) const;

    std::string toString() const;

    auto begin() { return Iterator<T>::begin(*this); }
    auto end() { return Iterator<T>::end(*this); }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Tree<U>& tree);

protected:
    std::list<Node> children_;
};

template<typename U>
std::ostream& operator<<(std::ostream& os, const Tree<U>& tree) {
    return tree.stream(os);
}

#include <tree_impl.hpp>

#endif // TREE_HPP
