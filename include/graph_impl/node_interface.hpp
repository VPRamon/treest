#ifndef NODE_INTERFACE_HPP
#define NODE_INTERFACE_HPP

#include <memory>

namespace vpr {

/**
 * @class NodeImpl
 * @brief Represents a graph node with optional templated data and edges.
 * 
 * @tparam T The type of the optional value held by the node.
 */
template <template <typename, typename> class Container, typename T, typename Allocator = std::allocator<T>>
class NodeInterface {

    size_t index_;      ///< Index of the node
    T value_;           ///< Optional value stored in the node

protected:

    Container<size_t, Allocator> edges_;        ///< Vector of indices representing edges

public:

    /**
     * @brief Constructs a node with a given index and optional value.
     * 
     * @param index Index of the node.
     * @param v Optional value of type T (defaults to std::nullopt).
     */
    NodeInterface(size_t index, T v)
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
    NodeInterface(size_t index, Args&&... args)
        : index_(index), edges_()
    {
        value_(std::forward<Args>(args)...);
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
    virtual T& value() { return value_; }

    /**
     * @brief Gets a constant reference to the value stored in the node.
     * 
     * @throws std::bad_optional_access If the node has no value.
     * @return const T& Constant reference to the value.
     */
    virtual const T& value() const { return value_; }

    /**
     * @brief Dereferences the node to access its value.
     * 
     * @return T& Reference to the value.
     */
    virtual T& operator*() { return value_; }

    /**
     * @brief Dereferences the node to access its constant value.
     * 
     * @return const T& Constant reference to the value.
     */
    virtual const T& operator*() const { return value(); }

    /**
     * @brief Accesses the value through the arrow operator.
     * 
     * @return T* Pointer to the value.
     */
    virtual T* operator->() { return &(value()); }

    /**
     * @brief Accesses the constant value through the arrow operator.
     * 
     * @return const T* Pointer to the constant value.
     */
    virtual const  T* operator->() const { return &(value()); }

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
