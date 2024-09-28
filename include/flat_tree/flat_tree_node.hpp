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
    int index;                         // Index of the self node
    int parentIndex;                   // Index of the parent node (-1 for the root)
    std::vector<int> childIndices;     // Indices of the children nodes
    FlatTree<T>* tree;

    // Default constructor
    FlatTreeNode() 
        : value(std::nullopt), parentIndex(-1), index(0), tree(nullptr), childIndices() {}

    // Constructor accepting std::optional<T> and parent index
    FlatTreeNode(std::optional<T> v, int parentIdx = -1, int index=0, FlatTree<T>* tree=nullptr)
        : value(v), parentIndex(parentIdx), index(index), tree(tree), childIndices() {}

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

    // Add child to a node at 'parentIndex' (optional value)
    int addChild(std::optional<T> value = std::nullopt) {
        return this->tree->addChild(index, value);
    }

    // Get a reference to a node at a specific index
    FlatTreeNode<T>& getChild(int index) {
        assert(childIndices.size() < index);
        return this->tree->getNode(childIndices[index]);
    } 

};

} // namespace vpr

#endif // FLAT_TREE_NODE_HPP
