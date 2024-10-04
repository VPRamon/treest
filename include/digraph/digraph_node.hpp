#ifndef DIGRAPH_NODE_HPP
#define DIGRAPH_NODE_HPP

#include "digraph_node_impl.hpp"

namespace vpr {

namespace digraph {

template <typename T>
using Node = digraph_impl::Node<T>;

} // namespace digraph
} // namespace vpr

#endif // DIGRAPH_NODE_HPP
