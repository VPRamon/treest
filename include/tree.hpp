#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <list>
#include <memory>
#include <variant>
#include <string>

// Helper struct for visitor pattern
template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

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

    void stream(std::ostream &out) const {
        out << '{';
        for (auto it = children_.begin(); it != children_.end(); ++it) {
            std::visit(overload{
                [&out](const Leaf& leaf)    { out << leaf; },
                [&out](const SubTree& tree) { tree->stream(out); },
            }, *it);
            if (std::next(it) != children_.end()) {  // Check if it's not the last element
                out << ',';
            }
        }
        out << '}';
    }

    void print() {
        this->stream(std::cout);
    }

    std::string toString() {
        std::ostringstream oss;  // Create an ostringstream object
        stream(oss);             // Pass the ostringstream to the stream function
        return oss.str();        // Retrieve the string from the ostringstream
    }

protected:
    std::list<Node> children_;
};

#endif // TREE_HPP
