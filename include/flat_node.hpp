#ifndef _FLAT_NODE_HPP
#define _FLAT_NODE_HPP

#include <optional>
#include <vector>
#include <iostream>

#include "flat_tree_iterator.hpp"

namespace vpr {

template <typename T>
struct FlatTreeNode {
    std::optional<T> value;            // Optional value for the node
    int parentIndex;                   // Index of the parent node (-1 for the root)
    std::vector<int> childIndex;       // Indices of the children nodes

    // Default constructor
    FlatTreeNode() : value(std::nullopt), parentIndex(-1) {}

    // Constructor accepting std::optional<T>
    FlatTreeNode(std::optional<T> v, int parentIdx = -1)
        : value(v), parentIndex(parentIdx) {}
};

template <typename T>
class FlatBinaryTree {
public:
    std::vector<FlatTreeNode<T>> nodes;  // Flat array to store all nodes

    // Constructor
    FlatBinaryTree() { nodes.reserve(16); }  // Pre-allocate space for nodes

    // Add root node
    int addRoot(std::optional<T> value = std::nullopt) {
        nodes.emplace_back(value);             // Create the root node
        return nodes.size() - 1;               // Return index of root
    }

    // Add child to a node at 'parentIndex'
    int addChild(int parentIndex, std::optional<T> value = std::nullopt) {
        int childIndex = nodes.size();
        nodes.emplace_back(value, parentIndex);   // Create and store child node
        nodes[parentIndex].childIndex.push_back(childIndex);  // Link parent to child
        return childIndex;
    }

    // Begin iterator (pre-order traversal)
    FlatTreeIterator<T> begin() {
        if (nodes.empty()) return FlatTreeIterator<T>(this, -1);
        return FlatTreeIterator<T>(this, 0);  // Start at the root
    }

    // End iterator (past the end)
    FlatTreeIterator<T> end() {
        return FlatTreeIterator<T>(this, -1);  // Indicate end
    }

    // Utility function to print the tree using the iterator
    void printPreOrder() {
        for (auto it = begin(); it != end(); ++it) {
            if (it->value.has_value()) {
                std::cout << "Node: " << it->value.value() << std::endl;
            } else {
                std::cout << "Node: None" << std::endl;
            }
        }
    }

};

} // namespace vpr

#endif // _FLAT_NODE_HPP
