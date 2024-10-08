#ifndef LIGHTWEIGHT_DIGRAPH_HPP
#define LIGHTWEIGHT_DIGRAPH_HPP

#include "graph_template.hpp"
#include "node_template.hpp"

namespace vpr {
namespace lightweight {

/**
 * @brief A lightweight directed graph (digraph) class.
 * 
 * This class represents a directed graph where nodes store values of type `T`. 
 * It uses a specialized `templates::Node` with a `std::vector` as the container for 
 * edges. Unlike an undirected graph, the edges in this digraph are one-way, meaning 
 * that an edge from node `A` to node `B` does not imply an edge from `B` to `A`.
 * 
 * @tparam T The type of the value stored in each node.
 */
template <typename T>
class Digraph : public templates::Graph<templates::Node<T, std::vector>, std::vector> {
public:
    using Node = templates::Node<T, std::vector>;

private:
    using Base = templates::Graph<Node, std::vector>;

public:

    /**
     * @brief Adds a node to the digraph.
     * 
     * Inserts a new node into the digraph with the value stored in the given `Node` object. 
     * The method returns the index of the newly added node.
     * 
     * @param node The node to be added to the digraph.
     * @return The index of the newly added node.
     */
    size_t addNode(Node node) {
        return Base::emplace_node(node.value());
    }

    /**
     * @brief Adds a directed edge between two nodes.
     * 
     * Adds a directed edge from the node with index `from` to the node with index `to`.
     * In a directed graph, this creates a one-way connection from `from` to `to`, 
     * meaning traversal can go from `from` to `to`, but not the other way around unless
     * explicitly added.
     * 
     * @param from The index of the source node.
     * @param to The index of the target node.
     */
    void addEdge(size_t from, size_t to) {
        Base::addEdge(from, to);
    }

};

} // namespace lightweight
} // namespace vpr

#endif // LIGHTWEIGHT_DIGRAPH_HPP
