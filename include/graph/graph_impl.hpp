#ifndef GRAPH_IMPL_HPP
#define GRAPH_IMPL_HPP

#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <stack>

namespace vpr {

/**
 * @brief Represents a directed graph using a vector to store nodes.
 *
 * The GraphImpl class manages a collection of nodes stored in a vector,
 * allowing efficient traversal and manipulation of the graph structure.
 *
 * @tparam Node The type of the value stored in each node.
 */
template <typename Node>
class GraphImpl {

    std::vector<Node> nodes;  ///<  vector to store all nodes

public:

    /**
     * @brief Constructs a GraphImpl with an optional initial capacity.
     *
     * @param initialCapacity Initial capacity for the nodes vector. Defaults to 16.
     */
    explicit GraphImpl(size_t initialCapacity = 16) {
        nodes.reserve(initialCapacity);
    }

    /**
     * @brief Copy constructor. Performs a deep copy of the graph.
     *
     * @param other The GraphImpl to copy from.
     */
    GraphImpl(const GraphImpl& other) : nodes(other.nodes)
    { }

    /**
     * @brief Move constructor. Transfers ownership of the graph from another GraphImpl.
     *
     * @param other The GraphImpl to move from.
     */
    GraphImpl(GraphImpl&& other) noexcept : nodes(std::move(other.nodes))
    { }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the graph.
     *
     * @param other The GraphImpl to copy from.
     * @return Reference to the assigned GraphImpl.
     */
    GraphImpl& operator=(const GraphImpl& other) {
        if (this != &other) {
            nodes = other.nodes;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator. Transfers ownership of the graph from another GraphImpl.
     *
     * @param other The GraphImpl to move from.
     * @return Reference to the assigned GraphImpl.
     */
    GraphImpl& operator=(GraphImpl&& other) noexcept {
        if (this != &other) {
            nodes = std::move(other.nodes);
        }
        return *this;
    }

    /**
     * @brief Adds a node with no edges.
     *
     * @param value Optional value for the node. Defaults to `std::nullopt`.
     * @return The index of the newly added node.
     */
    template <typename T>
    size_t addNode(std::optional<T> value = std::nullopt) {
        size_t index = nodes.size();
        nodes.emplace_back(index, std::move(value));
        return index;
    }

    /**
     * @brief Creates a node in the graph.
     *
     * @param args Arguments needed to create an object of type T.
     * @return The index of the newly added node.
     */
    template <typename... Args>
    size_t emplace_node(Args&&... args) {
        size_t nodeIndex = nodes.size();
        nodes.emplace_back(nodeIndex, std::forward<Args>(args)...);
        return nodeIndex;
    }

    /**
     * @brief Retrieves a reference to the node at the specified index.
     *
     * @param index The index of the node to retrieve.
     * @return Reference to the node.
     *
     * @throws std::out_of_range if the index is invalid.
     */
    Node& getNode(size_t index) {
        return nodes.at(index);
    }

    /**
     * @brief Retrieves a const reference to the node at the specified index.
     *
     * @param index The index of the node to retrieve.
     * @return Const reference to the node.
     *
     * @throws std::out_of_range if the index is invalid.
     */
    const Node& getNode(size_t index) const {
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

    constexpr bool empty() const noexcept {
        return nodes.empty();
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
     * @param graph The GraphImpl to print.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const GraphImpl<Node>& graph) {
        for (const auto& node : graph.nodes) {
            os << node << " ";
        }
        return os;
    }

protected:

    /**
     * @brief Adds a directed edge from one node to another.
     *
     * @param from The index of the source node.
     * @param to The index of the target node.
     *
     * @throws std::out_of_range if either index is invalid.
     */
    virtual void addEdge(size_t from, size_t to) {
        validateIndex(to);
        nodes.at(from).addEdge(to);
    }


private:

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

#endif // GRAPH_IMPL_HPP
