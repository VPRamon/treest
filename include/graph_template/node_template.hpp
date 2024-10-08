#ifndef NODE_TEMPLATE_HPP
#define NODE_TEMPLATE_HPP

#include <memory>
#include <vector>

namespace vpr {

/**
 * @class NodeImpl
 * @brief Represents a graph node with optional templated data and edges.
 * 
 * @tparam T The type of the optional value held by the node.
 */
template <typename T, template <typename, typename> class Container = std::vector, typename Allocator = std::allocator<T>>
class NodeTemplate {

    size_t index_;      ///< Index of the node
    T value_;           ///< Optional value stored in the node

protected:

    Container<size_t, Allocator> edges_;        ///< Vector of indices representing edges

public:

    using DataType = T;

    /**
     * @brief Constructs a node with a given index and optional value.
     * 
     * @param index Index of the node.
     * @param v Optional value of type T (defaults to std::nullopt).
     */
    NodeTemplate(size_t index, T v)
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
    NodeTemplate(size_t index, Args&&... args)
        : index_(index), edges_(), value_(std::forward<Args>(args)...)
    { }

    /**
     * @brief Emplaces a new value in the node, replacing the old one if present.
     * 
     * @tparam Args Variadic template parameters for constructing the new value.
     * @param args Arguments to construct the new value.
     */
    template <typename... Args>
    void emplace(Args&&... args) {
        value_ = T(std::forward<Args>(args)...);
    }

    /**
     * @brief Gets the index of the node.
     * 
     * @return size_t The index of the node.
     */
    size_t index() const { return index_; }

    /**
     * @brief Gets a reference to the value stored in the node.
     * 
     * @throws std::bad_optional_access If the node has no value.
     * @return T& Reference to the value.
     */
    T& value() { return value_; }

    /**
     * @brief Gets a constant reference to the value stored in the node.
     * 
     * @throws std::bad_optional_access If the node has no value.
     * @return const T& Constant reference to the value.
     */
    const T& value() const { return value_; }

    /**
     * @brief Dereferences the node to access its value.
     * 
     * @return T& Reference to the value.
     */
    T& operator*() { return value_; }

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
    const  T* operator->() const { return &(value()); }

    /**
     * @brief Gets the degree (number of edges) of the node.
     * 
     * @return size_t The number of edges.
     */
    size_t degree() const { return edges_.size(); }

    /**
     * @brief Gets a constant reference to the edges of the node.
     * 
     * @return const std::vector<size_t>& Vector of edges.
     */
    const Container<size_t, Allocator>& edges() const { return edges_; }

    /**
     * @brief Adds an edge from this node to another node.
     * 
     * @param fromIndex Index of the connected node.
     */
    void addEdge(size_t fromIndex) { edges_.push_back(fromIndex); }

    /**
     * @brief Checks if the node is isolated (i.e., has no edges).
     * 
     * @return true If the node has no edges.
     * @return false If the node has one or more edges.
     */
    bool isolated() const { return edges_.empty(); }

    /**
     * @brief Overloads the output stream operator to print all nodes in the graph.
     *
     * @param os Output stream.
     * @param graph The graph to print.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const NodeTemplate<T, Container, Allocator>& node) {
        os << node.value();
        return os;
    }

};

} // namespace vpr

#endif // NODE_TEMPLATE_HPP
