#ifndef LIGHTWEIGHT_GRAPH_NODE_HPP
#define LIGHTWEIGHT_GRAPH_NODE_HPP

#include "node_impl.hpp"

namespace vpr {
namespace lightweight {
namespace graph {

/**
 * @class Node
 * @brief A specialized graph node that inherits from NodeImpl.
 *
 * This class represents a node within a graph structure and extends 
 * the functionality of the base NodeImpl class. Each node can store 
 * an optional value and manage its edges in the graph.
 *
 * @tparam T The type of the value stored in the node.
 */
template <typename T>
class Node : public NodeImpl<T> {
    using Base = NodeImpl<T>;

public:

    // Inherit constructors from NodeImpl
    using Base::NodeImpl;

    /**
     * @brief Retrieves the number of edges (degree) of the node.
     *
     * @return The degree (number of edges) of the node.
     */
    virtual size_t degree() const override { return Base::degree(); }

    /**
     * @brief Gets a constant reference to the list of edges.
     *
     * @return const std::vector<size_t>& The vector of edge indices.
     */
    virtual const std::vector<size_t>& edges() const { return Base::edges(); }

    /**
     * @brief Adds an edge from this node to another node.
     *
     * @param fromIndex The index of the node to add an edge to.
     */
    virtual void addEdge(size_t fromIndex) { Base::addEdge(fromIndex); }

    /**
     * @brief Checks if the node is isolated (i.e., has no edges).
     *
     * @return true If the node has no edges.
     * @return false If the node has one or more edges.
     */
    virtual bool isolated() const { return Base::isolated(); }
};

} // namespace graph
} // namespace lightweight
} // namespace vpr

#endif // LIGHTWEIGHT_GRAPH_NODE_HPP
