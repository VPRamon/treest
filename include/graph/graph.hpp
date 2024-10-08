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
class Graph {
    using Base = GraphImpl<graph::Node<T>>;

public:

    using Base::GraphImpl;

    /**
     * @brief Copy constructor. Performs a deep copy of the graph.
     *
     * @param other The Graph to copy from.
     */
    Graph(const Graph& other) : Base(other)
    { syncNodes(); }

    /**
     * @brief Move constructor. Transfers ownership of the graph from another Graph.
     *
     * @param other The Graph to move from.
     */
    Graph(Graph&& other) noexcept : Base(other)
    { syncNodes(); }

    /**
     * @brief Move assignment operator. Transfers ownership of the graph from another Graph.
     *
     * @param other The Graph to move from.
     * @return Reference to the assigned Graph.
     */
    Graph& operator=(Graph&& other) noexcept {
        if (this != &other) {
            Base::nodes = std::move(other.nodes);
            syncNodes();
        }
        return *this;
    }

    /**
     * @brief Adds a node with an optional value and no edges.
     *
     * @param value Optional value for the node. Defaults to `std::nullopt`.
     * @return The index of the newly added node.
     */
    Graph operator=(Graph& other) {
        Base::nodes = other.nodes;
        syncNodes();
    }

    /**
     * @brief Adds a new node to the graph.
     *
     * @tparam T Type of the value to store in the node.
     * @param value Optional value for the node. Defaults to `std::nullopt`.
     * @return The index of the newly added node.
     */
    size_t addNode(std::optional<T> value = std::nullopt) {
        size_t index = Base::size();
        Base::nodes.emplace_back(this, index, std::move(value));
        return index;
    }

    /**
     * @brief Constructs a node with arguments and adds it to the graph.
     *
     * @tparam Args Types of arguments to construct the node.
     * @param args Arguments needed to construct the node.
     * @return The index of the newly added node.
     */
    template <typename... Args>
    size_t emplace_node(Args&&... args {
        size_t nodeIndex = nodes.size();
        nodes.emplace_back(this nodeIndex, std::forward<Args>(args)...);
        return nodeIndex;
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

private:

    inline void syncNodes() {
        for (auto& node : Base::nodes) {
            node.graph(this);
        }
    }

};

} // namespace vpr

#endif // GRAPH_HPP
