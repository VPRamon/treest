#ifndef FLAT_TREE_HPP
#define FLAT_TREE_HPP

#include "flat_tree_node.hpp"
#include "flat_tree_iterator.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>

namespace vpr {

template <typename T>
class FlatTree {
public:
    std::vector<FlatTreeNode<T>> nodes;  // Flat array to store all nodes

    // Constructor
    FlatTree() { nodes.reserve(16); }  // Pre-allocate space for nodes

    // Add root node (optional value)
    int addRoot(std::optional<T> value = std::nullopt) {
        nodes.emplace_back(value, -1);    // Create the root node with no parent
        return nodes.size() - 1;          // Return index of root
    }

    // Add child to a node at 'parentIndex' (optional value)
    int addChild(int parentIndex, std::optional<T> value = std::nullopt) {
        validateParentIndex(parentIndex);
        int childIndex = nodes.size();
        nodes.emplace_back(value, parentIndex);          // Create and store child node
        nodes[parentIndex].childIndices.push_back(childIndex);  // Link parent to child
        return childIndex;
    }

    // Get a reference to a node at a specific index
    FlatTreeNode<T>& getNode(int index) { 
        validateNodeIndex(index);
        return nodes[index]; 
    }

    // Check if a node has a value
    bool hasValue(int nodeIndex) const { 
        validateNodeIndex(nodeIndex);
        return nodes[nodeIndex].value.has_value(); 
    }

    // Begin iterator (pre-order traversal)
    FlatTreeIterator<T> begin() {
        return FlatTreeIterator<T>(this, nodes.empty() ? -1 : 0);  // Start at the root
    }

    // End iterator (past the end)
    FlatTreeIterator<T> end() {
        return FlatTreeIterator<T>(this, -1);  // Indicate end
    }

private:
    // Validate that the parent index is within bounds
    void validateParentIndex(int parentIndex) const {
        if (parentIndex < 0 || parentIndex >= static_cast<int>(nodes.size())) {
            throw std::out_of_range("Invalid parent index.");
        }
    }

    // Validate that the node index is within bounds
    void validateNodeIndex(int nodeIndex) const {
        if (nodeIndex < 0 || nodeIndex >= static_cast<int>(nodes.size())) {
            throw std::out_of_range("Invalid node index.");
        }
    }
};

// Overload operator<< for FlatTree outside the class template to avoid incomplete type issues
template <typename T>
std::ostream& operator<<(std::ostream& os, const FlatTree<T>& tree) {
    for (const auto& node : tree.nodes) {
        os << node << " ";
    }
    return os;
}

} // namespace vpr

#endif // FLAT_TREE_HPP
