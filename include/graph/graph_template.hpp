#ifndef GRAPH_TEMPLATE_HPP
#define GRAPH_TEMPLATE_HPP

#include <iostream>
#include <stdexcept>

namespace vpr {
namespace templates {

/**
 * @brief Generic container representing a graph structure.
 * 
 * This templated graph class manages nodes and provides functionalities to add, access, and iterate over them.
 * It offers flexibility by allowing the use of custom containers and allocators.
 * 
 * @tparam Node The type representing a node in the graph.
 * @tparam Container The container type used to store nodes.
 */
template <typename Node,
          typename Container>
class Graph {
protected:
    /**
     * @brief Container holding all nodes in the graph.
     * 
     * The underlying container type is user-defined, allowing flexibility for different performance requirements.
     */
    Container nodes_;

public:
    /**
     * @brief Constructs an empty graph with an optional initial capacity.
     * 
     * @param initialCapacity Initial reserve capacity for the container to minimize reallocations.
     * @param alloc Allocator instance used to manage memory for the container.
     */
    explicit Graph(size_t initialCapacity = 16) {
        nodes_.reserve(initialCapacity);
    }

    /**
     * @brief Copy constructor.
     * 
     * Creates a deep copy of the given graph, including allocating memory using the same allocator.
     * 
     * @param other The graph to copy from.
     */
    Graph(const Graph& other) : nodes_(other.nodes_) {
        nodes_.reserve(other.nodes_.size());
        nodes_ = other.nodes_;
    }

    /**
     * @brief Move constructor.
     * 
     * Transfers ownership of the resources from the given graph to this instance, avoiding deep copies.
     * 
     * @param other The graph to move from.
     */
    Graph(Graph&& other) noexcept : nodes_(std::move(other.nodes_))
    { }

    /**
     * @brief Copy assignment operator.
     * 
     * Assigns the state of another graph to this graph, performing a deep copy of nodes.
     * 
     * @param other The graph to copy from.
     * @return A reference to the assigned graph.
     */
    Graph& operator=(const Graph& other) {
        if (this != &other) {
            nodes_ = other.nodes_;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator.
     * 
     * Transfers ownership of the resources from the given graph to this instance.
     * 
     * @param other The graph to move from.
     * @return A reference to the assigned graph.
     */
    Graph& operator=(Graph&& other) noexcept {
        nodes_ = std::move(other.nodes_);
        return *this;
    }

    /**
     * @brief Clears all nodes from the graph.
     * 
     * This operation leaves the graph empty but maintains the current capacity of the underlying container.
     */
    void clear() noexcept {
        nodes_.clear();
    }

    /**
     * @brief Constructs a new node in place.
     * 
     * Adds a new node to the graph, forwarding arguments to the node constructor.
     * 
     * @tparam Args Variadic template for forwarding arguments to the node constructor.
     * @param args Arguments used to construct the new node.
     * @return The index of the newly created node.
     */
    template <typename... Args>
    size_t emplace_node(Args&&... args) {
        size_t node_index = nodes_.size();
        nodes_.emplace_back(node_index, std::forward<Args>(args)...);
        return node_index;
    }

    /**
     * @brief Access a node by its index.
     * 
     * Throws an exception if the index is out of bounds.
     * 
     * @param index The index of the node to access.
     * @return A reference to the node at the specified index.
     * @throw std::out_of_range If the index is invalid.
     */
    Node& getNode(size_t index) { return nodes_.at(index); }

    /**
     * @brief Access a node by its index (const version).
     * 
     * Throws an exception if the index is out of bounds.
     * 
     * @param index The index of the node to access.
     * @return A const reference to the node at the specified index.
     * @throw std::out_of_range If the index is invalid.
     */
    const Node& getNode(size_t index) const { return nodes_.at(index); }

    /**
     * @brief Returns the number of nodes in the graph.
     * 
     * @return The current number of nodes.
     */
    inline size_t size() const noexcept { return nodes_.size(); }

    /**
     * @brief Checks if the graph is empty.
     * 
     * @return True if there are no nodes, false otherwise.
     */
    inline bool empty() const noexcept { return nodes_.empty(); }

    /**
     * @brief Returns an iterator to the beginning of the nodes.
     * 
     * @return Iterator pointing to the first node.
     */
    typename Container::iterator begin() noexcept { return nodes_.begin(); }

    /**
     * @brief Returns an iterator to the end of the nodes.
     * 
     * @return Iterator pointing past the last node.
     */
    typename Container::iterator end() noexcept { return nodes_.end(); }

    /**
     * @brief Returns a reverse iterator to the beginning of the nodes in reverse order.
     * 
     * @return Reverse iterator pointing to the last node.
     */
    typename Container::reverse_iterator rbegin() noexcept { return nodes_.rbegin(); }

    /**
     * @brief Returns a reverse iterator to the end of the nodes in reverse order.
     * 
     * @return Reverse iterator pointing before the first node.
     */
    typename Container::reverse_iterator rend() noexcept { return nodes_.rend(); }

    /**
     * @brief Const version of the iterator to the beginning of nodes.
     * 
     * @return Const iterator pointing to the first node.
     */
    typename Container::const_iterator begin() const noexcept { return nodes_.begin(); }

    /**
     * @brief Const version of the iterator to the end of nodes.
     * 
     * @return Const iterator pointing past the last node.
     */
    typename Container::const_iterator end() const noexcept { return nodes_.end(); }

    /**
     * @brief Const version of the reverse iterator to the beginning of nodes in reverse order.
     * 
     * @return Const reverse iterator pointing to the last node.
     */
    typename Container::const_reverse_iterator rbegin() const noexcept { return nodes_.rbegin(); }

    /**
     * @brief Const version of the reverse iterator to the end of nodes in reverse order.
     * 
     * @return Const reverse iterator pointing before the first node.
     */
    typename Container::const_reverse_iterator rend() const noexcept { return nodes_.rend(); }

    /**
     * @brief Outputs the graph to an output stream.
     * 
     * Iterates over all nodes and writes their values to the given output stream.
     * 
     * @param os The output stream.
     * @param graph The graph to output.
     * @return A reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph) {
        for (const auto& node : graph.nodes_) {
            os << node << " ";
        }
        return os;
    }

protected:
    /**
     * @brief Adds an edge between two nodes.
     * 
     * Validates indices before creating a connection from one node to another.
     * 
     * @param from Index of the starting node.
     * @param to Index of the target node.
     * @throw std::out_of_range If either index is invalid.
     */
    void addEdge(size_t from, size_t to) {
        validateIndex(to);
        nodes_.at(from).addEdge(to);
    }

    /**
     * @brief Ensures the given index is valid for accessing nodes.
     * 
     * Throws an exception if the index is out of range.
     * 
     * @param index Index to validate.
     * @throw std::out_of_range If the index is invalid.
     */
    inline void validateIndex(size_t index) const {
        if (index >= nodes_.size()) {
            throw std::out_of_range("Invalid node index.");
        }
    }
};

} // namespace templates
} // namespace vpr

#endif // GRAPH_TEMPLATE_HPP