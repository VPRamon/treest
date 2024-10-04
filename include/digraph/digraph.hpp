#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include "graph_impl.hpp"
#include "digraph_node.hpp"

namespace vpr {

/**
 * @brief Represents a directed graph using a vector to store nodes.
 *
 * The Graph class manages a collection of nodes stored in a vector,
 * allowing efficient traversal and manipulation of the graph structure.
 *
 * @tparam T The type of the value stored in each node.
 */
template <typename T>
class Digraph : public GraphImpl<digraph::Node<T>> {
    using Base = GraphImpl<digraph::Node<T>>;
public:

    /**
     * @brief Adds a node with no edges.
     *
     * @param value Optional value for the node. Defaults to `std::nullopt`.
     * @return The index of the newly added node.
     */
    size_t addNode(std::optional<T> value = std::nullopt) {
        return Base::template addNode(value);
    }

    virtual void addEdge(size_t from, size_t to) override {
        digraph::Node<T>& orig = Base::getNode(from);
        digraph::Node<T>& dest = Base::getNode(to);
        orig.addOutEdge(to);
        dest.addInEdge(from);
    }
 
};

} // namespace vpr

#endif // DIGRAPH_HPP
