#pragma once

#include "lightweight_tree_node.hpp"
#include "tree_template.hpp"

namespace vpr {
namespace lightweight {

template <typename T>
using Tree = templates::Tree<
    std::vector<                //< Tree Container Type
        tree::Node<             //< Node Type
            T,                  //< Data
            std::vector<size_t> //< Edges
        >
    >
>;

} // namespace lightweight
} // namespace vpr
