#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include "digraph_impl.hpp"
#include "digraph_node.hpp"

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
class Digraph : public DigraphImpl<digraph::Node<T>> {
    using Base = DigraphImpl<digraph::Node<T>>;
public:

    using Base::DigraphImpl;

    /**
     * @brief Adds a node with no edges.
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
