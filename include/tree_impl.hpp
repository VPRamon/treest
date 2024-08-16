#ifndef TREE_IMPL_HPP
#define TREE_IMPL_HPP

namespace rvp {

// Helper struct for visitor pattern
template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

template <typename T, typename U>
std::ostream& Tree<T, U>::stream(std::ostream &out) const {
    if(data_)
        out << data_.value();
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

template <typename T, typename U>
std::string Tree<T, U>::toString() const {
    std::ostringstream oss;  // Create an ostringstream object
    stream(oss);             // Pass the ostringstream to the stream function
    return oss.str();        // Retrieve the string from the ostringstream
}

// Copy constructor
template <typename T, typename U>
Tree<T, U>::Tree(const Tree& other) {
    for (const Node& node : other.children_) {
        std::visit(overload{
            [this](const Leaf& leaf)    { this->addChild(leaf); },
            [this](const SubTree& tree) { this->addChild(*tree); },
        }, node);
    }
}

} // namespace rvp

#endif // TREE_IMPL_HPP
