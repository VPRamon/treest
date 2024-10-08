#ifndef GRAPH_IMPL_HPP
#define GRAPH_IMPL_HPP

#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>

namespace vpr {

/**
 * @class GraphImpl
 * @brief A base graph implementation using a vector to store nodes.
 *
 * @tparam Node The type of the nodes in the graph.
 */
template <template <typename, typename> class Container, typename Node, typename Allocator = std::allocator<Node>>
class GraphInterface {
protected:

    Container<Node, Allocator> nodes_;

public:

    /**
     * @brief Constructs a GraphImpl with an optional initial capacity for nodes.
     * 
     * @param initialCapacity Initial capacity for the nodes vector. Defaults to 16.
     */
    explicit GraphImpl(size_t initialCapacity = 16) {
        nodes_.reserve(initialCapacity);
    }

    /**
     * @brief Copy constructor. Performs a deep copy of the graph.
     *
     * @param other The GraphImpl to copy from.
     */
    GraphImpl(const GraphImpl& other) : nodes_(other.nodes_)
    { }

    /**
     * @brief Move constructor. Transfers ownership of the graph from another GraphImpl.
     *
     * @param other The GraphImpl to move from.
     */
    GraphImpl(GraphImpl&& other) noexcept : nodes_(std::move(other.nodes_))
    { }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the graph.
     *
     * @param other The GraphImpl to copy from.
     * @return Reference to the assigned GraphImpl.
     */
    virtual GraphImpl& operator=(const GraphImpl& other) {
        if (this != &other) {
            nodes_ = other.nodes_;
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
            nodes_ = std::move(other.nodes_);
        }
        return *this;
    }

    /**
     * @brief Constructs a node with arguments and adds it to the graph.
     *
     * @tparam Args Types of arguments to construct the node.
     * @param args Arguments needed to construct the node.
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
     * @param index The index of the node.
     * @return Reference to the node.
     * 
     * @throws std::out_of_range if the index is invalid.
     */
    Node& getNode(size_t index) { return nodes.at(index); }

    /**
     * @brief Retrieves a const reference to the node at the specified index.
     *
     * @param index The index of the node.
     * @return Const reference to the node.
     * 
     * @throws std::out_of_range if the index is invalid.
     */
    const Node& getNode(size_t index) const { return nodes.at(index); }

    /**
     * @brief Retrieves the number of nodes in the graph.
     *
     * @return The number of nodes.
     */
    constexpr size_t size() const noexcept { return nodes.size(); }

    /**
     * @brief Checks if the graph is empty.
     *
     * @return true if the graph has no nodes, false otherwise.
     */
    constexpr bool empty() const noexcept { return nodes.empty(); }

    // *** Iterator Methods ***

    /**
     * @brief Returns an iterator to the beginning of the nodes.
     *
     * @return Iterator to the beginning of the nodes.
     */
    auto begin() { return nodes.begin(); }

    /**
     * @brief Returns an iterator to the end of the nodes.
     *
     * @return Iterator to the end of the nodes.
     */
    auto end() { return nodes.end(); }

    /**
     * @brief Returns a reverse iterator to the beginning of the nodes.
     *
     * @return Reverse iterator to the beginning of the nodes.
     */
    auto rbegin() { return nodes.rbegin(); }

    /**
     * @brief Returns a reverse iterator to the end of the nodes.
     *
     * @return Reverse iterator to the end of the nodes.
     */
    auto rend() { return nodes.rend(); }

    /**
     * @brief Returns a constant iterator to the beginning of the nodes.
     *
     * @return Constant iterator to the beginning of the nodes.
     */
    const auto begin() const { return nodes.begin(); }

    /**
     * @brief Returns a constant iterator to the end of the nodes.
     *
     * @return Constant iterator to the end of the nodes.
     */
    const auto end() const { return nodes.end(); }

    /**
     * @brief Returns a constant reverse iterator to the beginning of the nodes.
     *
     * @return Constant reverse iterator to the beginning of the nodes.
     */
    const auto rbegin() const { return nodes.rbegin(); }

    /**
     * @brief Returns a constant reverse iterator to the end of the nodes.
     *
     * @return Constant reverse iterator to the end of the nodes.
     */
    const auto rend() const { return nodes.rend(); }

    /**
     * @brief Overloads the output stream operator to print all nodes in the graph.
     *
     * @param os Output stream.
     * @param graph The graph to print.
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
        nodes.at(from).addEdge(to);
    }

};

} // namespace vpr

#endif // GRAPH_IMPL_HPP
