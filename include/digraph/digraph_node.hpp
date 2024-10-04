#ifndef DIGRAPH_NODE_HPP
#define DIGRAPH_NODE_HPP

#include "digraph_node_impl.hpp"

namespace vpr {

namespace digraph {

/**
 * @typedef Node
 * @brief Alias for the directed graph node implementation.
 *
 * This typedef provides a simplified alias for `digraph_impl::Node<T>`, 
 * representing a node in a directed graph that manages incoming and 
 * outgoing edges.
 *
 * @tparam T The type of the value stored in the node.
 */
template <typename T>
using Node = digraph_impl::Node<T>;

} // namespace digraph
} // namespace vpr

#endif // DIGRAPH_NODE_HPP
