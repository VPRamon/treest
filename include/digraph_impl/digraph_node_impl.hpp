#ifndef DIGRAPH_NODE_IMPL_HPP
#define DIGRAPH_NODE_IMPL_HPP

#include "node_impl.hpp"

namespace vpr {

template <typename U> class GraphImpl;

namespace digraph_impl {

/**
 * @class Node
 * @brief A specialized node for directed graphs, managing incoming and outgoing edges.
 *
 * This class extends the `NodeImpl` class to support directed graphs (digraphs),
 * where each node can have both incoming and outgoing edges.
 *
 * @tparam T The type of the value stored in the node.
 */
template <typename T>
class Node : public NodeImpl<T> {
    using Base = NodeImpl<T>;
    friend GraphImpl<Node<T>>;

    std::vector<size_t>& out_edges_;  ///< Reference to the outgoing edges
    std::vector<size_t> in_edges_;    ///< Container for incoming edges

public:

    /**
     * @brief Constructs a directed graph node.
     *
     * @param index The index of the node.
     * @param v Optional value stored in the node. Defaults to `std::nullopt`.
     */
    Node(size_t index, std::optional<T> v = std::nullopt)
        : Base(index, v), out_edges_(Base::edges_), in_edges_()
    {}

    /**
     * @brief Retrieves a constant reference to the incoming edges.
     *
     * @return const std::vector<size_t>& A vector of incoming edge indices.
     */
    const std::vector<size_t>& inEdges() const { return in_edges_; }

    /**
     * @brief Retrieves a constant reference to the outgoing edges.
     *
     * @return const std::vector<size_t>& A vector of outgoing edge indices.
     */
    const std::vector<size_t>& outEdges() const { return out_edges_; }

    /**
     * @brief Retrieves the number of incoming edges (in-degree).
     *
     * @return The number of incoming edges.
     */
    size_t inDegree() const { return inEdges().size(); }

    /**
     * @brief Retrieves the number of outgoing edges (out-degree).
     *
     * @return The number of outgoing edges.
     */
    size_t outDegree() const { return outEdges().size(); }

    /**
     * @brief Retrieves the total number of edges (in-degree + out-degree).
     *
     * @return The total number of edges connected to the node.
     */
    size_t totalDegree() const { return inDegree() + outDegree(); }

    /**
     * @brief Adds an incoming edge to the node.
     *
     * @param fromIndex Index of the node from which the edge originates.
     */
    void addInEdge(size_t fromIndex) { in_edges_.push_back(fromIndex); }

    /**
     * @brief Adds an outgoing edge from the node.
     *
     * @param fromIndex Index of the node to which the edge points.
     */
    void addOutEdge(size_t fromIndex) { out_edges_.push_back(fromIndex); }

    /**
     * @brief Checks if the node is isolated (i.e., has no incoming or outgoing edges).
     *
     * @return true If the node has no edges, false otherwise.
     */
    bool isolated() const { return inEdges().empty() && outEdges().empty(); }

};

} // namespace digraph_impl
} // namespace vpr

#endif // DIGRAPH_NODE_IMPL_HPP
