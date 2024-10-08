#ifndef LIGHTWEIGHT_DIGRAPH_HPP
#define LIGHTWEIGHT_DIGRAPH_HPP

#include "graph_template.hpp"
#include "node_template.hpp"

namespace vpr {
namespace lightweight {

/**
 * @class Digraph
 * @brief A directed graph implementation derived from Digraph.
 *
 * This class provides a specialization of Digraph where each node 
 * stores a value of type T. It allows efficient management of nodes 
 * and edges in the graph.
 *
 * @tparam T The type of the value stored in each node.
 */
template <typename T>
class Digraph : public Graph<templates::Node<T, std::vector>, std::vector> {
public:
    using Node = templates::Node<T, std::vector>;
    using Base = Graph<Node, std::vector>;

public:

    size_t addNode(Node node) {
        return Base::emplace_node(node.value());
    }

    /**
     * @brief Adds a directed edge from one node to another.
     *
     * @param from The index of the source node.
     * @param to The index of the target node.
     * 
     * @throws std::out_of_range if either index is invalid.
     */
    void addEdge(size_t from, size_t to) {
        Base::addEdge(from, to);
    }

};

} // namespace lightweight
} // namespace vpr

#endif // LIGHTWEIGHT_DIGRAPH_HPP
