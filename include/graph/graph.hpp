#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "graph_impl.hpp"
#include "graph_node.hpp"

namespace vpr {

/**
 * @class Graph
 * @brief A directed graph implementation derived from GraphImpl.
 *
 * This class provides a specialization of GraphImpl where each node 
 * stores a value of type T. It allows efficient management of nodes 
 * and edges in the graph.
 *
 * @tparam T The type of the value stored in each node.
 */
template <typename T>
class Graph : public GraphImpl<graph::Node<T>> {
    using Base = GraphImpl<graph::Node<T>>;

public:

    /**
     * @brief Adds a node with an optional value and no edges.
     *
     * @param value Optional value for the node. Defaults to `std::nullopt`.
     * @return The index of the newly added node.
     */
    size_t addNode(std::optional<T> value = std::nullopt) {
        return Base::template addNode(value);
    }

    /**
     * @brief Adds a bidirectional edge between two nodes.
     *
     * This method overrides the base class's `addEdge` to ensure that
     * an edge is added in both directions (from -> to and to -> from).
     *
     * @param from Index of the source node.
     * @param to Index of the target node.
     *
     * @throws std::out_of_range if either node index is invalid.
     */
    virtual void addEdge(size_t from, size_t to) override {
        graph::Node<T>& orig = Base::getNode(from);
        graph::Node<T>& dest = Base::getNode(to);
        orig.addEdge(to);
        dest.addEdge(from);
    }
};

} // namespace vpr

#endif // GRAPH_HPP
