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
class Digraph {
public:
    using Node = NodeTemplate<T, std::vector>;

private:

    GraphTemplate<Node, std::vector> graph_impl_;

public:

    /**
     * @brief Constructs a Digraph with an optional initial capacity for nodes.
     * 
     * @param initial_capacity Initial capacity for the nodes vector. Defaults to 16.
     */
    explicit Digraph(size_t initial_capacity = 16) : graph_impl_(initial_capacity)
    { }

    /**
     * @brief Copy constructor. Performs a deep copy of the graph.
     *
     * @param other The Digraph to copy from.
     */
    Digraph(const Digraph& other) : graph_impl_(other.graph_impl_)
    { }

    /**
     * @brief Move constructor. Transfers ownership of the graph from another Digraph.
     *
     * @param other The Digraph to move from.
     */
    Digraph(Digraph&& other) noexcept : graph_impl_(std::move(other.graph_impl_))
    { }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the graph.
     *
     * @param other The Digraph to copy from.
     * @return Reference to the assigned Digraph.
     */
    virtual Digraph& operator=(const Digraph& other) {
        if (this != &other) {
            graph_impl_ = other.graph_impl_;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator. Transfers ownership of the graph from another Digraph.
     *
     * @param other The Digraph to move from.
     * @return Reference to the assigned Digraph.
     */
    Digraph& operator=(Digraph&& other) noexcept {
        if (this != &other) {
            graph_impl_ = std::move(other.graph_impl_);
        }
        return *this;
    }

    size_t addNode(Node node) {
        return graph_impl_.emplace_node(node.value());
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
        graph_impl_.addEdge(from, to);
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
        return graph_impl_.emplace_node(std::forward<Args>(args)...);
    }

    /**
     * @brief Retrieves a reference to the node at the specified index.
     *
     * @param index The index of the node.
     * @return Reference to the node.
     * 
     * @throws std::out_of_range if the index is invalid.
     */
    Node& getNode(size_t index) { return graph_impl_.getNode(index); }

    /**
     * @brief Retrieves a const reference to the node at the specified index.
     *
     * @param index The index of the node.
     * @return Const reference to the node.
     * 
     * @throws std::out_of_range if the index is invalid.
     */
    const Node& getNode(size_t index) const { return graph_impl_.getNode(index); }

    /**
     * @brief Retrieves the number of nodes in the graph.
     *
     * @return The number of nodes.
     */
    constexpr size_t size() const noexcept { return graph_impl_.size(); }

    /**
     * @brief Checks if the graph is empty.
     *
     * @return true if the graph has no nodes, false otherwise.
     */
    constexpr bool empty() const noexcept { return graph_impl_.empty(); }

    // *** Iterator Methods ***

    /**
     * @brief Returns an iterator to the beginning of the nodes.
     *
     * @return Iterator to the beginning of the nodes.
     */
    auto begin() { return graph_impl_.begin(); }

    /**
     * @brief Returns an iterator to the end of the nodes.
     *
     * @return Iterator to the end of the nodes.
     */
    auto end() { return graph_impl_.end(); }

    /**
     * @brief Returns a reverse iterator to the beginning of the nodes.
     *
     * @return Reverse iterator to the beginning of the nodes.
     */
    auto rbegin() { return graph_impl_.rbegin(); }

    /**
     * @brief Returns a reverse iterator to the end of the nodes.
     *
     * @return Reverse iterator to the end of the nodes.
     */
    auto rend() { return graph_impl_.rend(); }

    /**
     * @brief Returns a constant iterator to the beginning of the nodes.
     *
     * @return Constant iterator to the beginning of the nodes.
     */
    const auto begin() const { return graph_impl_.begin(); }

    /**
     * @brief Returns a constant iterator to the end of the nodes.
     *
     * @return Constant iterator to the end of the nodes.
     */
    const auto end() const { return graph_impl_.end(); }

    /**
     * @brief Returns a constant reverse iterator to the beginning of the nodes.
     *
     * @return Constant reverse iterator to the beginning of the nodes.
     */
    const auto rbegin() const { return graph_impl_.rbegin(); }

    /**
     * @brief Returns a constant reverse iterator to the end of the nodes.
     *
     * @return Constant reverse iterator to the end of the nodes.
     */
    const auto rend() const { return graph_impl_.rend(); }

    /**
     * @brief Overloads the output stream operator to print all nodes in the graph.
     *
     * @param os Output stream.
     * @param graph The graph to print.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Digraph<T>& graph) {
        os << graph.graph_impl_;
        return os;
    }

};

} // namespace lightweight
} // namespace vpr

#endif // LIGHTWEIGHT_DIGRAPH_HPP
