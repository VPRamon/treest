#ifndef TREE_IMPL_HPP
#define TREE_IMPL_HPP

#include <iostream>
#include <list>
#include <memory>
#include <variant>
#include <sstream>

// Helper struct for visitor pattern
template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;
template <typename T> class Iterator;

template <typename T>
class TreeImpl {
    friend Iterator<T>;
public:
    using Leaf = T;
    using SubTree = std::unique_ptr<TreeImpl<T>>;
    using Node = std::variant<Leaf, SubTree>;

    TreeImpl() = default;
    virtual ~TreeImpl() = default;

    void addChild(Node node) { children_.emplace_back(std::move(node)); }
    const std::list<Node>& getChildren() const { return children_; }

    std::ostream& stream(std::ostream &out) const {
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
        return out;
    }

    std::string toString() const {
        std::ostringstream oss;  // Create an ostringstream object
        stream(oss);             // Pass the ostringstream to the stream function
        return oss.str();        // Retrieve the string from the ostringstream
    }

    // Begin and End functions for the iterator
    auto begin() { return Iterator<T>::begin(*this); }
    auto end() { return Iterator<T>::end(*this); }

    // Friend function declaration for operator<<
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const TreeImpl<U>& tree);

protected:
    std::list<Node> children_;
};

// Implementation of operator<<
template<typename U>
std::ostream& operator<<(std::ostream& os, const TreeImpl<U>& tree) {
    return tree.stream(os);
}

#endif // TREE_IMPL_HPP
