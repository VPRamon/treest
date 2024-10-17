#ifndef LIGHTWEIGHT_GRAPH_HPP
#define LIGHTWEIGHT_GRAPH_HPP

#include "graph_template.hpp"
#include "node_template.hpp"
#include <vector>

namespace vpr {
namespace lightweight {

/**
 * @brief A lightweight, undirected graph class that stores nodes and edges.
 * 
 * This class represents a simple, undirected graph where each node holds a value of type `T`.
 * It extends a more generic `Graph` template, specializing the node type to use `templates::Node` 
 * with a `std::vector` as the container for storing edges. Each edge is bidirectional, 
 * meaning if an edge from `A` to `B` is added, an edge from `B` to `A` is automatically added as well.
 * 
 * @tparam T The type of the value stored in each node.
 */
template <typename T>
class Graph : public templates::Graph<templates::Node<T, size_t, std::vector>, std::vector<templates::Node<T, size_t, std::vector>>> {
public:
    using Node = templates::Node<T, size_t, std::vector>;

private:
    using Base = templates::Graph<Node, std::vector<Node>>;

public:

    /**
     * @brief Adds a node to the graph.
     * 
     * Inserts a new node into the graph. The node is created with the value 
     * stored in the passed `Node` object. The method returns the index of the newly added node.
     * 
     * @param node The node to be added to the graph.
     * @return The index of the newly added node.
     */
    size_t addNode(Node node) {
        return Base::emplace_node(node.value());
    }

    /**
     * @brief Adds an undirected edge between two nodes.
     * 
     * Adds an edge from the node with index `from` to the node with index `to` and 
     * vice versa, as this is an undirected graph. This method establishes a bidirectional connection.
     * 
     * @param from The index of the first node.
     * @param to The index of the second node.
     */
    void addEdge(size_t from, size_t to) {
        Base::addEdge(from, to);
        Base::addEdge(to, from);
    }

};

} // namespace lightweight
} // namespace vpr

#endif // LIGHTWEIGHT_GRAPH_HPP
