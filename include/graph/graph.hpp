#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "graph_node.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>

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
class Graph {

    friend class GraphNode<T>;

public:

    /**
     * @brief Constructs a Graph with an optional initial capacity.
     *
     * @param initialCapacity Initial capacity for the nodes vector. Defaults to 16.
     */
    explicit Graph(size_t initialCapacity = 16) {
        nodes.reserve(initialCapacity);
    }

    /**
     * @brief Copy constructor. Performs a deep copy of the graph.
     *
     * @param other The Graph to copy from.
     */
    Graph(const Graph& other) : nodes(other.nodes) {
        for (auto& node : nodes) {
            node.graph_ = this;
        }
    }

    /**
     * @brief Move constructor. Transfers ownership of the graph from another Graph.
     *
     * @param other The Graph to move from.
     */
    Graph(Graph&& other) noexcept : nodes(std::move(other.nodes)) {
        for (auto& node : nodes) {
            node.graph_ = this;
        }
    }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the graph.
     *
     * @param other The Graph to copy from.
     * @return Reference to the assigned Graph.
     */
    Graph& operator=(const Graph& other) {
        if (this != &other) {
            nodes = other.nodes;
            for (auto& node : nodes) {
                node.graph_ = this;
            }
        }
        return *this;
    }

    /**
     * @brief Move assignment operator. Transfers ownership of the graph from another Graph.
     *
     * @param other The Graph to move from.
     * @return Reference to the assigned Graph.
     */
    Graph& operator=(Graph&& other) noexcept {
        if (this != &other) {
            nodes = std::move(other.nodes);
            for (auto& node : nodes) {
                node.graph_ = this;
            }
        }
        return *this;
    }

    /**
     * @brief Adds a node to the graph with an optional value.
     *
     * @param value Optional value for the node. Defaults to `std::nullopt`.
     * @return The index of the newly added node.
     */
    size_t addNode(std::optional<T> value = std::nullopt) {
        size_t nodeIndex = nodes.size();
        nodes.emplace_back(std::move(value), nodeIndex, this);
        return nodeIndex;
    }

    /**
     * @brief Adds a directed edge from one node to another.
     *
     * @param fromIndex The index of the source node.
     * @param toIndex The index of the target node.
     *
     * @throws std::out_of_range if either index is invalid.
     */
    void addEdge(size_t fromIndex, size_t toIndex) {
        validateNodeIndex(fromIndex);
        validateNodeIndex(toIndex);

        nodes[fromIndex].addOutgoingEdge(toIndex);
        nodes[toIndex].addIncomingEdge(fromIndex);
    }

    /**
     * @brief Retrieves a reference to the node at the specified index.
     *
     * @param index The index of the node to retrieve.
     * @return Reference to the node.
     *
     * @throws std::out_of_range if the index is invalid.
     */
    GraphNode<T>& getNode(size_t index) {
        return nodes.at(index);  // Using at() for bounds checking
    }

    /**
     * @brief Retrieves a const reference to the node at the specified index.
     *
     * @param index The index of the node to retrieve.
     * @return Const reference to the node.
     *
     * @throws std::out_of_range if the index is invalid.
     */
    const GraphNode<T>& getNode(size_t index) const {
        return nodes.at(index);  // Using at() for bounds checking
    }

    /**
     * @brief Retrieves the number of nodes in the graph.
     *
     * @return The number of nodes.
     */
    constexpr size_t size() const noexcept {
        return nodes.size();
    }

    // *** Iterator Methods ***
    auto begin() { return nodes.begin(); }
    auto end() { return nodes.end(); }
    auto rbegin() { return nodes.rbegin(); }
    auto rend() { return nodes.rend(); }

    const auto begin() const { return nodes.begin(); }
    const auto end() const { return nodes.end(); }
    const auto rbegin() const { return nodes.rbegin(); }
    const auto rend() const { return nodes.rend(); }

    /**
     * @brief Overloads the output stream operator to print the graph nodes.
     *
     * @param os The output stream.
     * @param graph The Graph to print.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Graph<T>& graph) {
        for (const auto& node : graph.nodes) {
            os << node << " ";
        }
        return os;
    }

private:
    std::vector<GraphNode<T>> nodes;  ///<  vector to store all nodes

    /**
     * @brief Validates that the parent index is within the bounds of the nodes vector.
     *
     * @param parentIndex The index of the parent node to validate.
     *
     * @throws std::out_of_range if the parentIndex is invalid.
     */
    inline void validateNodeIndex(size_t parentIndex) const {
        if (parentIndex >= nodes.size()) {
            throw std::out_of_range("Invalid parent index.");
        }
    }

};

} // namespace vpr

#endif // TREE_HPP
