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
class DigraphNode : public Node {

private:

    std::vector<size_t>& out_edges_ = &edges_;
    std::vector<size_t> in_edges_;

public:

    Node(size_t index, std::optional<T> v = std::nullopt)
        : index_(index), value_(v), edges_()
    {}

    template <typename... Args>
    void emplace(Args&&... args) {
        value_.emplace(std::forward<Args>(args)...);
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
