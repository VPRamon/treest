#ifndef GRAPH_NODE_HPP
#define GRAPH_NODE_HPP

#include <optional>
#include <vector>
#include <iostream>
#include <variant>
#include "type_traits.hpp"

namespace vpr {

template <typename T>
class Graph;

template <typename T>
class GraphNode {

    friend class Graph<T>;

private:
    size_t index_;                             // Index of the node
    std::vector<size_t> incomingEdges_;        // Indices of incoming edges (nodes pointing to this node)
    std::vector<size_t> outgoingEdges_;        // Indices of outgoing edges (nodes this node points to)
    Graph<T>* graph_;                          // Pointer to the graph

public:
    std::optional<T> value;                    // Optional value for the node

    GraphNode(std::optional<T> v, size_t index = 0, Graph<T>* graph = nullptr)
        : value(v), index_(index), graph_(graph), incomingEdges_(), outgoingEdges_()
    {}

    friend std::ostream& operator<<(std::ostream& os, const GraphNode<T>& node) {
        if (node.value.has_value()) {
            if constexpr (is_variant<T>::value) {
                // Handle std::variant by visiting the current value
                std::visit([&os](const auto& val) {
                    os << val;
                }, node.value.value());
            } else {
                // Handle non-variant types directly
                os << node.value.value();
            }
        } else {
            os << "None";
        }
        return os;
    }

    size_t index() const { return index_; }

    const std::vector<size_t>& incomingEdges() const { return incomingEdges_; }
    const std::vector<size_t>& outgoingEdges() const { return outgoingEdges_; }

    Graph<T>* graph() const { return graph_; }

    size_t nOutgoingEdges() const { return outgoingEdges_.size(); }
    size_t nIncomingEdges() const { return incomingEdges_.size(); }

    void addOutgoingEdge(size_t toIndex) {
        outgoingEdges_.push_back(toIndex);
    }

    void addIncomingEdge(size_t fromIndex) {
        incomingEdges_.push_back(fromIndex);
    }

    GraphNode<T>& getEdge(size_t index) { return graph_->getNode(outgoingEdges_.at(index)); }
    GraphNode<const T>& getEdge(size_t index) const { return graph_->getNode(outgoingEdges_.at(index)); }

    std::vector<std::reference_wrapper<GraphNode<T>>> getOutgoingEdges() {
        std::vector<std::reference_wrapper<GraphNode<T>>> neighbors;
        neighbors.reserve(outgoingEdges_.size());
        for (const size_t& neighborIdx : outgoingEdges_) {
            neighbors.emplace_back(graph_->getNode(neighborIdx));
        }
        return neighbors;
    }

    std::vector<std::reference_wrapper<const GraphNode<T>>> getOutgoingEdges() const {
        std::vector<std::reference_wrapper<const GraphNode<T>>> neighbors;
        neighbors.reserve(outgoingEdges_.size());
        for (const size_t& neighborIdx : outgoingEdges_) {
            neighbors.emplace_back(graph_->getNode(neighborIdx));
        }
        return neighbors;
    }
};

} // namespace vpr

#endif // GRAPH_NODE_HPP
