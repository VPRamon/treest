#ifndef TREE_VARIANT_HPP
#define TREE_VARIANT_HPP

#include "tree.hpp"
#include <variant>

namespace vpr {

// Helper alias to create a Tree with std::variant
template <typename... Ts>
using TreeVariant = Tree<std::variant<Ts...>>;

} // namespace vpr

#endif // TREE_VARIANT_HPP
