#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <list>
#include <memory>
#include <variant>

template <typename T>
class Tree {
public:
    using Leaf = T;
    using SubTree = std::unique_ptr<Tree<T>>;
    using Node = std::variant<Leaf, SubTree>;

    Tree() = default;
    virtual ~Tree() = default;

    void addChild(Node node) { 
        children_.emplace_back(std::move(node)); 
    }

    static bool isLeaf(const Node& node) {
        return std::holds_alternative<Leaf>(node);
    }

    static bool isSubTree(const Node& node) {
        return std::holds_alternative<SubTree>(node);
    }

    static const Leaf& getLeaf(const Node& node) {
        return std::get<Leaf>(node);
    }

    static const SubTree& getSubTree(const Node& node) {
        return std::get<SubTree>(node);
    }

    void printTree(int depth = 0) const {
        for (const auto& child : children_) {
            if (isLeaf(child)) {
                std::cout << std::string(depth * 2, ' ') << getLeaf(child) << "\n";
            } else {
                std::cout << std::string(depth * 2, ' ') << "SubTree:\n";
                getSubTree(child)->printTree(depth + 1);
            }
        }
    }

protected:
    std::list<Node> children_;
};

#endif // TREE_HPP
