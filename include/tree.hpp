#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <list>
#include <memory>
#include <variant>
#include "iterator.hpp"

namespace rvp {

template <typename T, typename U = char>
class Tree {
public:
    using NodeData = U;
    using Leaf = T;
    using SubTree = std::unique_ptr<Tree>;
    using Node = std::variant<Leaf, SubTree>;

    using ConstSubTree = std::unique_ptr<const Tree>;
    using ConstNode = std::variant<Leaf, ConstSubTree>;

    using Iterator = BaseIterator<Leaf, NodeData, Tree, typename std::list<std::variant<Leaf, std::unique_ptr<Tree>>>::iterator>;
    using ConstIterator = BaseIterator<Leaf, NodeData, const Tree, typename std::list<std::variant<Leaf, std::unique_ptr<Tree>>>::const_iterator>;

    static bool isLeaf(const Node& node)    { return std::get_if<Leaf>(&node); }
    static bool isSubTree(const Node& node) { return std::get_if<SubTree>(&node); }
    static const Leaf& getLeaf(const Node& node) { return std::get<Leaf>(node); }
    static Leaf& getLeaf(Node& node) { return std::get<Leaf>(node); }

    static const SubTree& getSubTree(const Node& node) { return std::get<SubTree>(node); }
    static SubTree& getSubTree(Node& node) { return std::get<SubTree>(node); }

    Tree(std::optional<NodeData> data = std::nullopt) : data_(data) {};
    virtual ~Tree() = default;
    Tree(const Tree& other);

    void addChild(const Leaf& leaf) { children_.emplace_back(leaf); }
    void addChild(const Tree& tree) { children_.emplace_back(std::make_unique<Tree>(tree)); }

    void addChild(Node node) { children_.emplace_back(std::move(node)); }
    const std::list<Node>& getChildren() const { return children_; }

    std::ostream& stream(std::ostream &out) const;

    std::string toString() const;

    auto begin() { return Iterator::begin(*this); }
    auto end()   { return Iterator::end(*this); }

    auto begin() const { return cbegin(); }
    auto end()   const { return cend(); }

    auto cbegin() const { return ConstIterator::begin(*this); }
    auto cend()   const { return ConstIterator::end(*this); }


    NodeData& operator*()  { return data_; }
    NodeData* operator->() { return data_;; }

    const NodeData& operator*()  const { return data_; }
    const NodeData* operator->() const { return data_; }

protected:
    std::list<Node> children_;
    std::optional<NodeData> data_;
    friend Iterator;
    friend ConstIterator;
};

template<typename U, typename W>
std::ostream& operator<<(std::ostream& os, const Tree<U, W>& tree) {
    return tree.stream(os);
}

} // namespace rvp

#include "tree_impl.hpp"

#endif // TREE_HPP
