#ifndef FLAT_TREE_NODE_HPP
#define FLAT_TREE_NODE_HPP

#include <optional>
#include <vector>
#include <iostream>
#include <variant>
#include "type_traits.hpp" // Include the type trait

namespace vpr {

// Forward declaration of FlatTree for friend declaration
template <typename T>
class FlatTree;

// FlatTreeNode structure for generic n-ary trees
template <typename T>
struct FlatTreeNode {
    std::optional<T> value;            // Optional value for the node
    int parentIndex;                   // Index of the parent node (-1 for the root)
    std::vector<int> childIndices;     // Indices of the children nodes

    // Default constructor
    FlatTreeNode() 
        : value(std::nullopt), parentIndex(-1), childIndices() {}

    // Constructor accepting std::optional<T> and parent index
    FlatTreeNode(std::optional<T> v, int parentIdx = -1) 
        : value(v), parentIndex(parentIdx), childIndices() {}

    // Overload operator<< for FlatTreeNode
    friend std::ostream& operator<<(std::ostream& os, const FlatTreeNode<T>& node) {
        if (node.value.has_value()) {
            if constexpr (is_variant<T>::value) {
                // Handle std::variant by visiting the current value
                std::visit([&os](const auto& val) {
                    os << val;
                }, node.value.value());
            } else {
                // Handle non-variant types directly
                os << node.value.value();
            }
        } else {
            os << "None";
        }
        return os;
    }
};

} // namespace vpr

#endif // FLAT_TREE_NODE_HPP
