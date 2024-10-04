#ifndef DIGRAPH_IMPL_HPP
#define DIGRAPH_IMPL_HPP

#include "graph_impl.hpp"
#include "digraph_node.hpp"

namespace vpr {

/**
 * @class DigraphImpl
 * @brief A directed graph implementation derived from GraphImpl.
 *
 * This class represents a directed graph, where edges have a direction 
 * (from a source node to a target node). It specializes the behavior of 
 * `GraphImpl` by managing both incoming and outgoing edges for each node.
 *
 * @tparam Node The type of the nodes in the graph.
 */
template <typename Node>
class DigraphImpl : public GraphImpl<Node> {
    using Graph = GraphImpl<Node>;

public:

    /**
     * @brief Adds a directed edge from one node to another.
     *
     * This method overrides the base class's `addEdge` to ensure that an 
     * outgoing edge is added from the source node, and an incoming edge 
     * is added to the target node.
     *
     * @param from The index of the source node.
     * @param to The index of the target node.
     *
     * @throws std::out_of_range if either node index is invalid.
     */
    virtual void addEdge(size_t from, size_t to) override {
        Node& orig = Graph::getNode(from);
        Node& dest = Graph::getNode(to);
        orig.addOutEdge(to);
        dest.addInEdge(from);
    }

};

} // namespace vpr

#endif // DIGRAPH_IMPL_HPP
