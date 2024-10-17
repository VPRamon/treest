#pragma once

#include "lightweight_tree_node.hpp"
#include "tree_template.hpp"

namespace vpr {
namespace lightweight {

template <typename T>
using BinaryTree = templates::Tree<tree::Node<T>, std::array>;


} // namespace lightweight
} // namespace vpr
