#ifndef DIGRAPH_IMPL_HPP
#define DIGRAPH_IMPL_HPP

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
template <typename Node>
class DigraphImpl : public GraphImpl<Node> {
    using Graph = GraphImpl<Node>;
public:

    virtual void addEdge(size_t from, size_t to) override {
        Node& orig = Graph::getNode(from);
        Node& dest = Graph::getNode(to);
        orig.addOutEdge(to);
        dest.addInEdge(from);
    }
 
};

} // namespace vpr

#endif // DIGRAPH_IMPL_HPP
