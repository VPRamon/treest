#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <list>
#include <memory>
#include <variant>
#include "iterator.hpp"

template <typename T>
class Tree {
    friend Iterator<T>;
    friend ConstIterator<T>;
public:
    using Leaf = T;
    using SubTree = std::unique_ptr<Tree<T>>;
    using Node = std::variant<Leaf, SubTree>;

    using ConstSubTree = std::unique_ptr<const Tree<T>>;
    using ConstNode = std::variant<Leaf, ConstSubTree>;

    static bool isLeaf(const Node& node) { return std::get_if<Leaf>(&node); }
    static bool isSubTree(const Node& node) { return std::get_if<SubTree>(&node); }
    static const Leaf& getLeaf(const Node& node) { return std::get<Leaf>(node); }
    static Leaf& getLeaf(Node& node) { return std::get<Leaf>(node); }

    static const SubTree& getSubTree(const Node& node) { return std::get<SubTree>(node); }
    static SubTree& getSubTree(Node& node) { return std::get<SubTree>(node); }

    Tree() = default;
    virtual ~Tree() = default;

    void addChild(Node node) { children_.emplace_back(std::move(node)); }
    const std::list<Node>& getChildren() const { return children_; }

    std::ostream& stream(std::ostream &out) const;

    std::string toString() const;

    auto begin() { return Iterator<T>::begin(*this); }
    auto end() { return Iterator<T>::end(*this); }

    auto begin() const { return ConstIterator<T>::begin(*this); }
    auto end() const { return ConstIterator<T>::end(*this); }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Tree<U>& tree);

protected:
    std::list<Node> children_;
};

template<typename U>
std::ostream& operator<<(std::ostream& os, const Tree<U>& tree) {
    return tree.stream(os);
}

#include "tree_impl.hpp"

#endif // TREE_HPP
