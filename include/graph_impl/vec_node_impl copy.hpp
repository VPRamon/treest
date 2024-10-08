#ifndef VEC_NODE_IMPL_HPP
#define VEC_NODE_IMPL_HPP

#include <optional>
#include <vector>
#include <iostream>
#include <variant>
#include <memory>
#include "type_traits.hpp"

namespace vpr {

/**
 * @class NodeImpl
 * @brief Represents a graph node with optional templated data and edges.
 * 
 * @tparam T The type of the optional value held by the node.
 */
template <typename T>
class VecNodeImpl : NodeInterface {

    size_t index_;                     ///< Index of the node
    std::optional<T> value_;           ///< Optional value stored in the node

protected:

    std::vector<size_t> edges_;        ///< Vector of indices representing edges

public:

    /**
     * @brief Constructs a node with a given index and optional value.
     * 
     * @param index Index of the node.
     * @param v Optional value of type T (defaults to std::nullopt).
     */
    NodeImpl(size_t index, std::optional<T> v = std::nullopt)
        : index_(index), value_(v), edges_()
    {}

    /**
     * @brief Constructs a node with a given index and initializes value in place.
     * 
     * @tparam Args Variadic template parameters for constructing the value.
     * @param index Index of the node.
     * @param args Arguments to construct the value.
     */
    template <typename... Args>
    NodeImpl(size_t index, Args&&... args)
        : index_(index), edges_()
    {
        value_.emplace(std::forward<Args>(args)...);
    }

    /**
     * @brief Emplaces a new value in the node, replacing the old one if present.
     * 
     * @tparam Args Variadic template parameters for constructing the new value.
     * @param args Arguments to construct the new value.
     */
    template <typename... Args>
    void emplace(Args&&... args) {
        value_.emplace(std::forward<Args>(args)...);
    }

    /**
     * @brief Outputs the node's value or "None" if it has no value.
     * 
     * @param os The output stream.
     * @param node The node to be printed.
     * @return std::ostream& The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& os, const NodeImpl<T>& node) {
        if (node.hasValue()) {
            if constexpr (is_variant<T>::value) {
                std::visit([&os](const auto& val) {
                    os << val;
                }, node.value());
            } else {
                os << node.value();
            }
        } else {
            os << "None";
        }
        return os;
    }

    /**
     * @brief Gets the index of the node.
     * 
     * @return size_t The index of the node.
     */
    size_t index() const { return index_; }

    /**
     * @brief Checks if the node holds a value.
     * 
     * @return true If the node has a value.
     * @return false If the node does not have a value.
     */
    bool hasValue() const { return value_.has_value(); }

    /**
     * @brief Gets a reference to the value stored in the node.
     * 
     * @throws std::bad_optional_access If the node has no value.
     * @return T& Reference to the value.
     */
    T& value() {
        if (hasValue()) {
            return *value_;
        } else {
            throw std::bad_optional_access();
        }
    }

    /**
     * @brief Gets a constant reference to the value stored in the node.
     * 
     * @throws std::bad_optional_access If the node has no value.
     * @return const T& Constant reference to the value.
     */
    const T& value() const {
        if (hasValue()) {
            return *value_;
        } else {
            throw std::bad_optional_access();
        }
    }

    /**
     * @brief Dereferences the node to access its value.
     * 
     * @return T& Reference to the value.
     */
    T& operator*() { return value(); }

    /**
     * @brief Dereferences the node to access its constant value.
     * 
     * @return const T& Constant reference to the value.
     */
    const T& operator*() const { return value(); }

    /**
     * @brief Accesses the value through the arrow operator.
     * 
     * @return T* Pointer to the value.
     */
    T* operator->() { return &(value()); }

    /**
     * @brief Accesses the constant value through the arrow operator.
     * 
     * @return const T* Pointer to the constant value.
     */
    const T* operator->() const { return &(value()); }

    /**
     * @brief Returns a vector representing the path to another node by index.
     * 
     * @param index Target node index.
     * @return std::vector<size_t> Vector representing the path (to be implemented).
     */
    std::vector<size_t> path(size_t index) const { return {/*TODO*/}; }

protected:

    /**
     * @brief Gets the degree (number of edges) of the node.
     * 
     * @return size_t The number of edges.
     */
    virtual size_t degree() const { return edges_.size(); }

    /**
     * @brief Gets a constant reference to the edges of the node.
     * 
     * @return const std::vector<size_t>& Vector of edges.
     */
    virtual const std::vector<size_t>& edges() const { return edges_; }

    /**
     * @brief Adds an edge from this node to another node.
     * 
     * @param fromIndex Index of the connected node.
     */
    virtual void addEdge(size_t fromIndex) { edges_.push_back(fromIndex); }

    /**
     * @brief Checks if the node is isolated (i.e., has no edges).
     * 
     * @return true If the node has no edges.
     * @return false If the node has one or more edges.
     */
    virtual bool isolated() const { return edges_.empty(); }

};

} // namespace vpr

#endif // NODE_IMPL_HPP
