#pragma once

#include "node_template.hpp"
#include "lightweight_tree_node.hpp"

namespace vpr {
namespace lightweight {
namespace binary_tree {

/**
 * @brief A specialized Node class with additional parent tracking.
 *
 * This class extends the functionality of the base `templates::Node` class by adding the concept of
 * a parent node. It stores the parent node's index and provides utility functions to check whether
 * the node is a root, a leaf, and retrieve the number of children.
 *
 * @tparam Data The type of data stored in the node.
 */
template <typename Data, typename Edges>
class Node : public tree::Node<Data, Edges> {
    using Base = tree::Node<Data, Edges>;

public:

    using Base::Node;

    inline size_t left() const { return Base::edges().at(0); }

    inline size_t right() const { return Base::edges().at(1); }
};


} // namespace binary_tree
} // namespace lightweight
} // namespace vpr
