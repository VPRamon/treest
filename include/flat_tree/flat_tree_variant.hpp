#ifndef FLAT_TREE_VARIANT_HPP
#define FLAT_TREE_VARIANT_HPP

#include "flat_tree.hpp"
#include <variant>

namespace vpr {

// Helper alias to create a FlatTree with std::variant
template <typename... Ts>
using FlatTreeVariant = FlatTree<std::variant<Ts...>>;

} // namespace vpr

#endif // FLAT_TREE_VARIANT_HPP
