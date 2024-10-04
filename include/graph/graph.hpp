#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "graph_impl.hpp"
#include "graph_node.hpp"

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
class Graph : public GraphImpl<graph::Node<T>> {
    using Base = GraphImpl<graph::Node<T>>;
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
        graph::Node<T>& orig = Base::getNode(from);
        graph::Node<T>& dest = Base::getNode(to);
        orig.addEdge(to);
        dest.addEdge(from);
    }
 
};

} // namespace vpr

#endif // GRAPH_HPP
