#ifndef NODE_IMPL_HPP
#define NODE_IMPL_HPP

#include <optional>
#include <vector>
#include <iostream>
#include <variant>
#include <memory>
#include "type_traits.hpp"

namespace vpr {

template <typename T>
class NodeImpl {

    size_t index_;                     // Index of the node
    std::optional<T> value_;           // Optional value for the node

protected:

    std::vector<size_t> edges_;        // Indices of edges

public:

    NodeImpl(size_t index, std::optional<T> v = std::nullopt)
        : index_(index), value_(v), edges_()
    {}

    template <typename... Args>
    NodeImpl(size_t index, Args&&... args)
        : index_(index), edges_()
    {
        value_.emplace(std::forward<Args>(args)...);
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        value_.emplace(std::forward<Args>(args)...);
    }

    friend std::ostream& operator<<(std::ostream& os, const NodeImpl<T>& node) {
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

    std::vector<size_t> path(size_t index) const { return {/*TODO*/}; }

protected:

    virtual size_t degree() const { return edges_.size(); }

    virtual const std::vector<size_t>& edges() const { return edges_; }

    virtual void addEdge(size_t fromIndex) { edges_.push_back(fromIndex); }

    virtual bool isolated() const { return edges_.empty(); }

};

} // namespace vpr

#endif // NODE_IMLP_HPP
