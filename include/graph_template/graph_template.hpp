#ifndef GRAPH_TEMPLATE_HPP
#define GRAPH_TEMPLATE_HPP

#include <iostream>
#include <stdexcept>

namespace vpr {

/**
 * @class GraphTemplate
 * @brief A base graph implementation using a vector to store nodes.
 *
 * @tparam Node The type of the nodes in the graph.
 */
template <typename Node, template <typename, typename> class Container = std::vector, typename Allocator = std::allocator<Node>>
class GraphTemplate {
protected:

    Container<Node, Allocator> nodes_;

public:

    /**
     * @brief Constructs a GraphTemplate with an optional initial capacity for nodes.
     * 
     * @param initialCapacity Initial capacity for the nodes vector. Defaults to 16.
     */
    explicit GraphTemplate(size_t initialCapacity = 16) {
        nodes_.reserve(initialCapacity);
    }

    /**
     * @brief Copy constructor. Performs a deep copy of the graph.
     *
     * @param other The GraphTemplate to copy from.
     */
    GraphTemplate(const GraphTemplate& other) : nodes_(other.nodes_)
    { }

    /**
     * @brief Move constructor. Transfers ownership of the graph from another GraphTemplate.
     *
     * @param other The GraphTemplate to move from.
     */
    GraphTemplate(GraphTemplate&& other) noexcept : nodes_(std::move(other.nodes_))
    { }

    /**
     * @brief Copy assignment operator. Performs a deep copy of the graph.
     *
     * @param other The GraphTemplate to copy from.
     * @return Reference to the assigned GraphTemplate.
     */
    GraphTemplate& operator=(const GraphTemplate& other) {
        if (this != &other) {
            nodes_ = other.nodes_;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator. Transfers ownership of the graph from another GraphTemplate.
     *
     * @param other The GraphTemplate to move from.
     * @return Reference to the assigned GraphTemplate.
     */
    GraphTemplate& operator=(GraphTemplate&& other) noexcept {
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
        size_t nodeIndex = nodes_.size();
        nodes_.emplace_back(nodeIndex, std::forward<Args>(args)...);
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
    Node& getNode(size_t index) { return nodes_.at(index); }

    /**
     * @brief Retrieves a const reference to the node at the specified index.
     *
     * @param index The index of the node.
     * @return Const reference to the node.
     * 
     * @throws std::out_of_range if the index is invalid.
     */
    const Node& getNode(size_t index) const { return nodes_.at(index); }

    /**
     * @brief Retrieves the number of nodes_ in the graph.
     *
     * @return The number of nodes.
     */
    constexpr size_t size() const noexcept { return nodes_.size(); }

    /**
     * @brief Checks if the graph is empty.
     *
     * @return true if the graph has no nodes_, false otherwise.
     */
    constexpr bool empty() const noexcept { return nodes_.empty(); }

    // *** Iterator Methods ***

    /**
     * @brief Returns an iterator to the beginning of the nodes.
     *
     * @return Iterator to the beginning of the nodes.
     */
    auto begin() { return nodes_.begin(); }

    /**
     * @brief Returns an iterator to the end of the nodes_.
     *
     * @return Iterator to the end of the nodes.
     */
    auto end() { return nodes_.end(); }

    /**
     * @brief Returns a reverse iterator to the beginning of the nodes.
     *
     * @return Reverse iterator to the beginning of the nodes.
     */
    auto rbegin() { return nodes_.rbegin(); }

    /**
     * @brief Returns a reverse iterator to the end of the nodes.
     *
     * @return Reverse iterator to the end of the nodes.
     */
    auto rend() { return nodes_.rend(); }

    /**
     * @brief Returns a constant iterator to the beginning of the nodes.
     *
     * @return Constant iterator to the beginning of the nodes.
     */
    const auto begin() const { return nodes_.begin(); }

    /**
     * @brief Returns a constant iterator to the end of the nodes.
     *
     * @return Constant iterator to the end of the nodes.
     */
    const auto end() const { return nodes_.end(); }

    /**
     * @brief Returns a constant reverse iterator to the beginning of the nodes.
     *
     * @return Constant reverse iterator to the beginning of the nodes.
     */
    const auto rbegin() const { return nodes_.rbegin(); }

    /**
     * @brief Returns a constant reverse iterator to the end of the nodes.
     *
     * @return Constant reverse iterator to the end of the nodes.
     */
    const auto rend() const { return nodes_.rend(); }

    /**
     * @brief Overloads the output stream operator to print all nodes in the graph.
     *
     * @param os Output stream.
     * @param graph The graph to print.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const GraphTemplate<Node, Container, Allocator>& graph) {
        for (const auto& node : graph.nodes_) {
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
    void addEdge(size_t from, size_t to) {
        validateIndex(to);
        nodes_.at(from).addEdge(to);
    }

private:

    /**
     * @brief Validates if a node index is within bounds.
     *
     * @param index The index to validate.
     * 
     * @throws std::out_of_range if the index is invalid.
     */
    inline void validateIndex(size_t index) const {
        if (index >= nodes_.size()) {
            throw std::out_of_range("Invalid node index.");
        }
    }
};

} // namespace vpr

#endif // GRAPH_TEMPLATE_HPP
