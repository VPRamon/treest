#ifndef NODE_TEMPLATE_HPP
#define NODE_TEMPLATE_HPP

#include <memory>

namespace vpr {
namespace templates {

/**
 * @brief A template class representing a graph node with an optional value and edges.
 * 
 * This class defines a generic node structure, which holds a value of type `Data` and 
 * manages its connections (edges) using a container. The node is designed to be 
 * flexible by allowing custom containers and allocators for edge storage.
 * 
 * @tparam Data Type of the value stored in the node.
 * @tparam Edges Container for storing edges.
 */
template <typename Data,
          typename Edges>
class Node {
    using Edge = typename Edges::value_type;
    size_t index_;      ///< Index of the node.
    Data value_;        ///< Value stored in the node.

protected:
    Edges edges_; ///< Edges holding the indices of edges.

public:

    using DataType = Data; ///< Alias for the type of data stored in the node.

    /**
     * @brief Constructs a node with a given index and a value.
     * 
     * @tparam U Type of the value, defaulting to `Data`.
     * @param index Index of the node.
     * @param v Value to store in the node, perfect-forwarded.
     */
    template <typename U = Data>
    Node(size_t index, U&& v)
        : index_(index), value_(std::forward<U>(v)), edges_() {}

    /**
     * @brief Copy constructor for the Node.
     * 
     * Creates a new Node as a copy of another Node. Copies the index, value, 
     * and edges from the given Node.
     * 
     * @param other The Node to copy from.
     */
    Node(const Node& other)
        : index_(other.index_), value_(other.value_), edges_(other.edges_) {}

    /**
     * @brief Move constructor for the Node.
     * 
     * Creates a new Node by moving the data from another Node. The moved-from 
     * Node will have its resources transferred, leaving it in a valid but unspecified state.
     * 
     * @param other The Node to move from.
     */
    Node(Node&& other) noexcept
        : index_(other.index_), value_(std::move(other.value_)), edges_(std::move(other.edges_)) {}

    /**
     * @brief Copy assignment operator for the Node.
     * 
     * Assigns the values of another Node to this Node, copying the index, value, 
     * and edges from the given Node. Handles self-assignment correctly.
     * 
     * @param other The Node to copy from.
     * @return A reference to this Node after assignment.
     */
    Node& operator=(const Node& other) {
        if (this != &other) {
            index_ = other.index_;
            value_ = other.value_;
            edges_ = other.edges_;
        }
        return *this;
    }

    /**
     * @brief Move assignment operator for the Node.
     * 
     * Transfers ownership of the resources (index, value, edges) from another Node to this Node.
     * After the move, the other Node is left in a valid but unspecified state. Handles 
     * self-assignment correctly.
     * 
     * @param other The Node to move from.
     * @return A reference to this Node after assignment.
     */
    Node& operator=(Node&& other) noexcept {
        if (this != &other) {
            index_ = other.index_;
            value_ = std::move(other.value_);
            edges_ = std::move(other.edges_);
        }
        return *this;
    }


    /**
     * @brief Reserves space in the edge container for a specified number of edges.
     * 
     * This can be useful to avoid reallocations when the number of edges is known in advance.
     * 
     * @param n Number of edges to reserve space for.
     */
    void reserveEdges(size_t n) {
        edges_.reserve(n);
    }

    /**
     * @brief Emplaces a new value in the node, replacing the current one.
     * 
     * Constructs the value in place, with the forwarded arguments, 
     * destructing the previous value.
     * 
     * @tparam Args Variadic template for the constructor arguments.
     * @param args Arguments for constructing the new value.
     */
    template <typename... Args>
    void emplace(Args&&... args) {
        value_.~Data();
        new (&value_) Data(std::forward<Args>(args)...);
    }

    /**
     * @brief Returns the index of the node.
     * 
     * @return The index of the node.
     */
    inline size_t index()  const noexcept { return index_; }

    /**
     * @brief Returns the degree of the node (number of edges).
     * 
     * @return The number of edges connected to this node.
     */
    inline size_t degree() const noexcept { return edges_.size(); }

    /**
     * @brief Checks if the node is isolated (has no edges).
     * 
     * @return `true` if the node has no edges, otherwise `false`.
     */
    inline bool isolated() const noexcept { return edges_.empty(); }

    /**
     * @brief Returns a reference to the stored value.
     * 
     * @return A reference to the value.
     */
    Data& value() { return value_; }

    /**
     * @brief Returns a constant reference to the stored value.
     * 
     * @return A constant reference to the value.
     */
    const Data& value() const { return value_; }

    /**
     * @brief Dereferences the node to access the value.
     * 
     * @return A reference to the value.
     */
    Data& operator*() { return value_; }

    /**
     * @brief Dereferences the node to access the constant value.
     * 
     * @return A constant reference to the value.
     */
    const Data& operator*() const { return value(); }

    /**
     * @brief Provides pointer-like access to the value.
     * 
     * @return A pointer to the value.
     */
    Data* operator->() { return &(value()); }

    /**
     * @brief Provides constant pointer-like access to the value.
     * 
     * @return A constant pointer to the value.
     */
    const Data* operator->() const { return &(value()); }

    /**
     * @brief Returns a constant reference to the container holding edges.
     * 
     * @return A constant reference to the edges container.
     */
    const Edges& edges() const { return edges_; }

    /**
     * @brief Adds an edge to the node, connecting it to another node.
     * 
     * @param fromIndex Index of the node to which this node is being connected.
     */
    void addEdge(Edge from) { edges_.push_back(from); }

    /**
     * @brief Output stream operator for printing the node's value.
     * 
     * Prints the value stored in the node to the given output stream.
     * 
     * @param os The output stream.
     * @param node The node to print.
     * @return The output stream, for chaining.
     */
    friend std::ostream& operator<<(std::ostream& os, const Node& node) {
        os << node.value_;
        return os;
    }

};

} // namespace templates
} // namespace vpr

#endif // NODE_TEMPLATE_HPP
