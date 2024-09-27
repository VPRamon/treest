// type_traits.hpp
#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <type_traits>
#include <variant>

namespace vpr {

template<typename T>
struct is_variant : std::false_type {};

template<typename... Ts>
struct is_variant<std::variant<Ts...>> : std::true_type {};

} // namespace vpr

#endif // TYPE_TRAITS_HPP
