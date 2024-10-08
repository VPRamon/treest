#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <type_traits>
#include <variant>

namespace vpr {

/**
 * @struct is_variant
 * @brief Trait to detect if a type is an instance of `std::variant`.
 *
 * This trait helps determine whether a given type `T` is a `std::variant`. 
 * It inherits from `std::true_type` if `T` is a `std::variant`, and from 
 * `std::false_type` otherwise.
 *
 * @tparam T The type to check.
 */
template<typename T>
struct is_variant : std::false_type {};

/**
 * @brief Specialization of `is_variant` for `std::variant` types.
 *
 * This specialization sets `is_variant<std::variant<Ts...>>` to inherit 
 * from `std::true_type`, indicating that `std::variant` is detected.
 */
template<typename... Ts>
struct is_variant<std::variant<Ts...>> : std::true_type {};

} // namespace vpr

#endif // TYPE_TRAITS_HPP
