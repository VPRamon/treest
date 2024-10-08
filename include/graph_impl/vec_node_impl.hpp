#ifndef VEC_NODE_IMPL_HPP
#define VEC_NODE_IMPL_HPP

#include <optional>
#include <vector>
#include <iostream>
#include <variant>
#include <memory>
#include "type_traits.hpp"

namespace vpr {
namespace vec {

    template <typename T>
    using NodeImpl = NodeInterface<std::vector, T>;

} // namespace vec
} // namespace vpr

#endif // NODE_IMPL_HPP
