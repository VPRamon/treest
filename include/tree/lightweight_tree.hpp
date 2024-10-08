#ifndef TREE_HPP
#define TREE_HPP

#include "lightweight_tree_node.hpp"
#include "tree_template.hpp"

namespace vpr {
namespace lightweight {

template <typename T>
using Tree = templates::TreeImpl<tree::Node<T>, std::vector>;


} // namespace lightweight
} // namespace vpr

#endif // TREE_HPP
