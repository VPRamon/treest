#ifndef GRAPH_NODE_HPP
#define GRAPH_NODE_HPP

#include "lightweight_graph_node.hpp"

namespace vpr {
template <typename T> class Graph;
namespace graph {

/**
 * @class Node
 * @brief A specialized graph node that inherits from NodeImpl.
 *
 * This class represents a node within a graph structure and extends 
 * the functionality of the base NodeImpl class. Each node can store 
 * an optional value and manage its edges in the graph.
 *
 * @tparam T The type of the value stored in the node.
 */
template <typename T>
class Node : public NodeTemplate<T> {
    using Base = vpr::lightweight::graph::Node<T>;
    friend Graph<T>;

    Graph<T>* graph_;

protected:

    /**
     * @brief Adds an edge from this node to another node.
     *
     * @param fromIndex The index of the node to add an edge to.
     */
    virtual void addEdge(size_t fromIndex) override {
        Base::addEdge(fromIndex);
    }

public:

    template <typename... Args>
    Node(Graph<T>* graph, Args&&... args)
        : Base(std::forward<Args>(args)...), graph_(graph)
    { }

    void graph(Graph<T>* graph) {
        this->graph_ = graph;
    }

    /**
     * @brief Adds an edge from this node to another node. 
     *
     * @param fromIndex The index of the node to add an edge to.
     */
    void addEdgeTo(size_t fromIndex) {
        this->graph_->addEdge(Base::index(), fromIndex);
    }

};

} // namespace graph
} // namespace vpr

#endif // GRAPH_NODE_HPP
