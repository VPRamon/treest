#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "node.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <stack>

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

    friend class Node<T>;

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
     * @brief Adds a node and all the connected nodes into the graph.
     *        The indexes are updated accordingly.
     *
     * @param node Node to be pushed into the graph.
     * @return The index of the newly added node.
     */
    size_t push_back(const Node<T>& node) {
        /*
        std::set<size_t> visited_nodes{node.index()};
        std::stack<const Node<T>*> to_visit{&node};
        while (!to_visit.empty()) {
            for (auto n : to_visit.top()->getNeighbour()) {
                if (!visited_nodes.contains(n->index())) {
                    visited_nodes.insert(n->index());
                    to_visit.push(&n);
                }
            }
           to_visit.pop();
        }


        size_t base_id = nodes.size();
        auto getNewId = [&visited_nodes, base_id](size_t id){
            auto it = visited_nodes.find(id);
            return base_id + std::distance(visited_nodes.begin(), it) -1;
        };

        nodes.resize(base_id + visited_nodes.size());
        for (auto id : visited_nodes) {
            size_t newId = getNewId(id);
            Node<T>& NewNode = node[newId];
            auto n = node.tree->getNode(id);
            NewNode.value(n.value());
            for (auto neighbours : n.getNeighbours()) {
                NewNode.addEdge(neighbours.index());
            }
        }
        return base_id; // FALSE
        */
       return 0;
    }

    template <typename... Args>
    size_t push_back(Args&&... args) {
        size_t nodeIndex = nodes.size();
        nodes.emplace_back(nodeIndex, this, std::forward<Args>(args)...);
        return nodeIndex;
    }

    /**
     * @brief Adds a node with no edges.
     *
     * @param value Optional value for the node. Defaults to `std::nullopt`.
     * @return The index of the newly added node.
     */
    size_t addChild(std::optional<T> value = std::nullopt) {
        size_t index = nodes.size();
        nodes.emplace_back(index, this, std::move(value));
        return index;
    }

    /**
     * @brief Creates a node in the graph.
     *
     * @param args Arguments needed to create an object of type T.
     * @return The index of the newly added node.
     */
    template <typename... Args>
    size_t emplace_back(Args&&... args) {
        size_t nodeIndex = nodes.size();
        nodes.emplace_back(nodeIndex, this, std::forward<Args>(args)...);
        return nodeIndex;
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
        validateIndex(to);
        nodes.at(from).addEdge(to);
    }

    /**
     * @brief Retrieves a reference to the node at the specified index.
     *
     * @param index The index of the node to retrieve.
     * @return Reference to the node.
     *
     * @throws std::out_of_range if the index is invalid.
     */
    Node<T>& getNode(size_t index) {
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
    const Node<T>& getNode(size_t index) const {
        return nodes.at(index);
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
    std::vector<Node<T>> nodes;  ///<  vector to store all nodes

    /**
     * @brief Validates that the parent index is within the bounds of the nodes vector.
     *
     * @param parentIndex The index of the parent node to validate.
     *
     * @throws std::out_of_range if the parentIndex is invalid.
     */
    inline void validateIndex(size_t index) const {
        if (index >= nodes.size()) {
            throw std::out_of_range("Invalid node index.");
        }
    }

};

} // namespace vpr

#endif // TREE_HPP
