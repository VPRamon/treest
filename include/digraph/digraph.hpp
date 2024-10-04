#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include "digraph_impl.hpp"
#include "digraph_node.hpp"

namespace vpr {

/**
 * @class Digraph
 * @brief A directed graph class specialized for managing nodes with directed edges.
 *
 * This class extends `DigraphImpl` to manage a directed graph where nodes store values 
 * of type `T`. The graph allows efficient traversal and manipulation of directed edges.
 *
 * @tparam T The type of the value stored in each node.
 */
template <typename T>
class Digraph : public DigraphImpl<digraph::Node<T>> {
    using Base = DigraphImpl<digraph::Node<T>>;

public:

    // Inherit constructors from DigraphImpl
    using Base::DigraphImpl;

    /**
     * @brief Adds a new node to the graph with an optional value.
     *
     * This method adds a node with no edges, optionally storing a value of type `T`.
     *
     * @param value Optional value for the node. Defaults to `std::nullopt`.
     * @return The index of the newly added node.
     */
    size_t addNode(std::optional<T> value = std::nullopt) {
        return Base::template addNode(value);
    }

};

} // namespace vpr

#endif // DIGRAPH_HPP
