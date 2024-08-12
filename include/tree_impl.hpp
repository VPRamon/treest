#ifndef TREE_IMPL_HPP
#define TREE_IMPL_HPP

// Helper struct for visitor pattern
template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

template <typename T>
std::ostream& Tree<T>::stream(std::ostream &out) const {
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

template <typename T>
std::string Tree<T>::toString() const {
    std::ostringstream oss;  // Create an ostringstream object
    stream(oss);             // Pass the ostringstream to the stream function
    return oss.str();        // Retrieve the string from the ostringstream
}

#endif // TREE_IMPL_HPP
