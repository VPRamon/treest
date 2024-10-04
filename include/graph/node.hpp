#ifndef NODE_HPP
#define NODE_HPP

#include <optional>
#include <vector>
#include <iostream>
#include <variant>
#include <memory>
#include "type_traits.hpp"

namespace vpr {

template <typename T>
class Node {

private:
    size_t index_;                     // Index of the node
    std::optional<T> value_;           // Optional value for the node
    std::vector<size_t> edges_;        // Indices of incoming edges (nodes pointing to this node)

public:

    Node(size_t index, std::optional<T> v = std::nullopt)
        : index_(index), value_(v), edges_()
    {}

    template <typename... Args>
    Node(size_t index, Args&&... args)
        : index_(index), edges_()
    {
        value_.emplace(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        value_.emplace(std::forward<Args>(args)...);
    }

    friend std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
        if (node.hasValue()) {
            if constexpr (is_variant<T>::value) {
                // Handle std::variant by visiting the current value
                std::visit([&os](const auto& val) {
                    os << val;
                }, node.value());
            } else {
                // Handle non-variant types directly
                os << node.value();
            }
        } else {
            os << "None";
        }
        return os;
    }

    size_t index() const { return index_; }

    const std::vector<size_t>& edges() const { return edges_; }

    bool hasValue() const { return value_.has_value(); }

    T& value() {
        if (hasValue()) {
            return *value_;
        } else {
            throw std::bad_optional_access();
        }
    }

    const T& value() const {
        if (hasValue()) {
            return *value_;
        } else {
            throw std::bad_optional_access();
        }
    }

    T& operator*() { return value(); }

    const T& operator*() const { return value(); }

    T* operator->() { return &(value()); }

    const T* operator->() const { return &(value()); }

    size_t degree() const { return edges_.size(); }

    void addEdge(size_t fromIndex) { edges_.push_back(fromIndex); }

    const std::vector<size_t>& getEdges(size_t index) const { return edges_; }

    bool isolated() const { return edges_.empty(); }

    std::vector<size_t> path(size_t index) const { return {/*TODO*/}; }

private:

};

} // namespace vpr

#endif // NODE_HPP
